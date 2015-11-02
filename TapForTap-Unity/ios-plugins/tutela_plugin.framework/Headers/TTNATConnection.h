/**
         @file  TTNATConnection.h
         @section PROJECT
          iOS_TutelaNATSDK

         @author  Created by Brennen on 12-11-26.
         @section LICENSE
          Copyright (c) 2012 Tutela Technologies. All rights reserved.
 */

#import "TTNATConnectivityStatus.h"
#import <Foundation/Foundation.h>

/**
   A container class that stores the connection information from the database.
 */
@interface TTNATConnection : NSObject {
}
/**
   The connection type.
 */
@property (nonatomic, assign) TTNATConnectivityState connectionType;
/**
   The connection technology. Not used with WiFi.
 */
@property (nonatomic, assign) TTNATConnectionTechnology technology;
/**
   The connection option. Not used on iOS.
 */
@property (nonatomic, assign) int connectionOption;
/**
   The connection service provider. Not used with WiFi.
 */
@property (nonatomic, strong) NSString *serviceProvider;
/**
   The start of the connection, in UNIX time.
 */
@property (nonatomic, assign) long long startTime;
/**
   The end of the connection, in UNIX time.
 */
@property (nonatomic, assign) long long endTime;
/**
   The cellular Mobile Country Code, as defined by the SIM card. Not used with WiFi.
 */
@property (nonatomic, assign) int mcc;
/**
   The cellular Mobile Network Code, as defined by the SIM card. Not used with WiFi.
 */
@property (nonatomic, assign) int mnc;
/**
   The cell id of the connected tower. Not used on iOS.
 */
@property (nonatomic, assign) int cid;
/**
   The location area code of the connection. Not used on iOS.
 */
@property (nonatomic, assign) int lac;
/**
   The BSSID of the access point to which the device is connected. Only used with WiFi.
 */
@property (nonatomic, strong) NSString *bssid;
/**
   The SSID of the access point to which the device is connected. Only used with WiFi.
 */
@property (nonatomic, strong) NSString *ssid;
/**
   The hessid of the connected AP. Not used on iOS.
 */
@property (nonatomic, strong) NSString *hessid;
/**
   The time it takes the network to obtain an IP Address. Not used on iOS.
 */
@property (nonatomic, assign) int dhcpTime;
/**
   The time it takes the device to authenticate. Not used on iOS.
 */
@property (nonatomic, assign) int authenticationTime;
/**
   The current connection ID
 */
@property (nonatomic, assign) int connectionID;
/**
   The current timezone
 */
@property (nonatomic, assign) int timezone;

@end
