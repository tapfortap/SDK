//
//  Copyright (c) 2013 Tap for Tap. All rights reserved.
//

#import "TFTInterstitial.h"

#import "TFTFullScreenAd.h"
#import "TFTBreakAd.h"
#import "TFTRescueAd.h"
#import "TFTRewardAd.h"
#import "TFTLog.h"
#import "TFTUserInfo.h"

static NSString *const INTERSTITIAL_PATH = @"ad/interstitial";

@interface TFTInterstitial () <TFTFullScreenAdDelegate>

@property (retain, nonatomic) id<TFTInterstitialAdManager> ad;
@property (weak, nonatomic) id<TFTInterstitialDelegate> delegate;

@property (copy) void (^receivedAdBlock) (TFTInterstitial *);
@property (copy) void (^failedAdBlock) (TFTInterstitial *, NSString *);
@property (copy) void (^shownAdBlock) (TFTInterstitial *);
@property (copy) void (^tappedAdBlock) (TFTInterstitial *);
@property (copy) void (^dismissedAdBlock) (TFTInterstitial *);
@property (copy) void (^rewardedAdBlock) (TFTInterstitial *);

@property (readwrite) BOOL unitTesting;

@end

@implementation TFTInterstitial

#pragma mark - Initialization

+ (TFTInterstitial *)interstitial {
    TFTInterstitial *interstitialAd = [[TFTInterstitial alloc] init];
    [interstitialAd load];
    return interstitialAd;
}

+ (TFTInterstitial *)interstitialWithDelegate:(id<TFTInterstitialDelegate>)delegate {
    TFTInterstitial *interstitialAd = [[TFTInterstitial alloc] initWithDelegate:delegate];
    [interstitialAd load];
    return interstitialAd;
}

- (id)init {
    return [self initWithDelegate: nil];
}

- (id)initWithDelegate:(id<TFTInterstitialDelegate>)delegate {
    self = [super init];
    if (self) {
        _ad = [[TFTFullScreenAd alloc] initWithType:@"interstitial" path:INTERSTITIAL_PATH delegate:self];
        _delegate = delegate;
        _unitTesting = NO;
    }
    return self;
}

#pragma mark - Delegate Based Convenience Methods

+ (TFTInterstitial *)loadBreakInterstitialWithDelegate:(id<TFTInterstitialDelegate>)delegate {
    
    TFTInterstitial *interstitialAd = [[TFTInterstitial alloc] initWithDelegate:delegate];
    interstitialAd.ad = [[TFTBreakAd alloc] initWithDelegate:interstitialAd];
    TFTDebugLog(@"Params = %@", [interstitialAd ad].params);
    [[interstitialAd ad].params setObject:@"break" forKey:@"adContext"];
    if([TFTUserInfo getLocation] != nil) [[interstitialAd ad].params setObject:@"YES" forKey:@"allowLocation"];
    if([TFTUserInfo getUserAccountID] != nil) [[interstitialAd ad].params setObject:[TFTUserInfo getUserAccountID] forKey:@"uid"];
    [interstitialAd _load];
    
    return interstitialAd;
    
}

+ (TFTInterstitial *)loadRescueInterstitialWithTitle: (NSString *)title
                                        brandingText: (NSString *)branding
                                      enticementText: (NSString *)enticement
                                   rewardDescription: (NSString *)rewardDescription
                                          rewardIcon: (UIImage *)icon
                                     optInButtonText: (NSString *)optInText
                                            delegate:(id<TFTInterstitialDelegate>)delegate {
    
    TFTInterstitial *interstitialAd = [[TFTInterstitial alloc] initWithDelegate:delegate];
    interstitialAd.ad = [[TFTRescueAd alloc] initWithDelegate:interstitialAd];
    [[interstitialAd ad].params setObject:@"rescue" forKey:@"adContext"];
    [[interstitialAd ad].params setObject:title forKey:@"rescueTitle"];
    [[interstitialAd ad].params setObject:branding forKey:@"rescueBranding"];
    [[interstitialAd ad].params setObject:enticement forKey:@"rescueEnticement"];
    [[interstitialAd ad].params setObject:rewardDescription forKey:@"rescueRewardDescription"];
    [[interstitialAd ad].params setObject:icon forKey:@"rescueRewardIcon"];
    [[interstitialAd ad].params setObject:optInText forKey:@"rescueOptInText"];
    if([TFTUserInfo getLocation] != nil) [[interstitialAd ad].params setObject:@"YES" forKey:@"allowLocation"];
    if([TFTUserInfo getUserAccountID] != nil) [[interstitialAd ad].params setObject:[TFTUserInfo getUserAccountID] forKey:@"uid"];
    [interstitialAd _load];
    
    return interstitialAd;
    
}

