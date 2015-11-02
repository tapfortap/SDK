//
//  Copyright (c) 2013 Tap for Tap. All rights reserved.
//

#import "TFTTapForTap.h"
#import "TapForTap_TFTPrivate.h"
#import "TFTAssetMananger.h"
#import "TFTInitializeRequest.h"
#import "TFTLog.h"
#import "TFTURIUtils.h"
#import "TFTUserInfo.h"
#import "TFTAdProvider.h"
#import "TFTPlugin.h"
#import "TapForTapAdProvider.h"

@interface TFTTapForTap() {}
@property (nonatomic, retain) NSMutableArray *initializationHandlers;
@property (nonatomic, assign) BOOL initialized;
@property (nonatomic, assign) BOOL initializing;
@property (nonatomic, retain) NSObject *initializeLock;
@property (nonatomic, assign) NSString *environment;

+ (void)initializeWithHandler:(TFTInitializationRequestHandler)handler;
@end

static NSString *SDK_VERSION_USER_DEFAULT =  @"SDK_VERSION";
static NSMutableArray *adProviderClasses;
static NSMutableArray *pluginClasses;

@implementation TFTTapForTap {}

#pragma mark - Initialization

__attribute__((constructor))
static void initialize_adProviderClassesArray() {
    adProviderClasses = [NSMutableArray array];
}

__attribute__((constructor))
static void initialize_pluginClassesArray() {
    pluginClasses = [NSMutableArray array];
}

+ (void)initializeWithAPIKey:(NSString *)apiKey completion:(TFTInitializationRequestHandler)handler {
    if (!apiKey || [apiKey isEqualToString:@"YOUR API KEY"]) {
        NSLog(@"Please enter a valid Tap for Tap API Key");
        handler(NO, @{@"reason" : @"Invalid API key."});
        return;
    }

    @synchronized(tapfortap.initializeLock) {
        if (tapfortap.initialized) {
            handler(YES, nil);
            return;
        } else if (tapfortap.initializing) {
            [tapfortap.initializationHandlers addObject:[handler copy]];
            return;
        }
        tapfortap.initializing = YES;
        [tapfortap.initializationHandlers addObject:[handler copy]];
    }

    [self invalidateAssets];

    tapfortap.apiKey = apiKey;
    [TFTInitializeRequest startNewInitializeRequestWithHandler:^(BOOL success, NSDictionary *extra) {
        @synchronized (tapfortap.initializeLock) {
            for (TFTInitializationRequestHandler handler in tapfortap.initializationHandlers) {
                handler(success, extra);
            }
            tapfortap.initializing = NO;
            tapfortap.initialized = YES;
        }
    }];
    NSMutableArray *pluginArray = [NSMutableArray arrayWithObject:[TapForTapAdProvider class]];
    [self registerPlugins:pluginArray];
    
    for (id adProvider in adProviderClasses)
    {
        if([[adProvider class] conformsToProtocol:@protocol(TFTAdProvider)]) {
            [adProvider initialize];
        }
    }
    
    for (id plugin in pluginClasses)
    {
        if([[plugin class] conformsToProtocol:@protocol(TFTPlugin)]) {
            [plugin initialize];
        }
    }
    
}

+ (void)initializeWithAPIKey:(NSString *)apiKey {
    [TFTTapForTap initializeWithAPIKey:apiKey completion:^(BOOL success, NSDictionary *extra) {
        if ([extra[@"created"] boolValue]) {
            [[[UIAlertView alloc] initWithTitle: @"New App"
                                         message: @"Alright, we created your app! You can manage it at tapfortap.com/manage."
                                        delegate: nil
                               cancelButtonTitle: @"OK"
                               otherButtonTitles: nil] show];
        }

        if ([extra[@"paused"] boolValue]) {
            [TFTTapForTap disableTapForTap];
        }

        if (success) {
            TFTDebugLog(@"Successfully initialized.");
        }
        else {
            TFTDebugLog(@"Failed to initialize.");
        }
    }];
}

+ (void)initializeWithAPIKey:(NSString *)apiKey andPlugins:(Class)firstPlugin, ... NS_REQUIRES_NIL_TERMINATION {
    
    NSMutableArray *pluginsArray = [NSMutableArray array];
    
    Class plugin;
    va_list argumentList;
    
    va_start(argumentList, firstPlugin);
    plugin = firstPlugin;
    
    while(plugin != nil)
    {
        [pluginsArray addObject:plugin];
        plugin = va_arg(argumentList, Class);
    }
    
    va_end(argumentList);
    
    [self registerPlugins:pluginsArray];

    
    [TFTTapForTap initializeWithAPIKey:apiKey completion:^(BOOL success, NSDictionary *extra) {
        if ([extra[@"created"] boolValue]) {
            [[[UIAlertView alloc] initWithTitle: @"New App"
                                        message: @"Alright, we created your app! You can manage it at tapfortap.com/manage."
                                       delegate: nil
                              cancelButtonTitle: @"OK"
                              otherButtonTitles: nil] show];
        }
        
        if ([extra[@"paused"] boolValue]) {
            [TFTTapForTap disableTapForTap];
        }
        
        if (success) {
            TFTDebugLog(@"Successfully initialized.");
        }
        else {
            TFTDebugLog(@"Failed to initialize.");
        }
    }];
}

