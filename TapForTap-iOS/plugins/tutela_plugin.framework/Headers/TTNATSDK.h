/**
         @file  TutelaNATSDK.h
         @section PROJECT
          iOS_TutelaNATSDK

         @author  Created by Brennen on 13-01-11.
         @section LICENSE
          Copyright (c) 2013 Tutela Technologies. All rights reserved.
 */

#import "TTNATConnectivityStatus.h"
#import "TTNATConstants.h"
#import "TTNATTestResult.h"
#import "TTObject.h"
#import <CoreLocation/CoreLocation.h>
#import <Foundation/Foundation.h>
#import <sqlite3.h>
#import <UIKit/UIKit.h>

#define TTNATSDK_HEADER 1

/**
   Notification used to indicate that a location error has occurred.
 */
extern NSString *const kTTNATLocationErrorNotification;
/**
   Notification that an export action is complete. The user info dictionary, given the kTNATSDKNotificationStatusKey, states whether or not the export succeeded.
 */
extern NSString *const kTTNATExportCompleteNotification;
/**
   Notification that connectivity changed.
 */
extern NSString *const kTTNATConnectivityChangeNotification;
/**
   Notification that a maximum file size limit has been reached. The user info dictionary, given the kTNATSDKDBFileSizeLimitKey, states whether the limit is soft or hard.
 */
extern NSString *const kTTNATMaximumDBFileSizeNotification;
/**
   Notification that test completed.
 */
extern NSString *const kTTNATTestCompleteNotification;
/**
   Notification that a deployment key check completed. The user info dictionary, given the kTNATSDKNotificationStatusKey, states whether or not the check succeeded.
 */
extern NSString *const kTTNATDeploymentKeyNotification;
/**
   Notification that a NAT DSC config profile was downloaded and applied. Changes are noted in the user info dictionary.
 */
extern NSString *const kTTNATSettingsChangedNotification;
/**
   A collection of possible test sizes. These are used for executing different types of throughput tests.
 */
typedef enum TTNATTestSize : int {
    TTNATTestSizeMicro = 0,         ///< Micro Test Size: 250kB Download, 250kB Upload
    TTNATTestSizeSmall = 1,         ///< Small Test Size: 500kB Download, 250kB Upload
    TTNATTestSizeMedium = 2,        ///< Medium Test Size: 1MB Download, 500KB Upload
    TTNATTestSizeLarge = 3,         ///< Large Test Size: 5MB Download, 1MB Upload
    TTNATTestSizeHuge = 4,          ///< Huge Test Size: 10MB Download, 5MB Upload
    TTNATTestSizeContinuous = 5     ///< Continuous Test Size: Download/Upload until steady rate achieved
} TTNATTestSize;
/**
   A collection of possible power plans.
 */
typedef enum TTNATPowerPlan : int {
    TTNATPowerPlanUnknown = 0,        ///< Unknown power plan
    TTNATPowerPlanBalanced = 1,       ///< Balance between accuracy and power usage (significant location updates, motion activity)
    TTNATPowerPlanHighAccuracy = 2,   ///< High accuracy and power (full background location updates, motion activity)
    TTNATPowerPlanLowPower = 3        ///< Low accuracy and power (significant location updates, no motion activity)
} TTNATPowerPlan;

/**
   Tutela Network Analysis Toolset (NAT)

   This class contains methods for performing Quality of Service tests which are then reported back to Tutela servers for analysis and reporting.

   A valid deployment key is required to use this SDK.

   Usage Clarifications:
   "Jitter is the undesired deviation from true periodicity of an assumed periodic signal" (Wikipedia)
   Latency is the time difference between the start of a transmission by the sender and the end of a transmission as measured by the receiver

 */
@interface TTNATSDK : NSObject {
}
#pragma mark - NAT Properties
/**
   The licence key.
 */
@property (nonatomic, strong) NSString *tutelaDeploymentKey;
/**
   Enable passive tests.  This setting overrides ALL other settings, ensuring that no active probes are conducted. The default is NO.
 */
@property (nonatomic, assign) BOOL enablePassiveTest;
/**
   Enable dynamic server configuration. This is used to configure the NAT SDK settings through a central server. The default value is YES.
 */
