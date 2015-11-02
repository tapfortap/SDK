/**
         @file  TTNATDevice.h
         @section PROJECT
          iOS_TutelaNATSDK

         @author  Created by Brennen on 12-11-26.
         @section LICENSE
          Copyright (c) 2012 Tutela Technologies. All rights reserved.
 */

#import <Foundation/Foundation.h>
/**
   A container class for storing the device information from the database.
 */
@interface TTNATDevice : NSObject {
}
/**
   The unique device id.
 */
@property (nonatomic, strong) NSString *uid;
/**
   The device manufacturer. This is Apple on iOS.
 */
@property (nonatomic, strong) NSString *manufacturer;
/**
   The device model.
 */
@property (nonatomic, strong) NSString *model;
/**
   The WiFi MAC address. No longer used on iOS.
 */
@property (nonatomic, strong) NSString *macAddress;
/**
   The device's operating system.
 */
@property (nonatomic, strong) NSString *operatingSystem;
/**
   The SDK version.
 */
@property (nonatomic, strong) NSString *sdkVersion;
/**
   The database version.
 */
@property (nonatomic, assign) int databaseVersion;
/**
   The device screen resolution (width, height in landscape mode), in points.
 */
@property (nonatomic, strong) NSString *screenResolution;
/**
   The total device memory, in bytes.
 */
@property (nonatomic, assign) unsigned long long totalMemory;
/**
   The total device disk storage, in bytes.
 */
@property (nonatomic, assign) unsigned long long totalDiskStorage;
/**
   The host app package name.
 */
@property (nonatomic, strong) NSString *hostAppPackageName;
/**
   The host app version.
 */
@property (nonatomic, strong) NSString *hostAppPackageVersion;

@end
