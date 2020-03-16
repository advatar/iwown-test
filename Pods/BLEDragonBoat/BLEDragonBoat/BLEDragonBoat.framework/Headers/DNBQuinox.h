//
//  DNBQuinox.h
//  BLEDragonBoat
//
//  Created by A$CE on 2018/9/10.
//  Copyright © 2018年 A$CE. All rights reserved.
//

#import <Foundation/Foundation.h>
@class DNBBlePeripheral;
/**
 DicoverDeleagte，Response delegate methods in discover device.
 */
@protocol DnbDiscoverDelegate <NSObject>

@required

/**
 * This method is invoked while scanning
 
 @param iwDevice Instance contain a CBPeripheral object and the device's MAC address
 */
- (void)solsticeDidDiscoverDeviceWithMAC:(DNBBlePeripheral *)iwDevice;

/**
 * Search stopped
 */
- (void)solsticeStopScan;

@end

/**
 ConnectDeleagte，Response delegate methods in device connect method.
 */
@protocol DnbConnectDelegate <NSObject>

@required
/**
 *  invoked when the device did connected by the centeral
 *
 *  @param device the device did connected
 */
- (void)solsticeDidConnectDevice:(DNBBlePeripheral *)device;

@optional

/**
 Invoked when the device did disConnect with the connectted centeral
 
 @param device The device whom the centeral was connected
 @param error In most cases it is nil
 */
- (void)solsticeDidDisConnectWithDevice:(DNBBlePeripheral *)device andError:(NSError *)error;
/**
 Invoked when the device did fail to connected by the centeral
 
 @param device The device whom the centeral want to be connected
 @param error In most cases it is nil
 */
- (void)solsticeDidFailToConnectDevice:(DNBBlePeripheral *)device andError:(NSError *)error;

/**! Bluetooth state changed off.<##>*/
- (void)centralManagerStatePoweredOff;
/**! Bluetooth state changed on.<##>*/
- (void)centralManagerStatePoweredOn;

@end


@class DNBBattery;
@class DNBDeviceInfo;
@class DNBDataInfo;
@class DNBHealthData;
@protocol DNBQuinox <NSObject>

@required
/**! The handshake is completed, the initial setup is completed, and the App business logic can be executed.<##>*/
- (void)bleSolsticeIsReady;
/**! Update the device information callback, which is called when the device's Bluetooth address, model number, version information*/
- (void)bleSolsticeUpdateDeviceInfo:(DNBDeviceInfo *)deviceInfo;
/**! Battery information updated.*/
- (void)bleSolsticeUpdateBatteryLevel:(DNBBattery *)battery;

@optional
/**Return data information*/
- (void)updateNormalHealthDataInfo:(DNBDataInfo *)dInfo;
/**Return data.@See more in DNBHealthData*/
- (void)updateNormalHealthData:(DNBHealthData *)hData;
/**! Data synchronization progress, progress of a call to detailed data*/
- (void)responseDataProgress:(NSInteger)progress;
@end