@property (nonatomic, assign) BOOL enableDynamicServerConfiguration;
/**
   Enable database export over a cellular network. The default value is YES.
 */
@property (nonatomic, assign) BOOL exportOnCellular;
/**
   Enable database export over a WiFi network. The default value is YES.
 */
@property (nonatomic, assign) BOOL exportOnWiFi;
/**
   The export frequency, in minutes. This value will be considered advisory. If tests are not running, this value is ignored. The default value is 0 minutes (never).
 */
@property (nonatomic) unsigned exportFrequency;
/**
   Enable server response tests over cellular. Affects all background and foreground tests over cellular. The default value is YES.
 */
@property (nonatomic, assign) BOOL enableServerResponseTestOverCellular;
/**
   Enable throughput tests over cellular. Affects all foreground tests over cellular. (Due to iOS restrictions, no background throughput tests are performed.) The default value is YES.
 */
@property (nonatomic, assign) BOOL enableThroughputTestOverCellular;
/**
   Enable periodic throughput tests.  Affects all foreground tests.  (Due to iOS restrictions, no background throughput tests are performed.) The default value is YES.
 */
@property (nonatomic, assign) BOOL enablePeriodicThroughputTest;
/**
   Enable a QoS test when the device connectivity changes (Wi-Fi->Cell, Cell->Wi-Fi, WiFi->WiFi). Tests must already be running in the foreground, or this setting will have no effect. (Due to iOS restrictions, this setting has no effect in the background.) The default value is YES.
 */
@property (nonatomic, assign) BOOL enableQoSTestOnConnectivityChange;
/**
   Enable a QoS test when the device location changes. Tests must already be running in the foreground or background, or this setting will have no effect.
   The default value is YES.

   For standard location tests in the background, the 'location' key must be set in the Info.plist file, enableQoSTestOnLocationChange must be YES, and enableOnlySignificantLocationUpdates must be NO.
 */
@property (nonatomic, assign) BOOL enableQoSTestOnLocationChange;
/**
   Enable only significant location changes, as opposed to standard location updates. This will also be effective in the background. The default value is YES.
   Note that in a production environment, this value is expected to be set to YES if "location" is not a listed background mode, and NO if location is a listed background mode.
 */
@property (nonatomic, assign) BOOL enableOnlySignificantLocationUpdates;
/**
   Enable periodic server response tests. Tests must already be running in the foreground or background, or this setting will have no effect. (Due to iOS restrictions, no periodic tests can be performed in the background.)  The default value is YES.

   For aperiodic tests in the background, the 'fetch' key must be set in the Info.plist file, and enablePeriodicServerResponseTest must be YES.
 */
@property (nonatomic, assign) BOOL enablePeriodicServerResponseTest;
/**
   The period between server response tests, in seconds. Default is 30 seconds. Setting this property below this value will raise an NSInvalidArgumentException.
   @throws NSInvalidArgumentException
 */
@property (nonatomic, assign) int periodicServerResponseTestFrequency;
/**
   The minimum amount of time to wait between server response tests, in seconds.
 */
@property (nonatomic, assign, readonly) int minPeriodicServerResponseTestFrequency;
/**
   The period between throughput tests, in seconds. Default is 120 seconds. Setting this property below this value will raise an NSInvalidArgumentException.
   @throws NSInvalidArgumentException
 */
@property (nonatomic, assign) int periodicThroughputTestFrequency;
/**
   The minimum amount of time to wait between throughput tests, in seconds.
 */
@property (nonatomic, assign, readonly) int minPeriodicThroughputTestFrequency;
/**
   The file size limit before a soft kTTNATSDKDBFileSizeLimitKey notification is raised. This is a warning that data should be exported soon. Default value is 5MB bytes. Setting this property below this value will raise an NSInvalidArgumentException.
   @throws NSInvalidArgumentException

 */
@property (nonatomic, assign) long softFileSizeLimitation;
/**
   The file size limit before a hard kTTNATSDKDBFileSizeLimitKey notification is raised. Once this limit is reached, no further data will be collected. Default value is 8MB bytes. Setting this property below this value will raise an NSInvalidArgumentException.
   @throws NSInvalidArgumentException

 */
