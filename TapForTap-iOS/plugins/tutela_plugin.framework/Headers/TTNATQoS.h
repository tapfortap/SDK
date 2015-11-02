/**
         @file  TTNATQoS.h
         @section PROJECT
          iOS_TutelaNATSDK

         @author  Created by Brennen on 12-11-26.
         @section LICENSE
          Copyright (c) 2012 Tutela Technologies. All rights reserved.
 */

#import <CoreLocation/CoreLocation.h>
#import <Foundation/Foundation.h>

/**
   Defines the possible activity states.
 */
typedef enum {
    TTNATStationary = 1,    ///< The device is stationary
    TTNATWalking = 2,       ///< The user of the device is walking
    TTNATRunning = 3,       ///< The user of the device is running
    TTNATAutomotive = 4,    ///< The user of the device is driving in a car
    TTNATCycling = 5,       ///< The user of the device is riding a bicycle
    TTNATUnknown = 0        ///< The activity affecting the device is unknown
} TTNATActivityState;

/**
   Defines the possible battery states.
 */
typedef enum {
    TTNATDeviceBatteryStateUnknown = 1,         ///< The battery state for the device cannot be determined.
    TTNATDeviceBatteryStateUnplugged = 2,       ///< The device is not plugged into power; the battery is discharging.
    TTNATDeviceBatteryStateNotCharging = 3,     ///< The battery is less than 100% charged and is not charging.
    TTNATDeviceBatteryStateCharging = 4,        ///< The device is plugged into power and the battery is less than 100% charged.
    TTNATDeviceBatteryStateFull = 5,            ///< The device is plugged into power and the battery is 100% charged.
    TTNATDeviceBatteryStateUnknownLowPower = 9,         ///< The battery state for the device cannot be determined. Device is in Low Power Mode.
    TTNATDeviceBatteryStateUnpluggedLowPower = 10,      ///< The device is not plugged into power; the battery is discharging. Device is in Low Power Mode.
    TTNATDeviceBatteryStateNotChargingLowPower = 11,    ///< The battery is less than 100% charged and is not charging. Device is in Low Power Mode.
    TTNATDeviceBatteryStateChargingLowPower = 12,       ///< The device is plugged into power and the battery is less than 100% charged. Device is in Low Power Mode.
    TTNATDeviceBatteryStateFullLowPower = 13            ///< The device is plugged into power and the battery is 100% charged. Device is in Low Power Mode.
} TTNATDeviceBatteryState;

/**
   Defines the possible test triggers.
 */
typedef enum {
    TTNATTestOnStart = 0,                       ///<  QoS test triggered on start of the SDK
    TTNATTestOnConnectionChange = 1,            ///<  QoS test triggered on connection change
    TTNATTestOnLocationChange = 2,              ///<  QoS test triggered on location change
    TTNATTestOnBackgroundFetch = 3,             ///<  QoS test triggered on background fetch (iOS only)
    TTNATTestOnStop = 4,                        ///<  QoS test triggered on stop of the SD
    TTNATTestOnEnteringForeground = 5,          ///<  QoS test triggered on entering the foreground of the application
    TTNATTestOnEnteringBackground = 6,          ///<  QoS test triggered on entering the background of the application
    TTNATTestOnManualRequest = 7,               ///<  QoS test triggered on manual API call to SDK
    TTNATTestOnExport = 8,                      ///<  QoS test triggered on export of data from the SDK
    TTNATTestOnServerResponseTimer = 9,         ///<  QoS test triggered on server response test timer
    TTNATTestOnThroughputTimer = 10             ///<  QoS test triggered on throughput test timer
} TTNATTestTrigger;

/**
   Container class for the QoS database.
 */
@interface TTNATQoS : NSObject {
}
/**
   The connection id. This is a link to a specific row in the connection table.
 */
@property (nonatomic, assign) int connectionId;
/**
   The collection timestamp, in UNIX time.
 */
@property (nonatomic, assign) long long timestamp;
/**
   The average upload throughput, in kbps.
    A value of kTTNATErrorCode indicates that an error occured during the test.
    A value of kTTNATNoTestCode means that a test was not conducted.
 */
@property (nonatomic, assign) double uploadThroughput;
/**
   The average download throughtput, in kbps.
   A value of kTTNATErrorCode indicates that an error occured during the test.
   A value of kTTNATNoTestCode means that a test was not conducted.
 */
