//
//  MediaBrixUserDefaults.h
//  MediaBrixSDK
//
//  Created by Amos Elmaliah on 7/8/13.
//  Copyright (c) 2013 MediaBrix. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MediaBrix.h"

@interface MediaBrixUserDefaults : NSObject <
#ifdef MEDIABRIX_1_5
MediaBrixUserDefaultsDelegate
#elif defined(MEDIABRIX_1_5_5)
MediaBrixUserDefaults
#endif
>

+(NSMutableDictionary*)getBundleOverride;
@end

@interface MediaBrixUserDefaultsForProduction : MediaBrixUserDefaults

@end