+ (TFTInterstitial *)loadAchievementInterstitialWithDescription: (NSString *)description
                                              rewardDescription: (NSString *)rewardDescription
                                                     rewardIcon: (UIImage *)icon
                                                       delegate:(id<TFTInterstitialDelegate>)delegate {
    
    TFTInterstitial *interstitialAd = [[TFTInterstitial alloc] initWithDelegate:delegate];
    interstitialAd.ad = [[TFTRewardAd alloc] initWithDelegate:interstitialAd];
    [[interstitialAd ad].params setObject:@"achievement" forKey:@"adContext"];
    [[interstitialAd ad].params setObject:description forKey:@"achievementDescription"];
    [[interstitialAd ad].params setObject:rewardDescription forKey:@"achievementRewardDescription"];
    [[interstitialAd ad].params setObject:icon forKey:@"achievementRewardIcon"];
    if([TFTUserInfo getLocation] != nil) [[interstitialAd ad].params setObject:@"YES" forKey:@"allowLocation"];
    if([TFTUserInfo getUserAccountID] != nil) [[interstitialAd ad].params setObject:[TFTUserInfo getUserAccountID] forKey:@"uid"];
    [interstitialAd _load];
    
    return interstitialAd;
    
}

#pragma mark - Block Based Convenience Methods

+ (TFTInterstitial *)loadBreakInterstitialWithCallbackOnReceivedAd: (void (^)(TFTInterstitial *interstitial))receivedAdBlock
                                                       onAdDidFail: (void (^)(TFTInterstitial *interstitial, NSString *reason))failedAdBlock
                                                       onAdDidShow: (void (^)(TFTInterstitial *interstitial))shownAdBlock
                                                     onAdWasTapped: (void (^)(TFTInterstitial *interstitial))tappedAdBlock
                                                  onAdWasDismissed: (void (^)(TFTInterstitial *interstitial))dismissedAdBlock
{
    
    TFTInterstitial *interstitialAd = [[TFTInterstitial alloc] init];
    interstitialAd.receivedAdBlock = receivedAdBlock;
    interstitialAd.failedAdBlock = failedAdBlock;
    interstitialAd.shownAdBlock = shownAdBlock;
    interstitialAd.tappedAdBlock = tappedAdBlock;
    interstitialAd.dismissedAdBlock = dismissedAdBlock;
    interstitialAd.delegate = interstitialAd; // Set the ad itself as it's delegate.  We use this to catch the delegate methods and send them to blocks
    
    interstitialAd.ad = [[TFTBreakAd alloc] initWithDelegate:interstitialAd];
    [[interstitialAd ad].params setObject:@"break" forKey:@"adContext"];
    if([TFTUserInfo getLocation] != nil) [[interstitialAd ad].params setObject:@"YES" forKey:@"allowLocation"];
    if([TFTUserInfo getUserAccountID] != nil) [[interstitialAd ad].params setObject:[TFTUserInfo getUserAccountID] forKey:@"uid"];
    [interstitialAd _load];
    
    return interstitialAd;
    
}