@property (nonatomic, assign) long hardFileSizeLimitation;
/**
   The minimum horizontal distance, in metres, that must be covered before a test takes place. Default is 5 metres.
 */
@property (nonatomic, assign, readonly) long minLocationUpdateDistance;
/**
   The minimum time, in seconds, between tests. Default is 10 seconds.
 */
@property (nonatomic, assign, readonly) long minLocationUpdateTime;
/**
   The distance, in metres, that must be covered before a test takes place. Default is 5 metres. Setting this property below minLocationUpdateDistance will raise an NSInvalidArgumentException.
   @throws NSInvalidArgumentException
 */
@property (nonatomic, assign) long locationUpdateDistance;
/**
   The time, in seconds, that must elapse before a test takes place. Default is 10 seconds. Setting this property below minLocationUpdateTime will raise an NSInvalidArgumentException. This property takes precedence over locationUpdateDistance, meaning that no location changes, regardless of distance covered, are taken into consideration until the locationUpdateTime has elapsed.
   @throws NSInvalidArgumentException
 */
@property (nonatomic, assign) long locationUpdateTime;
/**
   The power plan of the SDK, as applied to the location subsystem. Note that TTNATPowerPlanUnknown will be ignored.
   Note that in a production environment, this value is expected to be set to TTNATPowerPlanBalanced or TTNATPowerPlanLowPower if "location" is not a listed background mode, and TTNATPowerPlanHighAccuracy if location is a listed background mode.
 */
@property (nonatomic, assign) TTNATPowerPlan locationRequestType;
/**
   The angular change, in degrees, before a heading update is recorded. Default is 5 degrees. Setting this property outside the range [0, 180] will raise an NSInvalidArgumentException.
   @throws NSInvalidArgumentException
 */
@property (nonatomic) CLLocationDegrees headingFilter;
/**
   Enable location updates to include motion updates, where the hardware allows. The default value is YES.
 */
@property (nonatomic, assign) BOOL enableMotionUpdates;
/**
   The current connection time, in seconds.
 */
@property (atomic, assign, readonly) int timerCount;

#pragma mark - QoS Properties
/**
   The number of packets to send during a response test. Default value is 20. Setting this property below this value will raise an NSInvalidArgumentException.
   @throws NSInvalidArgumentException
 */
@property (nonatomic, assign) int numberOfServerResponseTestPackets;
/**
   The size of the packets, in bytes, to use for the response test. Default value is 1 byte. Setting this property below this value will raise an NSInvalidArgumentException.
   @throws NSInvalidArgumentException
 */
@property (nonatomic, assign) int serverResponseTestPacketSize;
/**
   The timeout delay, in seconds, for the server response test. Default value is 10 seconds. Setting this property below this value will raise an NSInvalidArgumentException.
   @throws NSInvalidArgumentException
 */
@property (nonatomic, assign) int serverResponseTestTimeout;
/**
   The timeout delay, in seconds, for the download throughput test. Default value is 25 seconds. Setting this property below this value will raise an NSInvalidArgumentException.
   @throws NSInvalidArgumentException
 */
@property (nonatomic, assign) int throughputTestDownloadTimeout;
/**
   The timeout delay, in seconds, for the upload throughput test. Default value is 15 seconds. Setting this property below this value will raise an NSInvalidArgumentException.
   @throws NSInvalidArgumentException
 */
@property (nonatomic, assign) int throughputTestUploadTimeout;
/**
   The test size to use in the throughput test. Default value is TTNATTestSizeMedium.
 */
@property (nonatomic, assign) TTNATTestSize throughputTestSize;
/**
   The minimum number of packets to send during a server response test. Default value is 20.
 */
@property (nonatomic, assign, readonly) int minNumberOfPackets;
/**
   The maximum number of packets to send during a server response test. Default value is 100.
 */
@property (nonatomic, assign, readonly) int maxNumberOfPackets;
/**
   The minimum packet size, in bytes, for a server response test. Default value is 1 byte.
 */
