//
//  Copyright (c) 2013 Tap for Tap. All rights reserved.
//

#import "TFTTapForTap.h"
#import "TFTBanner.h"

#import "TFTAd.h"
#import "TFTAdRequest.h"
#import "TFTBannerAd.h"
#import "TFTLog.h"
#import "TFTImpressionRequest.h"
#import "TFTMRAIDPictureDelegate.h"
#import "TFTFreeformWebViewController.h"
#import "TFTMRAID.h"
#import "TFTTrackingPixelRequest.h"

static NSString *const BANNER_PATH = @"ad/banner";

@interface TFTBanner() <UIWebViewDelegate>
@property (nonatomic, retain) TFTBannerAd *banner1;
@property (nonatomic, retain) TFTBannerAd *banner2;
@property (nonatomic, assign) BOOL show1;
@property (nonatomic, assign) BOOL stopped;
@property (nonatomic, assign) double_t rolloverDelay;
@property (nonatomic, retain) TFTMRAID *mraidController;

- (void)getNextAdIn:(NSNumber *)delay;
@end

@implementation TFTBanner

#pragma mark - Initialization

+ (TFTBanner *)bannerWithFrame:(CGRect)frame{
    TFTBanner *bannerAd = [[TFTBanner alloc] initWithFrame:frame];
    [bannerAd startShowingAds];
    return bannerAd;
}

+ (TFTBanner *)bannerWithFrame:(CGRect)frame delegate:(id<TFTBannerDelegate>)delegate {
    TFTBanner *bannerAd = [[TFTBanner alloc] initWithFrame:frame delegate:delegate];
    [bannerAd startShowingAds];
    return bannerAd;
}

- (id)initWithFrame:(CGRect)frame {
    return [self initWithFrame:frame delegate:nil];
}

- (id)initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
    return [self initWithFrame:[self frame] delegate:nil];
}

- (id)initWithFrame:(CGRect)frame delegate:(id<TFTBannerDelegate>)delegate {
    self = [super initWithFrame:frame];
    if (self) {
        _autoRollover = YES;
        _rolloverDelay = 5.0;
        _delegate = delegate;
        _banner1 = [self createBannerAdWithFrame:frame delegate:delegate];
        _banner2 = [self createBannerAdWithFrame:frame delegate:delegate];
        _show1 = YES;
        _stopped = NO;
        _forceLoad = NO;
        _mraidController = [[TFTMRAID alloc] init];
        [self addSubview:_banner2];
        [self addSubview:_banner1];
        self.clipsToBounds = YES;
    }
    return self;
}

- (TFTBannerAd *)createBannerAdWithFrame:(CGRect)frame delegate:(id<TFTBannerDelegate>)delegate {
    TFTBannerAd *bannerAd = [TFTBannerAd createAdWithFrame:CGRectMake(0, 0, frame.size.width, frame.size.height) delegate:self bannerDelegate:delegate];
    return bannerAd;
}

#pragma mark - Setters

- (void) setDelegate:(id<TFTBannerDelegate>)delegate {
    _delegate = delegate;
    self.banner1.delegate = delegate;
    self.banner2.delegate = delegate;
}

#pragma mark - Life Cycle
//TODO XCode complains "Undeclared selector 'initializeWithHandler'" - needs fixing
- (void)startShowingAds {
    self.stopped = NO;
    self.autoRollover = YES;
    [self getNextAdIn:@1.0];
}

- (void)resumeShowingAds {
    self.stopped = NO;
}

- (void)stopShowingAds {
    self.stopped = YES;
}

- (void) showBanner {
    self.hidden = NO;
    [self startShowingAds];
}

- (void) hideBanner {
    self.hidden = YES;
    [self stopShowingAds];
}

- (void)showNewAd {
    [self getBannerAd];
}