+ (TFTInterstitial *)loadRescueInterstitialWithTitle: (NSString *)title
                                        brandingText: (NSString *)branding
                                      enticementText: (NSString *)enticement
                                   rewardDescription: (NSString *)rewardDescription
                                          rewardIcon: (UIImage *)icon
                                     optInButtonText: (NSString *)optInText
                                        onReceivedAd: (void (^)(TFTInterstitial *interstitial))receivedAdBlock
                                         onAdDidFail: (void (^)(TFTInterstitial *interstitial, NSString *reason))failedAdBlock
                                         onAdDidShow: (void (^)(TFTInterstitial *interstitial))shownAdBlock
                                       onAdWasTapped: (void (^)(TFTInterstitial *interstitial))tappedAdBlock
                                    onAdWasDismissed: (void (^)(TFTInterstitial *interstitial))dismissedAdBlock
                                     onAdWasRewarded: (void (^)(TFTInterstitial *interstitial))rewardedAdBlock
{
    TFTInterstitial *interstitialAd = [[TFTInterstitial alloc] init];
    interstitialAd.receivedAdBlock = receivedAdBlock;
    interstitialAd.failedAdBlock = failedAdBlock;
    interstitialAd.shownAdBlock = shownAdBlock;
    interstitialAd.tappedAdBlock = tappedAdBlock;
    interstitialAd.dismissedAdBlock = dismissedAdBlock;
    interstitialAd.rewardedAdBlock = rewardedAdBlock;
    interstitialAd.delegate = interstitialAd; // Set the ad itself as it's delegate.  We use this to catch the delegate methods and send them to blocks
    
    interstitialAd.ad = [[TFTRescueAd alloc] initWithDelegate:interstitialAd];
    [[interstitialAd ad].params setObject:@"rescue" forKey:@"adContext"];
    [[interstitialAd ad].params setObject:title forKey:@"rescueTitle"];
    [[interstitialAd ad].params setObject:branding forKey:@"rescueBranding"];
    [[interstitialAd ad].params setObject:enticement forKey:@"rescueEnticement"];
    [[interstitialAd ad].params setObject:rewardDescription forKey:@"rescueRewardDescription"];
    [[interstitialAd ad].params setObject:icon forKey:@"rescueRewardIcon"];
    [[interstitialAd ad].params setObject:optInText forKey:@"rescueOptInText"];
    if([TFTUserInfo getLocation] != nil) [[interstitialAd ad].params setObject:@"YES" forKey:@"allowLocation"];
    if([TFTUserInfo getUserAccountID] != nil) [[interstitialAd ad].params setObject:[TFTUserInfo getUserAccountID] forKey:@"uid"];
    [interstitialAd _load];
    
    return interstitialAd;
    
}

+ (TFTInterstitial *)loadAchievementInterstitialWithDescription: (NSString *)description
                                              rewardDescription: (NSString *)rewardDescription
                                                     rewardIcon: (UIImage *)icon
                                                   onReceivedAd: (void (^)(TFTInterstitial *interstitial))receivedAdBlock
                                                    onAdDidFail: (void (^)(TFTInterstitial *interstitial, NSString *reason))failedAdBlock
                                                    onAdDidShow: (void (^)(TFTInterstitial *interstitial))shownAdBlock
                                                  onAdWasTapped: (void (^)(TFTInterstitial *interstitial))tappedAdBlock
                                               onAdWasDismissed: (void (^)(TFTInterstitial *interstitial))dismissedAdBlock{
    
    TFTInterstitial *interstitialAd = [[TFTInterstitial alloc] init];
    interstitialAd.receivedAdBlock = receivedAdBlock;
    interstitialAd.failedAdBlock = failedAdBlock;
    interstitialAd.shownAdBlock = shownAdBlock;
    interstitialAd.tappedAdBlock = tappedAdBlock;
    interstitialAd.dismissedAdBlock = dismissedAdBlock;
    interstitialAd.delegate = interstitialAd; // Set the ad itself as it's delegate.  We use this to catch the delegate methods and send them to blocks
    
    interstitialAd.ad = [[TFTRewardAd alloc] initWithDelegate:interstitialAd];
    [[interstitialAd ad].params setObject:@"achievement" forKey:@"adContext"];
    [[interstitialAd ad].params setObject:description forKey:@"achievementDescription"];
    [[interstitialAd ad].params setObject:rewardDescription forKey:@"achievementRewardDescription"];
    [[interstitialAd ad].params setObject:icon forKey:@"achievementRewardIcon"];
    if([TFTUserInfo getLocation] != nil) [[interstitialAd ad].params setObject:@"YES" forKey:@"allowLocation"];
    if([TFTUserInfo getUserAccountID] != nil) [[interstitialAd ad].params setObject:[TFTUserInfo getUserAccountID] forKey:@"uid"];
    [interstitialAd _load];
    
    return interstitialAd;
    
}

