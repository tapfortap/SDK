//
//  Copyright (c) 2013 Tap for Tap. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "GADCustomEventBanner.h"

#import "TFTTapForTap.h"

@interface TFTAdMobBanner : NSObject <GADCustomEventBanner, TFTBannerDelegate>
@property (nonatomic, assign) id<GADCustomEventBannerDelegate> delegate;
@property (nonatomic, retain) TFTBanner *banner;

- (void)log;
@end