- (void)getBannerAd {
    
    if (self.stopped) {
        TFTDebugLog(@"Stopped, not loading any next ad anymore.");
        return;
    }
    
    if(self.mraidController.expandedWebViewController != nil) {
        TFTDebugLog(@"mraidController reports an expandedWebViewController, skipping next ad.");
        [self getNextAdIn:@5.0];
        return;
    }
    
    if (!self.superview.window && !self.forceLoad) {
        TFTDebugLog(@"Not in view, skipping next ad.");
        [self getNextAdIn:@5.0];
        return;
    }
    
    if(self.hidden)
    {
        TFTDebugLog(@"Banner is hidden, skipping next ad.");
        [self getNextAdIn:@5.0];
        return;
    }
    
    if(self.alpha == 0)
    {
        TFTDebugLog(@"Alpha is set to 0, skipping next ad.");
        [self getNextAdIn:@5.0];
        return;
    }
    
    NSMutableDictionary *params = [NSMutableDictionary dictionary];
    [params setObject:[NSString stringWithFormat:@"%.0f", (self.frame.size.width * [UIScreen mainScreen].scale)] forKey:@"container_width"];
    [params setObject:[NSString stringWithFormat:@"%.0f", (self.frame.size.height * [UIScreen mainScreen].scale)] forKey:@"container_height"];
    
    [TFTAdRequest startNewAdRequestWithPath:BANNER_PATH withParams:params withHandler:^(BOOL success, TFTAd *ad, NSString *reason) {
        if (success) {
            if (self.show1) {
                self.banner1.ad = ad;
            } else {
                self.banner2.ad = ad;
            }

            [TFTImpressionRequest startNewImpressionRequestWithImpressionIds:[ad impressionIds]];
            
            [self getNextAdIn:ad.refresh];
        }
        else {
            [self postFailedToReceiveAd:[@"Failed to download ad because: " stringByAppendingString:reason]];
        }
    }];
}

- (void)getNextAdIn:(NSNumber *)delay {
    if (self.autoRollover && !self.stopped) {
        [self performSelector:@selector(getBannerAd) withObject:nil afterDelay:[delay doubleValue]];
    }
}

#pragma mark - WebView Delegate
//This intercepts MRAID Requests.
- (BOOL) webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType {

    NSString *url = request.URL.absoluteString;
    
    [self.mraidController setCurrentWebview:webView];
    [self.mraidController setCurrentBanner:self];
    
    if ([url rangeOfString:@"tapfortap://mraid/expand"].location == 0) {
        [self.mraidController expandBanner:self withWebView:webView andURLString:url];
        return NO;
    }

    if ([url rangeOfString:@"tapfortap://mraid/resize"].location == 0) {
        [self.mraidController resizeBanner:self withWebView:webView andURLString:url];
        return NO;
    }

    if ([url rangeOfString:@"tapfortap://mraid/close"].location == 0) {
        [self.mraidController dismissWithBanner];
        return NO;
    }

    if ([url rangeOfString:@"tapfortap://mraid/open/"].location == 0) {
        [self.mraidController openWithURLString:url];
        return NO;
    }

    if ([url rangeOfString:@"tapfortap://mraid/playVideo/"].location == 0) {
        [self.mraidController playVideoWithURLString:url];
        return NO;
    }
    
    if ([url rangeOfString:@"tapfortap://mraid/storePicture/"].location == 0) {
        [self.mraidController storePictureWithURLString:url];
        return NO;
        
    }

    if ([url rangeOfString:@"tapfortap://mraid/createCalendarEvent/"].location == 0) {
        [self.mraidController setCurrentWebview:webView];
        [self.mraidController createCalendarEventWithURLString:url];
        return NO;
        
    }

    if ([url rangeOfString:@"tapfortap://mraid/useCustomClose/"].location == 0) {
        [self.mraidController useCustomCloseWithURLString:url];
        return NO;
    }
    
    return YES;
    
}

