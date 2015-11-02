/**
   @file  TTNATTestResult.h
   @section PROJECT
   iOS_TutelaNATSDK

   @author  Created by Brennen on 12-11-09.
   @section LICENSE
   Copyright (c) 2012 Tutela Technologies. All rights reserved.
 */

#import <Foundation/Foundation.h>

#define kTTNATErrorCode -32768
#define kTTNATNoTestCode -16384

/**
   Container class for a NAT test result.
   This is a copy of the TTQoSMeasurement class that is made available to the client application.
   This class was formerly called TTNATMeasurement.
 */
@interface TTNATTestResult : NSObject {
}
/**
   The download throughput, in kbps.
   If a test did not complete due to an error, then the kTTNATErrorCode will be passed used.
   If only a response test was completed, kTTNATNoTestCode will be passed used.
 */
@property (nonatomic, assign) double downloadThroughput;
/**
   The upload throughput in kbps.
   If a test did not complete due to error, then the kTTNATErrorCode will be passed used.
   If only a response test was completed, kTTNATNoTestCode will be passed used.
 */
@property (nonatomic, assign) double uploadThroughput;
/**
   The miniumum latency, in milliseconds.
 */
@property (nonatomic, assign) double minimumLatency;
/**
   The maximum latency, in milliseconds.
 */
@property (nonatomic, assign) double maximumLatency;
/**
   The average latency, in milliseconds.
 */
@property (nonatomic, assign) double averageLatency;
/**
   The minimum jitter, in milliseconds.
 */
@property (nonatomic, assign) double minimumJitter;
/**
   The maximum jitter, in milliseconds.
 */
@property (nonatomic, assign) double maximumJitter;
/**
   The average jitter, in milliseconds.
 */
@property (nonatomic, assign) double averageJitter;
/**
   The number of packets used in the server response test.
 */
@property (nonatomic, assign) int packetsSent;
/**
   The number of packets lost during the server response test.
 */
@property (nonatomic, assign) int packetsLost;
/**
   The packet loss percentage.
   The packet loss percentage only takes lost packets into account.
   Packets that arrived out of sequence are not included in this statistic.
 */
@property (nonatomic, assign) double packetsLostPercentage;
/**
   The number of packets that were discarded during the server response test.
 */
@property (nonatomic, assign) int packetsDiscarded;
/**
   The packet discard percentage.
   The packet discard percentage takes lost and out-of-sequence packets into account.
 */
@property (nonatomic, assign) double packetsDiscardedPercentage;
/**
   The number of packets that were received out of sequence during the server response test.
 */
@property (nonatomic, assign) int packetsOutOfSequence;

@end