@property (nonatomic, assign, readonly) int minServerResponseTestPacketSize;
/**
   The maximum packet size, in bytes, for a server response test. Default value is 100 bytes.
 */
@property (nonatomic, assign, readonly) int maxServerResponseTestPacketSize;
/**
   The minimum timeout, in seconds, for a server response test. Default value is 10 seconds.
 */
@property (nonatomic, assign, readonly) int minServerResponseTestTimeout;
/**
   The minimum timeout, in seconds, for a download throughput test. Default value is 25 seconds.
 */
@property (nonatomic, assign, readonly) int minThroughputTestDownloadTimeout;
/**
   The minimum timeout, in seconds, for an upload throughput test. Default value is 15 seconds.
 */
@property (nonatomic, assign, readonly) int minThroughputTestUploadTimeout;

#pragma mark - QoS Measurements
/**
   The download throughput, in kbps.
   A value of kTTNATErrorCode indicates that an error occured during the test.
   A value of kTTNATNoTestCode means that a test was not conducted.
 */
@property (nonatomic, assign, readonly) double downloadThroughput;
/**
   The upload throughput, in kbps.
   A value of kTTNATErrorCode indicates that an error occured during the test.
   A value of kTTNATNoTestCode means that a test was not conducted.
 */
@property (nonatomic, assign, readonly) double uploadThroughput;
/**
   The average jitter, in milliseconds.
   A value of kTTNATErrorCode indicates that an error occured during the test.
   A value of kTTNATNoTestCode means that a test was not conducted.
 */
@property (nonatomic, assign, readonly) double averageJitter;
/**
   The maximum jitter, in milliseconds.
   A value of kTTNATErrorCode indicates that an error occured during the test.
   A value of kTTNATNoTestCode means that a test was not conducted.
 */
@property (nonatomic, assign, readonly) double maximumJitter;
/**
   The minumum jitter, in milliseconds.
   A value of kTTNATErrorCode indicates that an error occured during the test.
   A value of kTTNATNoTestCode means that a test was not conducted.
 */
@property (nonatomic, assign, readonly) double minimumJitter;
/**
   The average latency, in milliseconds.
   A value of kTTNATErrorCode indicates that an error occured during the test.
   A value of kTTNATNoTestCode means that a test was not conducted.
 */
@property (nonatomic, assign, readonly) double averageLatency;
/**
   The maximum latency, in milliseconds.
   A value of kTTNATErrorCode indicates that an error occured during the test.
   A value of kTTNATNoTestCode means that a test was not conducted.
 */
@property (nonatomic, assign, readonly) double maximumLatency;
/**
   The minimum latency, in milliseconds.
   A value of kTTNATErrorCode indicates that an error occured during the test.
   A value of kTTNATNoTestCode means that a test was not conducted.
 */
@property (nonatomic, assign, readonly) double minimumLatency;
/**
   The number of packets sent during the server response test.
 */
@property (nonatomic, assign, readonly) int packetsSent;
/**
   The number of packets that were not returned, i.e., the difference between the number of packets sent and the number of packets returned.
 */
@property (nonatomic, assign, readonly) int numberOfPacketsLost;
/**
   The packet loss percentage.
 */
@property (nonatomic, assign, readonly) double packetLossPercentage;
/**
   The number of packets discarded during the test. This is the sum of lost AND out-of-sequence packets.
 */
@property (nonatomic, assign, readonly) int numberOfPacketsDiscarded;
/**
   The percentage of the discarded packets.
 */
@property (nonatomic, assign, readonly) double packetDiscardPercentage;
/**
   The number of packets that came back out of sequence.
 */
@property (nonatomic, assign, readonly) int packetsOutOfSequence;

#pragma mark - Initialization
/**
   Returns a reference to the NAT SDK singleton. The first time this method is called, it will apply the default settings.
   @return
   An instance of the NAT.
 */
+ (TTNATSDK *) natInstance;

#pragma mark - System Configuration
/**
   Resets the NAT settings to their default values.
 */
