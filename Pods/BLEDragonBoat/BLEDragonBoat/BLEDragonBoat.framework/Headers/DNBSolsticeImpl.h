//
//  DNBSolsticeImpl.h
//  BLEDragonBoat
//
//  Created by A$CE on 2017/10/11.
//  Copyright © 2017年 A$CE. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DNBSolstice.h"
#import "DNBQuinox.h"
#import "DNBBlePeripheral.h"

typedef enum{
    SCQASCTypeNull = 0x00,
    SCQASCTypeFirst = 0x01,
    SCQASCTypeNormal = SCQASCTypeFirst,
    SCQASCTypeResumeNow = 0x02,
    SCQASCTypeResponseTimeOut = 0x03,
    SCQASCTypeLast,
} SCQASCType;

typedef enum{
    SCQASCValueNull = 0x00,
    SCQASCValueFirst = 0x01,
    SCQASCValueIndexTable = SCQASCValueFirst,
    SCQASCValueDetail = 0x02,
    SCQASCValueLast,
} SCQASCValue;

typedef struct {
    SCQASCType type;
    SCQASCValue value;
}SCQASCReObj;

@protocol DNBSolsticeImplConnectDeleagte <NSObject>

@optional
- (void)connectDidLosedAndReConnectSoon;

@end

@protocol DNBSolsticeImplDelegate <NSObject>

@optional
- (void)thereIsSomeCmdGotTimeOut:(SCQASCReObj)sRobj;

@end


@class DNBDataHandle;
@interface DNBSolsticeImpl : NSObject<DNBSolstice>

@property (nonatomic ,weak) CBPeripheral *peripheral;
@property (nonatomic ,weak) id<DNBSolsticeImplConnectDeleagte>implConnectDelegate;
@property (nonatomic ,weak) id<DNBSolsticeImplDelegate>implDelegate;
@property (nonatomic ,weak) id<DNBQuinox> bleQuinox;
@property (class, nonatomic, readonly, copy) NSString *bleLogPath;

/**! cmd queue flag, return YES, cancel block action*/
@property (nonatomic, assign) BOOL cmdQueueCancelFlag;
@property (nonatomic, assign) BOOL longCmdsDuring; //接收数据属于长命令，需要拆包的
/**
 * Invoked after connected.
 * See also at @CODE{solsticeWithConnectedPeripheral:};
 @param peripheral the device 
 */
- (BOOL)startWithConnecttedPeriphral:(CBPeripheral *)peripheral;
- (void)reSetNotifyStatusBeforeUnbind;
- (void)releasePeriphral;

- (NSArray <NSString *>*)serviceUUIDs;
- (NSArray <CBUUID *>*)discoverUuids;

- (NSString *)writeServiceUuid;
- (NSString *)writeCharacteristicUuid;
- (BOOL)isWriteResp;
- (void)setNotification:(CBPeripheral *)peripheral enable:(BOOL)enable andCharcater:(NSString *)character;
- (void)setNotification:(CBPeripheral *)peripheral enable:(BOOL)enable andService:(NSString *)service andCharcater:(NSString *)character;

- (dispatch_queue_t)bleQueue;
- (void)suspendCmdQueueAfterSendCmd:(SCQASCReObj)sRobj;
/* Call this methods when get finished with one commands*/
- (void)resumeCmdQueueAfterResponse;
- (void)releaseCmdQueueInUnbind;
- (NSInteger)timerDelaySeconds;
- (SCQASCReObj)scqascType:(NSString *)cmdStr;
- (NSDictionary *)scqascCmdsDict;

- (void)beginAfterNofityReady;
- (BOOL)checkoutConnectState;
- (BOOL)checkoutCWorkState:(NSString *)cmdHeader;

/**! Reveive Data*/
- (void)braceletCmdReceive:(NSData *)rceData;
- (void)braceletReceiveHRData:(NSInteger)hr;
- (dispatch_queue_t)bleResponseQueue;

- (void)writeToBracelet:(NSData *)writeData;
- (void)writeCharacteristicBysUUID:(NSString *)sUUID cUUID:(NSString *)cUUID data:(NSData *)data withResponse:(BOOL)with;

/*Protocol*/
- (void)registerBleQuinox:(id<DNBQuinox>)quinox;

@end
