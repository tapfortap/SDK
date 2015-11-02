//
//  TTObject.h
//  iOS_TutelaNATSDK
//
//  Created by Michael Horie on 2015-02-06.
//  Copyright (c) 2015 Tutela Technologies. All rights reserved.
//

#ifndef iOS_TutelaNATSDK_TTObject_h
#define iOS_TutelaNATSDK_TTObject_h

@protocol TTObjectDelegateProtocol;

/**
   A class for tracking device and connection information.
 */
@interface TTObject : NSObject

/**
   A collection of possible object field flags
 */
    typedef enum TTObjectFieldFlags : int {
    TTObjectDevice = 1,         ///< Retrieve device information
    TTObjectConnection = 2,         ///< Retrieve connection information
    TTObjectWiFi = 4,        ///< Retrieve WiFi-specific information
    TTObjectCellular = 8,         ///< Retrieve cellular-specific information
    TTObjectLocation = 16,          ///< Retrieve location information
} TTObjectFieldFlags;

/**
   The device's connection state.
 */
@property NSString *connection;

/**
   The device's IP Address.
 */
@property NSString *ip;

/**
   The BSSID of the access point to which the device is connected. Only used with WiFi. nil otherwise.
 */
@property NSString *bssid;

/**
   The SSID of the access point to which the device is connected. Only used with WiFi. nil otherwise.
 */
@property NSString *ssid;

/**
   The cell ID of the network. nil on iOS.
 */
@property NSNumber *cid;

/**
   The local area code.  nil on iOS.
 */
@property NSNumber *lac;

/**
   The cellular Mobile Country Code, as defined by the SIM card. Only used with cellular. nil otherwise.
 */
@property NSNumber *mcc;

/**
   The cellular Mobile Network Code, as defined by the SIM card. Only used with cellular. nil otherwise.
 */
@property NSNumber *mnc;

/**
   The current service provider, as defined by the SIM card. Only used with cellular. nil otherwise.
 */
@property NSString *provider;

/**
   The cellular technology in use. Only used with cellular. nil otherwise.
 */
@property NSString *technology;

/**
   The device manufacturer.
 */
@property NSString *manufacturer;

/**
   The device model.
 */
@property NSString *model;

/**
   The device's operating system.
 */
@property NSString *os;

/**
   The device's system language.
 */
@property NSString *language;

/**
   The altitude. nil if unavailable.
 */
@property NSNumber *altitude;

/**
   The latitude. nil if unavailable.
 */
@property NSNumber *latitude;

/**
   The longitude. nil if unavailable.
 */
@property NSNumber *longitude;

/**
   The horizontal accuracy. nil if unavailable.
 */
@property NSNumber *horizontalAccuracy;

/**
   The vertical accuracy. nil if unavailable.
 */
@property NSNumber *verticalAccuracy;

/**
   The city. nil if unavailable.
 */
@property NSString *city;

/**
   The region (e.g., province, state, prefecture). nil if unavailable.
 */
@property NSString *region;

/**
   The country. nil if unavailable.
 */
@property NSString *country;

/**
   The mail code. nil if unavailable.
 */
@property NSString *mailCode;

/**
   The field flags used to initialize this object.
 */
@property TTObjectFieldFlags fieldFlags;

/**
   Prepares the Tutela object. The object, once prepared, will be returned to the delegate.
   @param fields
   The fields that should be filled out.  If multiple fields are needed, the corresponding flags can be OR'd together
   @param delegate
   The delegate that is to be called when the Tutela Object is ready
 */
- (id) initWithFields:(TTObjectFieldFlags)fields delegate:(id<TTObjectDelegateProtocol>)delegate;

/**
   Create a JSON encoding of this object. Do not call this method prior to receiving the preparedTutelaObject: callback
   @return
   The JSON encoding of this object.
 */
- (NSData *) jsonEncoding;
@end

@protocol TTObjectDelegateProtocol <NSObject>

/**
   If a TTObjectDelegate delegate is set, this delegate method will be called once the Tutela Object has been prepared
   @param ttObject
   The Tutela Object, or nil, if an error occurred
 */
- (void) preparedTutelaObject:(TTObject *)ttObject;

@end
#endif /* ifndef iOS_TutelaNATSDK_TTObject_h */
