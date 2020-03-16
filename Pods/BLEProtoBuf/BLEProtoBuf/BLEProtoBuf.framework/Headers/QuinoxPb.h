//
//  QuinoxPb.h
//  BLEProtocBuff
//
//  Created by A$CE on 2019/3/20.
//  Copyright © 2019年 Iwown. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BLEDragonBoat/DNBQuinox.h>
NS_ASSUME_NONNULL_BEGIN

@protocol QuinoxPb <DNBQuinox>

@optional
#pragma mark- PB_FileUpdate
- (void)pbFileUpdateDesc:(NSDictionary *)fileDesc;
/**!
 type : 0-GPS, 1-FONT
 status : 0-isOK, 1-Error ,2-Error
 error : nil mean successful
 */
- (void)pbFileUpdateInit:(NSInteger)type andStatus:(NSInteger)status andError:(NSError *)error;

/**!
 FUDataResponse_Status_Ok = 0,
 FUDataResponse_Status_ErrorParams = 1,
 FUDataResponse_Status_ErrorOffsetMismatch = 2,
 FUDataResponse_Status_ErrorCrc32Mismatch = 3,
 FUDataResponse_Status_ErrorInner = 4,
 */
- (void)pbFileUpdateData:(NSInteger)type andStatus:(NSInteger)status andFileOfSet:(NSInteger)fileOfSet andCrc32AtFileOfSet:(NSInteger)crc32 andError:(NSError *)error;

- (void)pbFileUpdateExitStatus:(NSInteger)status;

/**! Action event for take picture*/
- (void)notifyToTakePicture;

@end

NS_ASSUME_NONNULL_END
