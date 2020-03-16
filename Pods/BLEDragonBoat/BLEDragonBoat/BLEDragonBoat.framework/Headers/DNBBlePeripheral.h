//
//  DNBBlePeripheral.h
//  BLELib3
//
//  Created by 曹凯 on 16/1/4.
//  Copyright © 2016年 ZR. All rights reserved.
//
@class CBPeripheral;
@class DNBBlePeripheral;

#import <Foundation/Foundation.h>

@protocol DNBBlePeripheralDelegate <NSObject>
/*private method*/
- (void)zrBlePeripheralDidDiscoverServices:(DNBBlePeripheral *)zrBP;

@end

@interface DNBBlePeripheral : NSObject
/**
 The CBPeripheral object provided by CoreBluetooth Framework.
 */
@property (nonatomic ,strong) CBPeripheral *cbDevice;
/**
 The device's MAC address
 */
@property (nonatomic ,strong) NSString *mediaAC;
/**
 * Received Signal Strength Indicator
 * 接收信号强度指示器
 */
@property (nonatomic ,strong) NSNumber *RSSI;

@property (nonatomic ,strong) NSString *uuidString;
@property (nonatomic ,strong) NSString *deviceName;
/**
 * 该设备所属协议
 */
@property (nonatomic ,strong) NSString *className;

/*服务UUID String*/
@property (nonatomic ,strong) NSArray <CBUUID *>*sUuidS;

@property (nonatomic ,weak) id<DNBBlePeripheralDelegate>zrpDelegate;

- (instancetype)initWith:(CBPeripheral *)cbPeripheral andAdvertisementData:(NSDictionary *)advertisementData andRSSINumber:(NSNumber *)rssi;
- (void)readSUuidS;

@end


@interface DNBDeviceInfo : NSObject
/**! Device Model<##>*/
@property (nonatomic ,strong) NSString *model;
/**! Version of firmware, formatter is A.B.C.D, like 1.0.2.32<##>*/
@property (nonatomic ,strong) NSString *version;
/**! BLE mac address. Unique identifier of the device*/
@property (nonatomic ,strong) NSString *bleAddr;

@end


@interface DNBBattery : NSObject
/**! Battery power level; 1~100*/
@property (nonatomic ,assign) NSInteger batLevel;
/**! 1-Charging, 2-normal, 0-Unascertainable*/
@property (nonatomic ,assign) NSInteger charging;

@end