- (void) resetNATSettingsToDefaultValues;
#pragma mark - Start/Stop Automated Collection
/**
   Starts automated QoS collection.

   First, settings provided by the user (or defaults, if no settings are provided) are applied.

   Next, data will be exported, providing the settings permit this.

   Then, periodic server response and throughput tests will be conducted as specified by the settings.

   Tests will continue to be run until the stop method is called.

   A kTTNATTestCompleteNotification is dispatched when results are available.

   Results are stored in the database.
 */
- (void) start;
/**
   Performs a background test.
   Must be called from application:performFetchWithCompletionHandler:
   @param completionHandler
   The handler to be called upon completion of the test.
 */
- (void) performBackgroundTestWithCompletionHandler:( void (^)(UIBackgroundFetchResult) )completionHandler;
/**
   Stops automated QoS collection. When stop is called, all timers are cancelled and the tests will stop running.
 */
- (void) stop;

#pragma mark - QoS Test Execution
/**
   Starts one active throughput test. This will initiate a download throughput test followed by an upload throughput test.

   The download throughput test will initiate a download of a file. The size of the file is set by the TTNATTestSize setting.

   The upload throughput test will initiate an upload of a file. The size of the file is set by the TTNATTestSize setting.

   The corresponding stop method must be called when tests should be cancelled. A test will not be run if it interferes with an existing test.

   A kTTNATTestCompleteNotification is dispatched when results are available. Results of these one-off tests are not stored in the database.
   @return
   YES if the test was started successfully, NO otherwise.
 */
- (BOOL) startActiveThroughputTest;
/**
   Starts one throughput test followed by one server response test.

   The corresponding stop method must be called when tests should be cancelled. A test will not be run if it interferes with an existing test.

   A kTTNATTestCompleteNotification is dispatched when results are available. Results of these one-off tests are not stored in the database.
 */
- (BOOL) startThroughputAndServerResponseTest;
/**
   Starts a server response test.

   A server response test will send packets to the server (the number and size can be changed using the properties in this SDK).
   The response test sends packets to the server which are then echoed back and received by the device.
   Once all the packets have been returned, packet loss, jitter, latency and sequence are computed.

   The corresponding stop method must be called when tests should be cancelled. A test will not be run if it interferes with an existing test.

   A kTNATSDKNotificationStatusKey is dispatched when results are available. Results of these one-off tests are not stored in the database.
   @return
   YES if the test was started successfully, NO otherwise.
 */
- (BOOL) startServerResponseTest;
/**
   Stops a throughput test.
   @return
   YES if the test was stopped successfully, NO otherwise.
 */
- (BOOL) stopActiveThroughputTest;
/**
   Stops a throughput and server response test.
   @return
   YES if the tests were stopped successfully, NO otherwise.
 */
- (BOOL) stopThroughputAndServerResponseTest;
/**
   Stops a server response test.
   @return
   YES if the test was stopped successfully, NO otherwise.
 */
- (BOOL) stopServerResponseTest;
#pragma mark - Other API's
/**
   Returns whether or not the automated QoS test is currently running.
   @return
   YES if the automated QoS test is running, NO otherwise.
 */
- (BOOL) isRunning;
/**
   Returns the globally-unique device identifier. The identifier is hashed to provide anonymity.
   @return
   The device identifier as a hashed string.
 */
- (NSString *) getIdentifier;
/**
   Returns the device's current connection information.
   @return
   The device's current connection information.
 */
- (TTNATConnectivityStatus *) getConnectivityStatus;
/**
   Returns the device's current connectivity state.
   @return
   The current connectivity state of the device
 */
- (TTNATConnectivityState) getConnectivityState;
/**
   Returns the name of the cellular service provider tied to the SIM card.
   @return
   The current service provider name. If the device is on WiFi, an empty string is returned.
 */
- (NSString *) getConnectedServiceProvider;
/**
   Returns the current cellular technology.
   @return
   The current connection technology of the device. If the device is on WiFi, this is TTNATConnectionTechnologyUnknown.
 */
- (TTNATConnectionTechnology) getConnectedTechnology;
/**
   Returns the Wi-Fi Basic Service Set Identification (BSSID) of the current access point.
   @return
   The current BSSID of the wireless access point. If the device isn't connected to a Wi-Fi network, an empty string is returned.
 */
