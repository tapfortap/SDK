//
//  TFTMediaBrixWrapper.h
//  TapForTap
//
//  Created by Bob Warwick on 2015-02-20.
//  Copyright (c) 2015 Tap for Tap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <TapForTap/TFTAdProvider.h>
#import "AdHandler.h"

@interface MediaBrixAdProvider : NSObject <TFTAdProvider, AdHandlerDelegate>
@property (retain) id<TFTInterstitialAdManager> delegate;
@property (retain) NSDictionary *params;
@property (strong, nonatomic) AdHandler *adHandler;
@property (retain, nonatomic) NSString *adTypeIdentifier;
@property (assign) NSInteger numberOfDidLoadsExpected; // MediaBrix automatically loads next.  Circumvent this.
@end
