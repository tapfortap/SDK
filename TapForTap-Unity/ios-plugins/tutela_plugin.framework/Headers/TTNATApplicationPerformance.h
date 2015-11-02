/**
   @file  TTNATApplicationPerformance.h
   @section PROJECT
   iOS_TutelaNATSDK

   @author  Created by Michael Horie on 2015-01-23.
   @section LICENSE
   Copyright (c) 2015 Tutela Technologies. All rights reserved.
 */

#ifndef iOS_TutelaNATSDK_TTNATApplicationPerformance_h
#define iOS_TutelaNATSDK_TTNATApplicationPerformance_h

#import <Foundation/Foundation.h>

/**
   A class for tracking application performance.

   Example 1: Recording the start of a connection
   TTNATApplicationPerformance *appPerformance = [TTNATApplicationPerformance connectionStart:\@"http://videostreaming.tutelatechnologies.com/vod/Big_Buck_Bunny/smil:Big_Buck_Bunny/bigbuckbunnyiphone.smil/playlist.m3u8" contentType:\@"application/x-mpegURL" transferType:TTNATTAPStreaming tag:\@"AV Kit Player"];

   Example 2A: Recording the successful end of a connection
   [appPerformance connectionCompleted];

   Example 2B: Recording a failed connection
   [appPerformance connectionFailed];

   Example 2C: Recording a timed-out connection
   [appPerformance connectionTimedOut];

   Example 2D: Recording a cancelled connection
   [appPerformance connectionCancelled];

   Note that every started connection (Example 1) requires one, and only one, matching ending connection call (Examples 2A - 2D). Calling multiple ending connection calls will result in only the first ending call to be applied; subsequent calls are ignored.
 */
@interface TTNATApplicationPerformance : NSObject

/**
   List of the possible transfer types.
 */
    typedef enum {
    TTNATTAPDownload = 0,    ///<  Downloads
    TTNATTAPUpload = 1,      ///<  Uploads
    TTNATTAPStreaming = 2    ///<  Streaming
} TTNATTAPTransferType;

/**
   Indicates that a connection has started.
   @param contentURL
   The URL
   @param contentType
   The content type
   @param transferType
   The transfer type
   @param tag
   The tag
   @return
   A reference to an active connection instance, or nil in case of an error.
   To cause metrics to be written to database, and to make the connection instance passive, one (1) of connectionCompleted, connectionFailed, connectionTimedOut, or connectionCancelled must be called.
   It is assumed that only one connection instance is active at any one point in time.
   If the connection or location is changed while a connection instance is active, only the connection and location at start time will be recorded.
 */
+ (TTNATApplicationPerformance *) connectionStart:(NSString *)contentURL contentType:(NSString *)contentType transferType:(TTNATTAPTransferType)transferType tag:(NSString *)tag;

/**
   Indicates that a connection has successfully completed.
   @return
   YES if the call succeeded, NO otherwise.
 */
- (BOOL) connectionCompleted;

/**
   Indicates that a connection has failed.
   @return
   YES if the call succeeded, NO otherwise.
 */
- (BOOL) connectionFailed;

/**
   Indicates that a connection has timed out.
   @return
   YES if the call succeeded, NO otherwise.
 */
- (BOOL) connectionTimedOut;

/**
   Indicates that a connection has been cancelled.
   @return
   YES if the call succeeded, NO otherwise.
 */
- (BOOL) connectionCancelled;

@end
#endif /* ifndef iOS_TutelaNATSDK_TTNATApplicationPerformance_h */
