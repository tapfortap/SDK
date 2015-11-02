/**
         @file  TTNATConstants.h
         @section PROJECT
          iOS_TutelaNATSDK

         @author  Created by Steven Gillan on 2013-04-18.
         @section LICENSE
          Copyright (c) 2013 Tutela Technologies. All rights reserved.
 */

/**
   The default export frequency, in minutes.
 */
#define kTTNATDefaultExportFrequency 1440
/**
   The default periodic server response test frequency, in seconds.
 */
#define kTTNATDefaultServerResponseTestFrequency 60
/**
   The minimum periodic server response test frequency, in seconds.
 */
#define kTTNATMinimumServerResponseTestFrequency 30
/**
   The default periodic frequency test frequency, in seconds.
 */
#define kTTNATDefaultThroughputTestFrequency 5 * 60
/**
   The minimum periodic frequency test frequency, in seconds.
 */
#define kTTNATMinimumThroughputTestFrequency 2 * 60
/**
   The default data soft limit, in bytes.
 */
#define kTTNATDefaultSoftByteLimit 5L * 1024L * 1024L
/**
   The default data hard limit, in bytes.
 */
#define kTTNATDefaultHardByteLimit 8L * 1024L * 1024L
/**
   The default location update distance, in meters.
 */
#define kTTNATDefaultLocationUpdateDistance 30L
/**
   The minimum location update distance, in meters.
 */
#define kTTNATMinimumLocationUpdateDistance 5L
/**
   The default location update time, in seconds.
 */
#define kTTNATDefaultLocationUpdateTime 20L
/**
   The minimum location update time, in seconds.
 */
#define kTTNATMinimumLocationUpdateTime 10L
/**
   The default heading filter, in degrees.
 */
#define kTTNATDefaultHeadingFilter 5
/**
   The minimum heading filter, in degrees.
 */
#define kTTNATMinimumHeadingFilter 0
/**
   The maximum heading filter, in degrees.
 */
#define kTTNATMaximumHeadingFilter 180
/**
   The Tutela NAT SDK version.
 */
#define kTTNATSdkVersion @"3.10.10"
/**
   The Tutela NAT SDK database version.
 */
#define kTTNATDbVersion 6
/**
   The Tutela NAT SDK notification status key.
 */
#define kTTNATSDKNotificationStatusKey @"status"
/**
   The Tutela NAT SDK notification pass status.
 */
#define kTTNATSDKPassStatus @"pass"
/**
   The Tutela NAT SDK notification fail status.
 */
#define kTTNATSDKFailStatus @"fail"
/**
   The Tutela NAT SDK database file size limit notification key.
 */
#define kTTNATSDKDBFileSizeLimitKey @"limit"
/**
   The Tutela NAT SDK soft file size limit notification.
 */
#define kTTNATSDKDBFileSizeSoftLimit @"softLimit"
/**
   The Tutela NAT SDK hard file size limit key notification.
 */
#define kTTNATSDKDBFileSizeHardLimit @"hardLimit"