#pragma mark - Life Cycle

- (void) load {
    [self _load];
}

- (void) _load {
    
    if (self.unitTesting) { // If we're doing unit tests, we'd rather not start up the whole loading process
        return;
    }
    
    [self.ad load];
    
}

- (void) showWithViewController:(UIViewController *) viewController {
    [self.ad showWithViewController:viewController];
}

- (void)showAndLoadWithViewController:(UIViewController *)viewController {
    [self.ad showAndLoadNextWithViewController:viewController];
}

- (BOOL) readyToShow {
    return self.ad.readyToShow;
}

#pragma mark - Delegate

- (void)tftProviderDidReceiveAd {
    if([self.delegate respondsToSelector:@selector(tftInterstitialDidReceiveAd:)]) {
        [self.delegate tftInterstitialDidReceiveAd:self];
    }
}

- (void)tftProviderDidFailToReceiveAdWithReason:(NSString *)reason {
    if([self.delegate respondsToSelector:@selector(tftInterstitial:didFail:)]) {
        [self.delegate tftInterstitial:self didFail:reason];
    }
}

- (void)tftProviderAdDidShow {
    if([self.delegate respondsToSelector:@selector(tftInterstitialDidShow:)]) {
        [self.delegate tftInterstitialDidShow:self];
    }
}

- (void)tftProviderAdWasTapped {
    if([self.delegate respondsToSelector:@selector(tftInterstitialWasTapped:)]) {
        [self.delegate tftInterstitialWasTapped:self];
    }
}

- (void)tftProviderAdWasDismissed {
    if([self.delegate respondsToSelector:@selector(tftInterstitialWasDismissed:)]) {
        [self.delegate tftInterstitialWasDismissed:self];
    }
}

- (void)tftProviderAdWasRewarded {
    if([self.delegate respondsToSelector:@selector(tftInterstitialWasRewarded:)]) {
        [self.delegate tftInterstitialWasRewarded:self];
    }
}

#pragma mark Internal Delegate for Blocks

- (void)tftInterstitialDidReceiveAd:(TFTInterstitial *)interstitial {
    if (self.receivedAdBlock != nil) {
        self.receivedAdBlock(interstitial);
    }
}

- (void)tftInterstitial:(TFTInterstitial *)interstitial didFail:(NSString *)reason {
    if (self.failedAdBlock != nil) {
        self.failedAdBlock(interstitial, reason);
    }
}

- (void)tftInterstitialDidShow:(TFTInterstitial *)interstitial {
    if (self.shownAdBlock != nil) {
        self.shownAdBlock(interstitial);
    }
}

- (void)tftInterstitialWasTapped:(TFTInterstitial *)interstitial {
    if (self.tappedAdBlock != nil) {
        self.tappedAdBlock(interstitial);
    }
}

- (void)tftInterstitialWasDismissed:(TFTInterstitial *)interstitial {
    if (self.dismissedAdBlock != nil) {
        self.dismissedAdBlock(interstitial);
    }
}

- (void)tftInterstitialWasRewarded:(TFTInterstitial *)interstitial {
    if (self.rewardedAdBlock != nil) {
        self.rewardedAdBlock(interstitial);
    }
}

@end
