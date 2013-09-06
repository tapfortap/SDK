//
//  TFTViewController.h
//  example-app
//
//  Created by Phil Laird on 2013-07-18.
//  Copyright (c) 2013 Tap for Tap. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TFTTapForTap.h"
#import "GADInterstitial.h"

@interface TFTViewController : UIViewController <TFTBannerDelegate, TFTInterstitialDelegate, TFTAppWallDelegate, GADInterstitialDelegate>
@property (retain, nonatomic) TFTInterstitial *interstitial;
@property (retain, nonatomic) TFTAppWall *appWall;
@property (retain, nonatomic) GADInterstitial *adMobInterstitial;
@end
