/**
         @file  TTNATConnectivityStatus.h
         @section PROJECT
          iOS_TutelaNATSDK

         @author  Created by Brennen Chow on 2013-01-22.
         @section LICENSE
          Copyright (c) 2013 Tutela Technologies. All rights reserved.
 */

#import <Foundation/Foundation.h>

/**
 * Defines the possible connectivity states.
 */
typedef enum {
    TTNATConnectivityStateNone = -1,            ///< No connectivity
    TTNATConnectivityStateWifi = 0,             ///< Connected to Wi-Fi (802.11)
    TTNATConnectivityStateWifiRoaming = 1,      ///< Connected to Wi-Fi (802.11) roaming
    TTNATConnectivityStateCellular = 2,           ///< Connected to Cellular
    TTNATConnectivityStateCellularRoaming = 3     ///< Connected to Cellular roaming
} TTNATConnectivityState;
/**
   Defines the possible cellular technology types.
 */
typedef enum {
    TTNATConnectionTechnologyUnknown = 0,   ///< Unknown
    TTNATConnectionTechnologyGPRS = 1,      ///< GPRS
    TTNATConnectionTechnologyEDGE = 2,      ///< EDGE
    TTNATConnectionTechnologyUMTS = 3,      ///< UMTS
    TTNATConnectionTechnologyCDMA = 4,      ///< CDMA
    TTNATConnectionTechnologyEVDO0 = 5,     ///< EVDO revision 0
    TTNATConnectionTechnologyEVDOA = 6,     ///< EVDO revision A
    TTNATConnectionTechnology1XRTT = 7,     ///< 1xRTT
    TTNATConnectionTechnologyHSDPA = 8,     ///< HSDPA
    TTNATConnectionTechnologyHSUPA = 9,     ///< HSUPA
    TTNATConnectionTechnologyHSPA = 10,     ///< HSPA
    TTNATConnectionTechnologyIDEN = 11,     ///< iDen
    TTNATConnectionTechnologyEVDOB = 12,    ///< EVDO revision B
    TTNATConnectionTechnologyLTE = 13,      ///< LTE
    TTNATConnectionTechnologyEHRPD = 14,    ///< eHRPD
    TTNATConnectionTechnologyHSPAP = 15     ///< HSPA+
} TTNATConnectionTechnology;
/**
   A container class for the connectivity status of the device.
 */
@interface TTNATConnectivityStatus : NSObject {
}
/**
   The connectivity state of the device.
 */
@property (nonatomic, assign, readonly) TTNATConnectivityState connectivityState;
/**
   The current service provider. Not used with WiFi
 */
@property (nonatomic, retain, readonly) NSString *serviceProvider;
/**
   The current network technology. Not used with WiFi.
 */
@property (nonatomic, assign, readonly) TTNATConnectionTechnology technology;
/**
   The BSSID of the access point to which the device is connected. Only used with WiFi
 */
@property (nonatomic, retain, readonly) NSString *bssid;
/**
   The SSID of the access point to which the device is connected. Only used with WiFi
 */
@property (nonatomic, retain, readonly) NSString *ssid;
/**
   The cellular Mobile Country Code, as defined by the SIM card. Not used with WiFi.
 */
@property (nonatomic, assign) int mcc;
/**
   The cellular Mobile Network Code, as defined by the SIM card. Not used with WiFi.
 */
@property (nonatomic, assign) int mnc;
/**
   Creates a TTNATConnectivityStatus object.
   @param connectivityState
    The connectivity state of the device.
   @param serviceProvider
    The service provider
   @param technology
    The network technology
   @param bssid
    The BSSID of the access point
   @param ssid
    The SSID of the access point
   @param mcc
   The Mobile Country Code
   @param mnc
   The Mobile Network Code
 */
- (TTNATConnectivityStatus *) initWithConnectivityState:(TTNATConnectivityState)connectivityState connectedServiceProvider:(NSString *)serviceProvider connectedTechnology:(TTNATConnectionTechnology)technology connectedBSSID:(NSString *)bssid connectedSSID:(NSString *)ssid connectMCC:(int)mcc connectMNC:(int)mnc;

@end