- (NSString *) getConnectedBSSID;
/**
   Returns the Wi-Fi Service Set Identification (SSID) of the current access point.
   @return
   The current ssid of the wireless access point. If the device isn't connected to a Wi-Fi network, an empty string is returned.
 */
- (NSString *) getConnectedSSID;
/**
   Returns the cellular Mobile Country Code (MCC) tied to the SIM card.
   @return
   The cellular Mobile Country Code (MCC), or 0 if the device is on Wi-Fi.
 */
- (int) getConnectedMCC;
/**
   Returns the cellular Mobile Network Code (MNC) tied to the SIM card.
   @return
   The cellular Mobile Network Code (MNC), or 0 if the device is on Wi-Fi.
 */
- (int) getConnectedMNC;
/**
   Given a connection ID, return the corresponding connection type.
   @param connID
   The connection ID.
   @return
   The connection type, or TTNATConnectivityStateNone if no entry was found.
 */
- (TTNATConnectivityState) getConnectionTypeGivenConnectionID:(int)connID;
/**
   Given a connection ID, return the corresponding QoS entries.
   @param connID
   The connection ID.
   @return
   The corresponding QoS entries, or nil if no entry was found.
 */
- (NSArray *) getQosDataGivenConnectionID:(int)connID;
/**
   Given a connection type, return the corresponding QoS entries.
   @param connType
   The connection type.
   @return
   The corresponding QoS entries, or nil if no entry was found.
 */
- (NSArray *) getQosDataGivenConnectionType:(TTNATConnectivityState)connType;
/**
   Whether or not an emergency kill switch has been triggered
 */
- (BOOL) killSwitchTriggered;
#pragma mark - Export Database
/**
   Exports the device logs to the server, removes the database from the device, and creates a new database.
   @param forcedExport
    If YES, forces the export of the database using any type of connection available, including cellular. If NO, the export will only occur if the device is currently connected to a Wi-Fi network.
 */
- (void) exportDB:(BOOL)forcedExport;
/**
   Clears the data from the device logs. This will delete all current data collected from a QoS test. Deleted data cannot be recovered.
 */
- (void) clearLogs;

#pragma mark - Data Retrieval
/**
   Returns an array containing the column header names of the connection table.
   @return
   An array containing the column header names of the connection table.
 */
- (NSArray *) getConnectionTableColumnHeaders;
/**
   Returns an array containing the column header names of the device table.
   @return
   An array containing the column header names of the device table.
 */
- (NSArray *) getDeviceTableColumnHeaders;
/**
   Returns an array containing the column header names of the QoS table.
   @return
   An array containing the column header names of the QoS table.
 */
- (NSArray *) getQoSTableColumnHeaders;
/**
   Returns an array containing all the QoS data.
   @return
   An array containing all the QoS data.
 */
- (NSArray *) getQoSTable;
/**
   Returns an array containing all the connection data.
   @return
   An array containing all the connection data.
 */
- (NSArray *) getConnectionTable;
/**
   Returns an array containing the device information.
   @return
   An array containing the device information.
 */
- (NSArray *) getDeviceTable;
/**
   Returns the number of QoS entries.
   @return
   The number of QoS entries.
 */
- (unsigned) getQoSTableSize;
/**
   Returns the number of connection entries.
   @return
   The number of connection entries.
 */
- (unsigned) getConnectionTableSize;
/**
   Returns the number of device entries.
   @return
   The number of device entries.
 */
- (unsigned) getDeviceTableSize;
/**
   Returns a TTNATTestResult object that contains all the QoS Measurements for the last-run test.
   @return
   TTNATTestResult object that contains all the QoS Measurements for the last-run test.
 */
- (TTNATTestResult *) getMeasurementResults;
/**
   Prepares the Tutela object. The object, once prepared, will be returned to the ttObjectDelegate.
   @param fields
   The fields that should be filled out.  If multiple fields are needed, the corresponding flags can be OR'd together
   @param ttObjectDelegate
   The delegate that is to be called when the Tutela Object is ready
 */
- (void) prepareTutelaObjectWithFields:(TTObjectFieldFlags)fields delegate:(id<TTObjectDelegateProtocol>)ttObjectDelegate;

@end
