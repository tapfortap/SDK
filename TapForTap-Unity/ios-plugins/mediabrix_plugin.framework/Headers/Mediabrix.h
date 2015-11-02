//
//  MediaBrix.h
//  Bird Hop
//
//  Created by Amos Elmaliah on 10/16/12.
//  Copyright (c) 2013 MediaBrix inc. All rights reserved.
//
//



#import <Foundation/Foundation.h>
#import <SystemConfiguration/SystemConfiguration.h>
#import <MobileCoreServices/MobileCoreServices.h>
#import <CoreTelephony/CoreTelephonyDefines.h>
#import <UIKit/UIKit.h>




#define MEDIABRIX_1_5_5 [[Mediabrix version] hasPrefix:@"v1.5"]
#define MediaBrixSDK_MBUtils_h

// notifications:
extern NSString* const kMediaBrixAdWillLoadNotification;
extern NSString* const kMediaBrixAdDidLoadNotification;
extern NSString* const kMediaBrixAdFailedNotification;
extern NSString* const kMediaBrixAdReadyNotification;
extern NSString* const kMediaBrixAdShowNotification;
extern NSString* const kMediaBrixAdDidCloseNotification;
extern NSString* const kMediaBrixAdRewardNotification;

extern NSString * const kMediaBrixFlex;
extern NSString * const kMediaBrixViews;
extern NSString * const kMediaBrixRewards;

extern NSString * const kMediabrixTargetAdTypeKey;
extern NSString * const kMediabrixTargetPropertyKey;
extern NSString * const kMediabrixTargetZoneKey;

@protocol MediaBrixAdViewController <NSObject>

- (void)showInViewController:(UIViewController *)controller;

@property (retain, nonatomic) NSDictionary *adData;
@property (retain, nonatomic, readonly) NSDictionary *target;

@end

@protocol MediaBrixUserDefaults <NSObject>
@required

- (NSURL*)baseURL;
- (NSString*)appID;
- (NSString*)property;
- (NSDictionary*)defaultAdData;

@end

@interface MediaBrix : NSObject

+ (void) setUserDefaultsClass:(Class)userDefaultsClass;

+ (NSObject<MediaBrixUserDefaults>*)userDefaults;

+ (MediaBrix*) sharedInstance;


- (NSDictionary*)targetForAdType:(NSString*)adType zone:(NSString*)zone;

- (void) loadAdWithTarget:(NSDictionary*)target;

-(void)updateMediaBrixIntenralAdData:(NSDictionary*)adData;

- (NSString*) adTypeForController:(UIViewController<MediaBrixAdViewController>*)controller;
- (NSString*) adTypeForAd:(id)ad;
- (NSString*) adTypeForTarget:(NSDictionary *)target;

+ (NSString*)version;

@property (nonatomic,strong) NSMutableDictionary * mbSocialDictionary;

@end

#ifndef _SYSTEMCONFIGURATION_H
#error "The SystemConfiguration framework not found in project or not included in precompiled header, please make sure that it does"
#endif

#ifndef __UTTYPE__
#error "The MobileCoreServices framework not found in project or not included in precompiled header, please make sure that it does"
#endif

#ifndef CORETELEPHONY_EXTERN
#error "The CoreTelephony framework not found in project or not included in precompiled header, please make sure that it does"
#endif
