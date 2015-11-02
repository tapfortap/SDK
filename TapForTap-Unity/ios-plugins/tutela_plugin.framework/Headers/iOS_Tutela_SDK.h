/**
   @file iOS_Tutela_SDK.h
   @section PROJECT
   iOS_Tutela_SDK

   @author Created by Brennen on 12/9/2013.
   @section LICENSE
   Copyright (c) 2014 Tutela Technologies. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface iOS_Tutela_SDK : NSObject

#pragma mark - Registration Methods

/**
   Notification that a registration/API key check failed.
   (In case of success, a subsequent deployment key check will be made automatically; see the relevant SDK (e.g., NAT, MAT) for details.)
 */
    extern NSString * const kTTKeyCheckFailed;
/**
   Set the default registration key to be used if the user does not supply a registration key.
   @param registrationKey
   The default registration key.
 */
+ (void) setDefaultRegistrationKey:(NSString *)registrationKey;
/**
   Inform the Tutela SDK that the client application has started with a previously-set, non-nil registration key.

   The Tutela SDK will then prompt the user for a registration key to obtain the corresponding deployment key.
   If the controller is nil, the default registration key will be used to obtain the corresponding deployment key.
   (This deployment key will be cached and used by future calls to this method, to minimize user interaction.)
   The deployment key will be used initialize the components authorized by this deployment key.

   This method must be called from the main thread.
   setDefaultRegistrationKey must be called PRIOR to calling this method, to supply the SDK with a default registration key.
   If custom DSC certificates are used, verifyDSCUsingCertificate:anchors: must also be called PRIOR to calling this method.

   @param controller
   The view controller to use for user interaction.
 */
+ (void) applicationStartedWithController:(UIViewController *)controller;
/**
   Inform the Tutela SDK that the client application has started with a given API key.
   The Tutela SDK will then initialize the components authorized by this API key.

   This method must be called from the main thread.
   If custom DSC certificates are used, verifyDSCUsingCertificate:anchors: must also be called PRIOR to calling this method.

   @param apiKey
   The application API key. This must not be nil.
   @param referrer
   The referrer. This must not be nil.
 */
+ (void) applicationStartedWithAPIKey:(NSString *)apiKey referrer:(NSString *)referrer;
/**
   Inform the Tutela SDK that the client application has started with a given deployment key.
   The Tutela SDK will then initialize the components authorized by this deployment key.

   This method must be called from the main thread.
   If custom DSC certificates are used, verifyDSCUsingCertificate:anchors: must also be called PRIOR to calling this method.

   @param deploymentKey
   The application deployment key. This must not be nil.
 */
+ (void) applicationStartedWithDeploymentKey:(NSString *)deploymentKey;
/**
   Inform the Tutela SDK that the client application has started with a given deployment key.
   The Tutela SDK will then initialize the components authorized by this deployment key.

   This method must be called from the main thread.
   If custom DSC certificates are used, verifyDSCUsingCertificate:anchors: must also be called PRIOR to calling this method.

   @param deploymentKey
   The application deployment key. This must not be nil..
   @param controller
   The view controller to use for user interaction, or nil, if not required.
 */
+ (void) applicationStartedWithDeploymentKey:(NSString *)deploymentKey controller:(UIViewController *)controller;

#pragma mark - APNS/DSC Methods
/**
   Verify DSC data using a DER-encoded X.509 certificate. The certificate must use the SHA-256 signature algorithm.

   @param certificate
   The certificate
   @param anchors
   The anchor certificates. These must form a continuous chain from the certificate to the root.
   @return
   YES if verification will be attempted, NO otherwise.
 */
+ (BOOL) verifyDSCUsingCertificate:(NSData *)certificate anchors:(NSArray *)anchors;
/**
   Clear the app icon badge
 */
+ (void) clearBadge;
/**
   Report the device token to the push provider. Be sure to call this in application:(UIApplication *)app didRegisterForRemoteNotificationsWithDeviceToken:
   @param deviceToken
   The device token
 */
+ (void) reportDeviceToken:(NSData *)deviceToken;
/**
   Report a new notification to the TUPushNotifications singleton.
   Note that due to iOS time constraints in the background, DSC configurations will not be downloaded and applied until the app runs in the foreground.

   @param newNotification
   The new APNs notification.
   @param flag
   Whether or not to preserve the existing app icon badge value
 */
+ (void) reportNotification:(NSDictionary *)newNotification preserveIconBadgeValue:(BOOL)flag;
/**
   Report a new notification to the TUPushNotifications singleton.
   Note that due to iOS time constraints in the background, DSC configurations will not be downloaded and applied until the app runs in the foreground.

   @param newNotification
   The new APNs notification.
   @param flag
   Whether or not to preserve the existing app icon badge value
   @param completionHandler
   The completion handler to run after the notification has been processed (but before the configuration has been downloaded)
 */
+ (void) reportNotification:(NSDictionary *)newNotification preserveIconBadgeValue:(BOOL)flag fetchCompletionHandler:( void (^)(UIBackgroundFetchResult) )completionHandler;
/**
   Report a new notification to the TUPushNotifications singleton.
   Note that due to iOS time constraints in the background, DSC configurations will not be downloaded and applied until the app runs in the foreground.

   @param newNotification
   The new APNs notification.
   @param flag
   Whether or not to preserve the existing app icon badge value
   @param completionHandler
   The completion handler to run after the notification has been processed (but before the configuration has been downloaded)
 */
+ (void) reportNotification:(NSDictionary *)newNotification preserveIconBadgeValue:(BOOL)flag completionHandler:( void (^)() )completionHandler;

#pragma mark - Upload Methods
/**
   Upload to HTTPS only if a particular chain of trust holds

   @param anchors
   The anchor certificates. These must form a continuous chain from the certificate to the root.
   If this is nil, NO certificate pinning will be done on upload
   @param certificate
   The leaf certificate to use.
 */
+ (void) uploadUsingAnchors:(NSArray *)anchors leafCertificate:(NSData *)certificate;

@end
