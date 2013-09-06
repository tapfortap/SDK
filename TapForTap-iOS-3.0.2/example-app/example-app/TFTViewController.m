//
//  TFTViewController.m
//  example-app
//
//  Created by Phil Laird on 2013-07-18.
//  Copyright (c) 2013 Tap for Tap. All rights reserved.
//

#import "TFTViewController.h"
#import "TFTTapForTap.h"
#import "GADBannerView.h"
#import "GADRequest.h"
#import "GADInterstitial.h"

@implementation TFTViewController

- (void)viewDidLoad
{
    int width = self.view.frame.size.width;
    
    TFTBanner* banner = [TFTBanner bannerWithFrame:CGRectMake(width / 2 - 320 / 2, 0, 320, 50) delegate:self];
    
    GADBannerView *adMobBanner = [[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner];
    adMobBanner.frame = CGRectMake(width / 2 - 320 / 2, 55, 320, 50);
    adMobBanner.adUnitID = @"ca-app-pub-6233315881842046/8855778216";
    adMobBanner.rootViewController = self;
    GADRequest *request = [GADRequest request];
    [adMobBanner loadRequest:request];
    [self.view addSubview:adMobBanner];
    
    UIButton* showInterstitialButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [showInterstitialButton addTarget:self action:@selector(showInterstitial) forControlEvents:UIControlEventTouchUpInside];
    [showInterstitialButton setTitle:@"Show Interstitial" forState:UIControlStateNormal];
    showInterstitialButton.frame = CGRectMake(width / 2 - 200 / 2, 110, 200, 75);
    self.interstitial = [TFTInterstitial interstitialWithDelegate:self];
    
    UIButton* showAppWallButton =[UIButton buttonWithType:UIButtonTypeRoundedRect];
    [showAppWallButton addTarget:self action:@selector(showAppWall) forControlEvents:UIControlEventTouchUpInside];
    [showAppWallButton setTitle:@"Show App Wall" forState:UIControlStateNormal];
    showAppWallButton.frame = CGRectMake(width / 2 - 200 / 2, 210, 200, 75);
    self.appWall = [TFTAppWall appWallWithDelegate:self];
    
    UIButton* showAdMobInterstitialButton =[UIButton buttonWithType:UIButtonTypeRoundedRect];
    [showAdMobInterstitialButton addTarget:self action:@selector(showAdMobInterstitial) forControlEvents:UIControlEventTouchUpInside];
    [showAdMobInterstitialButton setTitle:@"Show Ad Mob Interstitial" forState:UIControlStateNormal];
    showAdMobInterstitialButton.frame = CGRectMake(width / 2 - 200 / 2, 310, 200, 75);
    self.appWall = [TFTAppWall appWallWithDelegate:self];
    

    [self.view addSubview:banner];
    [self.view addSubview:showAppWallButton];
    [self.view addSubview:showInterstitialButton];
    [self.view addSubview:showAdMobInterstitialButton];
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void) showInterstitial {
    [self.interstitial showAndLoadWithViewController:self];
}

- (void) showAppWall {
    [self.appWall showWithViewController:self];
}

- (void) showAdMobInterstitial {
    self.adMobInterstitial = [[GADInterstitial alloc] init];
    self.adMobInterstitial.adUnitID = @"ca-app-pub-6233315881842046/1332511417";
    self.adMobInterstitial.delegate = self;
    GADRequest *request = [GADRequest request];
    [self.adMobInterstitial loadRequest:request];
}

- (void)tftBannerDidReceive:(TFTBanner *)banner {
    NSLog(@"tftBannerAdDidReceiveAd");
}

- (void)tftBannerAd:(TFTBanner *)banner didFail:(NSString *)reason {
    NSLog(@"tftBannerAd:didFail");
    
}

- (void)tftBannerAdWasTapped:(TFTBanner *)banner {
    NSLog(@"tftBannerAdWasTapped");
}


- (void)tftInterstitialDidReceiveAd:(TFTInterstitial *)interstitial {
    NSLog(@"tftInterstitialDidReceiveAd");
}

- (void)tftInterstitial:(TFTInterstitial *)interstitial didFail:(NSString *)reason {
    NSLog(@"tftInterstitial");
}

- (void)tftInterstitialDidShow:(TFTInterstitial *)interstitial {
    NSLog(@"tftInterstitialDidShow");
}

- (void)tftInterstitialWasTapped:(TFTInterstitial *)interstitial {
    NSLog(@"tftInterstitialWasTapped");
}

- (void)tftInterstitialWasDismissed:(TFTInterstitial *)interstitial {
    NSLog(@"tftInterstitialWasDismissed");
}


- (void)tftAppWallDidReceiveAd:(TFTAppWall *)appWall {
    NSLog(@"tftAppWallDidReceiveAd");
}

- (void)tftAppWall:(TFTAppWall *)appWall didFail:(NSString *)reason {
    NSLog(@"tftAppWall:didFail");
}

- (void)tftAppWallDidShow:(TFTAppWall *)appWall {
    NSLog(@"tftAppWallDidShow");
}

- (void)tftAppWallWasTapped:(TFTAppWall *)appWall {
    NSLog(@"tftAppWallWasTapped");
}

- (void)tftAppWallWasDismissed:(TFTAppWall *)appWall {
    NSLog(@"tftAppWallWasDismissed");
}

- (void)interstitialDidReceiveAd:(GADInterstitial *)ad {
    [self.adMobInterstitial presentFromRootViewController:self];
}

@end