+ (void)initializeWithHandler:(TFTInitializationRequestHandler)handler {
    NSString *apiKey = tapfortap.apiKey ? [NSString stringWithString: tapfortap.apiKey] : nil;
    if (!apiKey) {
        NSBundle *mainBundle = [NSBundle mainBundle];

        NSString *testMode = [mainBundle objectForInfoDictionaryKey:@"TapForTapTestMode"];
        if (testMode && [testMode isEqualToString:@"ON"]) {
            [self enableTestMode];
        }

        apiKey = [mainBundle objectForInfoDictionaryKey:@"TapForTapApiKey"];
    }
    [TFTTapForTap initializeWithAPIKey:apiKey completion:handler];
}

+ (void)registerPlugins:(NSMutableArray*) array
{
    for(Class pluginClass in array){
        if([pluginClass conformsToProtocol:@protocol(TFTAdProvider)]) {
            bool alreadyAdded = false;
            id plugin = [[pluginClass alloc] init];
            for (id existingAdProvider in [TFTTapForTap getAdProviders]) {
                if([[existingAdProvider class] conformsToProtocol:@protocol(TFTPlugin)] && [[existingAdProvider getPluginName] isEqualToString:[plugin getPluginName]]) {
                    alreadyAdded = true;
                }
            }
            if(!alreadyAdded) [adProviderClasses addObject:plugin];
        }
        else if([pluginClass conformsToProtocol:@protocol(TFTPlugin)]) {
            bool alreadyAdded = false;
            id plugin = [[pluginClass alloc] init];
            for (id existingPlugin in [TFTTapForTap getPlugins]) {
                if([[existingPlugin class] conformsToProtocol:@protocol(TFTPlugin)] && [[existingPlugin getPluginName] isEqualToString:[plugin getPluginName]]) {
                    alreadyAdded = true;
                }
            }
            if(!alreadyAdded) [pluginClasses addObject:plugin];
        }
    }
}

+ (NSMutableArray *) getPlugins
{
    return pluginClasses;
}

+ (NSMutableArray *) getAdProviders
{
    return adProviderClasses;
}

#pragma mark - User Info

+ (void)setYearOfBirth:(NSUInteger)yearOfBirth {
    [TFTUserInfo setYearOfBirth:yearOfBirth];
}

+ (void)setGender:(TFTGender)gender {
    [TFTUserInfo setGender:gender];
}

+ (void)setLocation:(CLLocation *)location {
    [TFTUserInfo setLocation:location];
}

+ (void)setUserAccountId:(NSString *)userAccountId {
    [TFTUserInfo setUserAccountID:userAccountId];
}

#pragma mark - Mode Configuration

+ (void) enableTestMode {
    tapfortap.testMode = YES;
}

+ (void) disableTestMode {
    tapfortap.testMode = NO;
}

+ (BOOL)testMode {
    return tapfortap.testMode;
}

+ (void) enableTapForTap {
    tapfortap.disabled = NO;
}

+ (void) disableTapForTap {
    tapfortap.disabled = YES;
}

+ (BOOL)enabled {
    return !tapfortap.disabled;
}

+ (NSString *)apiKey {
    return tapfortap.apiKey;
}

+ (NSString *)version {
    return tapfortap.sdkVersion;
}


+ (void)setEnvironment:(NSString *)environment {
    if ([environment isEqualToString:@"development"]) {
        [TFTURIUtils configureForDevelopment];
        tapfortap.environment = @"development";
    } else {
        [TFTURIUtils configureForProduction];
        tapfortap.environment = @"production";
    }
}

+ (NSString *)environment {
    return tapfortap.environment;
}

+ (void)setPlugin:(NSString *)plugin {
    tapfortap.plugin = plugin;
}

+ (NSString *)plugin {
    return tapfortap.plugin;
}

+ (void)setPluginVersion:(NSString *)pluginVersion {
    tapfortap.pluginVersion = pluginVersion;
}

+ (NSString *)pluginVersion {
    return tapfortap.pluginVersion;
}

#pragma mark - Private Initialization

+ (void)initialize {
    tapfortap = [[TFTTapForTap alloc] init];
}

+ (void)invalidateAssets {
    if (![[self SDKVersion] isEqualToString:tapfortap.sdkVersion]) {
        [self setSDKVersion:tapfortap.sdkVersion];
        [TFTAssetMananger writeVersion:@"0"];
    }
}

+ (NSString *)SDKVersion {
    return [[NSUserDefaults standardUserDefaults] objectForKey:SDK_VERSION_USER_DEFAULT];
}

+ (void)setSDKVersion:(NSString *)sdkVersion {
    [[NSUserDefaults standardUserDefaults] setObject:sdkVersion forKey:SDK_VERSION_USER_DEFAULT];
}

- (id) init {
    self = [super init];
    if (self) {
        _initializationHandlers = [[NSMutableArray alloc] init];
        _initialized = NO;
        _initializing = NO;
        _platform = @"ios";
        _sdkVersion = @"4.2.0";
        _plugin = self.platform;
        _pluginVersion = self.sdkVersion;
        _disabled = NO;
        _testMode = NO;
        _environment = @"production";
        _initializeLock = [[NSObject alloc] init];
    }
    return self;
}
@end

