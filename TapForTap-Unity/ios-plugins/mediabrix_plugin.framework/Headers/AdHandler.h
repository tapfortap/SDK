//
//  AdHandler.h
//
//  Created by Amos Elmaliah on 8/1/13
//  Copyright (c) 2013 MediaBrix inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "MediaBrix.h"

extern NSString *const AdHandlerStatusLoading;
extern NSString *const AdHandlerStatusShowing;
extern NSString *const AdHandlerStatusReady;
extern NSString *const AdHandlerStatusFailed;
extern NSString *const kMediaBrixFlex;
extern NSString *const kMediaBrixViews;
extern NSString *const kMediaBrixRewards;

@class AdHandlerAbstract;
@protocol AdHandlerDelegate <NSObject>
@optional
-(void)adHandler:(AdHandlerAbstract*)adHandler willChangeStatusForIdentifier:(NSString*)identifier;
-(void)adHandler:(AdHandlerAbstract*)adHandler didChangeStatusForIdentifier:(NSString*)identifier;

-(void)adHandler:(AdHandlerAbstract*)adHandler willLoadTargetIdentifier:(NSString*)adIdentifier;
-(void)adHandler:(AdHandlerAbstract*)adHandler didFinishLoadingAdWithIdenitifer:(NSString*)adIdentifier;
-(void)adHandler:(AdHandlerAbstract*)adHandler failedLoadingAdWithIdentifier:(NSString*)adIdentifier;
-(void)adHandler:(AdHandlerAbstract*)adHandler willShowAdWithIdentifier:(NSString*)adIdentifier;
-(void)adHandler:(AdHandlerAbstract*)adHandler didShowAdWithIdentifier:(NSString*)adIdentifier willReload:(BOOL)reload;
-(void)adHandler:(AdHandlerAbstract*)adHandler didReceiveRewardConfirmationForAdWithIdentifier:(NSString*)adIdentifier withAdData:(NSDictionary*)adData totalRewardsForThisAd:(NSUInteger)totalRewards;

@end

@interface AdHandlerAbstract : NSObject

-(void)reset;

-(void) unloadAdWithIdentifier:(NSString*)adIdentifier;

-(NSString*)statusForAdIdentifier:(NSString*)identifier;

-(void)loadAdWithIdentifier:(NSString *)identifier adData:(NSDictionary*)adData;

-(void)loadAdWithTarget:(NSDictionary *)target identifier:(NSString*)adIdentifier adData:(NSDictionary*)adData;

-(BOOL)canShowAdWithIdentifier:(NSString*)adIdentifier;

-(void)showAdWithIdentifier:(NSString *)identifier fromViewController:(UIViewController*)presentinViewContorller reloadWhenDone:(BOOL)reloadWhenDone;


@property (nonatomic, strong) NSArray* ads;
@property (nonatomic, strong) NSDictionary* defaultAdData;
@property (nonatomic, weak) id<AdHandlerDelegate>delegate;
@end

@interface AdHandler : AdHandlerAbstract
@end