- (void)webViewDidFinishLoad:(UIWebView *)webView {
    
    [webView stringByEvaluatingJavaScriptFromString:@"mraid._placementType = 'inline';"];
    if (![[UIApplication sharedApplication] canOpenURL:[NSURL URLWithString:@"tel:5555555"]]) {
        [webView stringByEvaluatingJavaScriptFromString:@"mraid._supports_tel = false;"];
    }
    if (![[UIApplication sharedApplication] canOpenURL:[NSURL URLWithString:@"sms:5555555"]]) {
        [webView stringByEvaluatingJavaScriptFromString:@"mraid._supports_sms = false;"];
    }
    [webView stringByEvaluatingJavaScriptFromString:[NSString stringWithFormat:@"mraid._currentX = %.0f;", webView.frame.origin.x]];
    [webView stringByEvaluatingJavaScriptFromString:[NSString stringWithFormat:@"mraid._currentY = %.0f;", webView.frame.origin.y]];
    [webView stringByEvaluatingJavaScriptFromString:[NSString stringWithFormat:@"mraid._currentWidth = %.0f;", webView.frame.size.width]];
    [webView stringByEvaluatingJavaScriptFromString:[NSString stringWithFormat:@"mraid._currentHeight = %.0f;", webView.frame.size.height]];
    [webView stringByEvaluatingJavaScriptFromString:[NSString stringWithFormat:@"mraid._defaultWidth = %.0f;", webView.frame.size.width]];
    [webView stringByEvaluatingJavaScriptFromString:[NSString stringWithFormat:@"mraid._defaultHeight = %.0f;", webView.frame.size.height]];
    CGSize screenSize = [[UIScreen mainScreen] bounds].size;
    [webView stringByEvaluatingJavaScriptFromString:[NSString stringWithFormat:@"mraid._screensizeWidth = %.0f;", screenSize.width]];
    [webView stringByEvaluatingJavaScriptFromString:[NSString stringWithFormat:@"mraid._screensizeHeight = %.0f;", screenSize.height]];
    [webView stringByEvaluatingJavaScriptFromString:@"mraid._setState('default');"];
    [webView stringByEvaluatingJavaScriptFromString:@"mraid._sendReadyEvent();"];

    TFTBannerAd *from = self.show1 ? self.banner2 : self.banner1;
    TFTBannerAd *to = self.show1 ? self.banner1 :self.banner2;
    [to setFrame:CGRectMake(self.bounds.origin.x, self.bounds.origin.y + self.bounds.size.height, self.bounds.size.width, self.bounds.size.height)];
    [UIView animateWithDuration:0.75f
                          delay:0.0
                        options:UIViewAnimationOptionCurveLinear
                     animations:^{
                            [from setFrame:CGRectMake(self.bounds.origin.x, self.bounds.origin.y - self.bounds.size.height, self.bounds.size.width, self.bounds.size.height)];
                            [to setFrame:self.bounds];
                            [self addSubview:(self.show1 ? self.banner1 :self.banner2)];
                        }
                     completion:^(BOOL finished) {
                         [from removeFromSuperview];
                         self.show1 = !self.show1;
                     }];
    [self postReceivedAd];
    
    if (self.mraidController.needsToUnhideWebView) {
        [webView setHidden:NO];
        self.mraidController.needsToUnhideWebView = NO;
    }
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error {
    TFTErrorLog(@"Failed to load the webview.\n Error: %@\n userInfo: %@", error, [error userInfo]);
    [self postFailedToReceiveAd:@"Failed to load ad."];
}

#pragma mark - Delegate

- (void)postReceivedAd {
    if ([self.delegate respondsToSelector:@selector(tftBannerDidReceiveAd:)]) {
        [self.delegate tftBannerDidReceiveAd:self];
    }
}

- (void)postFailedToReceiveAd:(NSString *)reason {
    TFTErrorLog(@"%@", reason);
    if( [self.delegate respondsToSelector:@selector(tftBanner:didFail:)]) {
        [self.delegate tftBanner:self didFail:reason];
    }
}

- (void) setFrame:(CGRect)frame {
    [super setFrame:frame];
    self.banner1.frame = CGRectMake(0, 0, frame.size.width, frame.size.height);
    self.banner2.frame = CGRectMake(0, 0, frame.size.width, frame.size.height);
}

- (void) dealloc{
    TFTDebugLog(@"Deallocating Banner!");
    [self stopShowingAds];
    self.banner1 = nil;
    self.banner2 = nil;
    self.mraidController = nil;
}

@end