@property (nonatomic, assign) double downloadThroughput;
/**
   The maximum latency, in milliseconds.
   A value of kTTNATErrorCode indicates that an error occured during the test.
   A value of kTTNATNoTestCode means that a test was not conducted.
 */
@property (nonatomic, assign) double latencyMax;
/**
   The minimum latency, in milliseconds.
   A value of kTTNATErrorCode indicates that an error occured during the test.
   A value of kTTNATNoTestCode means that a test was not conducted.
 */
@property (nonatomic, assign) double latencyMin;
/**
   The average latency, in milliseconds.
   A value of kTTNATErrorCode indicates that an error occured during the test.
   A value of kTTNATNoTestCode means that a test was not conducted.
 */
@property (nonatomic, assign) double latencyAvg;
/**
   The link speed, in Mbps. Not used on iOS.
 */
@property (nonatomic, assign) int linkSpeed;
/**
   The signal strength, in dB. Not used on iOS.
 */
@property (nonatomic, assign) int signalStrength;
/**
   The location.
 */
@property (nonatomic, strong) CLLocation *location;
/**
   The maximum jitter, in milliseconds.
   A value of kTTNATErrorCode indicates that an error occured during the test.
   A value of kTTNATNoTestCode means that a test was not conducted.
 */
@property (nonatomic, assign) double jitterMax;
/**
   The minimum jitter, in milliseconds.
   A value of kTTNATErrorCode indicates that an error occured during the test.
   A value of kTTNATNoTestCode means that a test was not conducted.
 */
@property (nonatomic, assign) double jitterMin;
/**
   The average jitter, in milliseconds.
   A value of kTTNATErrorCode indicates that an error occured during the test.
   A value of kTTNATNoTestCode means that a test was not conducted.
 */
@property (nonatomic, assign) double jitterAvg;
/**
   The number of packets sent.
 */
@property (nonatomic, assign) int packetsSent;
/**
   The number of packets lost.
 */
@property (nonatomic, assign) int packetsLost;
/**
   The percentage, range [0, 1], of lost packets.
 */
@property (nonatomic, assign) double packetLostPercentage;
/**
   The number of packets lost or out of sequence.
 */
@property (nonatomic, assign) int packetsDiscarded;
/**
   The percentage, range [0, 1], of lost or out-of-sequence packets.
 */
@property (nonatomic, assign) double packetDiscardedPercentage;
/**
   The number of transmitted bytes.
 */
@property (nonatomic, assign) long long transmitBytes;
/**
   The number of transmitted packets.
 */
@property (nonatomic, assign) long long transmitPackets;
/**
   The number of received bytes.
 */
@property (nonatomic, assign) long long receiveBytes;
/**
   The number of received packets.
 */
@property (nonatomic, assign) long long receivePackets;
/**
   The velocity, in m/s and degrees, at the time the measurement was taken.
 */
@property (nonatomic, strong) NSString *velocity;
/**
   The activity that took place at the time the measurement was taken.
 */
@property (nonatomic, assign) TTNATActivityState motionActivity;
/**
   The free memory, in bytes, at the time the measurement was taken.
 */
@property (nonatomic, assign) unsigned long long freeMemory;
/**
   The CPU utilization, range [0, 1], at the time the measurement was taken.
 */
@property (nonatomic, assign) double cpu;
/**
   The battery level, range [0, 1], at the time the measurement was taken.
 */
@property (nonatomic, assign) double batteryLevel;
/**
   The battery state at the time the measurement was taken.
 */
@property (nonatomic, assign) TTNATDeviceBatteryState batteryState;
/**
   The free storage, in bytes, at the time the measurement was taken.
 */
@property (nonatomic, assign) unsigned long long freeStorage;
/**
   The change in transmitted bytes since the last test.
 */
@property (nonatomic, assign) long long deltaTXBytes;
/**
   The change in received bytes since the last test.
 */
@property (nonatomic, assign) long long deltaRXBytes;
/**
   The download throughput test size in bytes since the last test.
 */
@property (nonatomic, assign) unsigned long long downloadThroughputTestSize;
/**
   The upload test size in bytes since the last test.
 */
@property (nonatomic, assign) unsigned long long uploadThroughputTestSize;
/**
   The test trigger.
 */
@property (nonatomic, assign) TTNATTestTrigger testTrigger;

@end
