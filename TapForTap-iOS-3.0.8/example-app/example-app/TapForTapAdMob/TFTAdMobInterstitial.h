//
//  Copyright (c) 2013 Tap for Tap. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "GADCustomEventInterstitial.h"

#import "TFTTapForTap.h"

@interface TFTAdMobInterstitial : NSObject <GADCustomEventInterstitial, TFTInterstitialDelegate>
@property (nonatomic, assign) id<GADCustomEventInterstitialDelegate> delegate;
@property (nonatomic, retain) TFTInterstitial *interstitial;
- (void)log;
@end
