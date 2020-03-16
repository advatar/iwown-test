//
//  DNBDataHandle.h
//  BLEDragonBoat
//
//  Created by A$CE on 2018/7/26.
//  Copyright © 2018年 A$CE. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

@class DNBSolsticeImpl;
@interface DNBDataHandle : NSObject

@property (nonatomic ,weak) CBPeripheral *peripheral;
@property (nonatomic ,weak) DNBSolsticeImpl *bleSolstice;

- (void)braceletCmdReceive:(id)obj;
- (void)braceletReceiveHRData:(NSInteger)hr; //心率标准协议

@end
