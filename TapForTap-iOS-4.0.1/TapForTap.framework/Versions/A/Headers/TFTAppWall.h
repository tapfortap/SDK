//
//  Copyright (c) 2013 Tap for Tap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class TFTAppWall;

@protocol TFTAppWallDelegate <NSObject>
@optional
- (void)tftAppWallDidReceiveAd:(TFTAppWall *)appWall __attribute__((deprecated));
- (void)tftAppWall:(TFTAppWall *)appWall didFail:(NSString *)reason __attribute__((deprecated));
- (void)tftAppWallDidShow:(TFTAppWall *)appWall __attribute__((deprecated));
- (void)tftAppWallWasTapped:(TFTAppWall *)appWall __attribute__((deprecated));
- (void)tftAppWallWasDismissed:(TFTAppWall *)appWall __attribute__((deprecated));
@end

@interface TFTAppWall : NSObject
- (void)load __attribute__((deprecated));
- (void)showWithViewController:(UIViewController *)viewController __attribute__((deprecated));
- (void)showAndLoadWithViewController:(UIViewController *)viewController __attribute__((deprecated));
- (BOOL)readyToShow __attribute__((deprecated));

+ (TFTAppWall *) appWall __attribute__((deprecated));
+ (TFTAppWall *) appWallWithDelegate:(id<TFTAppWallDelegate>) delegate __attribute__((deprecated));
@end
