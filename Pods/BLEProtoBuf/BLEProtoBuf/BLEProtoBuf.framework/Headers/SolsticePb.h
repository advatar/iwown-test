//
//  SolsticePb.h
//  BLEProtocBuff
//
//  Created by A$CE on 2019/3/18.
//  Copyright © 2019年 Iwown. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef enum {
    /**! PBSDType_it ; data indextable*/
    PBSDType_it_health = 0x01,
    PBSDType_it_gnss,
    PBSDType_it_ecg,
    PBSDType_it_ppg,
    PBSDType_it_rri,
    
    /**! PBSDType_dt ; data detail<##>*/
    PBSDType_dt_health = 0x11,
    PBSDType_dt_gnss,
    PBSDType_dt_ecg,
    PBSDType_dt_ppg,
    PBSDType_dt_rri,
    
    PBSDType_summary = 0x70,
}PBSDType;

/**
 Device operation s events
 
 - BKN_SET_Normal: Reset
 - BKN_SET_SmartPhoto: Easy camera switch enter
 - BKN_GET_SmartPhoto: Easy camera switch action
 - BKN_GET_SearchPhone: Search phone action
 */
typedef NS_ENUM(NSInteger ,PB_BKeyNotify) {
    PB_BKN_SET_Normal = 0,
    PB_BKN_SET_SmartPhoto = 1,
    PB_BKN_GET_SmartPhoto = PB_BKN_SET_SmartPhoto,
    PB_BKN_GET_SearchPhone = 2,
};


typedef NS_ENUM(NSInteger ,PB_Error) {
    PB_ErrorNull = 0,
    PB_ErrorMissConnect = 0x01,
    PB_ErrorNotSupply = 0x02,
    PB_ErrorTimeOut = 0x04,
};

@class PBPersonalInfo;
@class PBBloodPressureConf;
@class PBHrAlarmConf;
@class PBGnssParam;
@class PBGoalOnceDay;
@class PBDNDModel;
@class PBRoll;
@class PB24Weather;
@class PBClock;
@class PBSchedule;
@class PBSedentary;
@class PBHWOption;
@class PBMotor;
@class PBAfConfModel;
@protocol SolsticePb <NSObject>

/**! Config of personal info setting in device, like height, weight, age and forth. Device has no way for correct arithmetic If not setting*/
- (void)setPersonalInfo:(PBPersonalInfo *)pi;

/**! Blood pressure calibration setting method<##>*/
- (void)setBloodPresureConf:(PBBloodPressureConf *)bpConf;

/**! Exercise heart rate alert setting*/
- (void)setEHRWParam:(PBHrAlarmConf *)ehrwp;
/**! Synchronization time*/
- (void)syscTime:(NSDate *)date;
/** Set GNSS location information*/
- (void)setGNSSParameter:(PBGnssParam *)gp;
/**! Switch config of atrial fibrillation detection method */
- (void)setAf24HourConfig:(PBAfConfModel *)afModel;
/** Set the target number of days and target calories on the day, a ring indicating the progress will be displayed on the home page of the device. If the device supports this method */
- (void)setTargetOnceDay:(PBGoalOnceDay *)target;
/**! Set don't disurb model*/
- (void)setDNDMode:(PBDNDModel *)dndModel;
/**
 Add a message blacklists .
 The contents of the blacklist agreement are as follows:
 The app writes the corresponding application package name (such as WeChat) to the hand ring through a specific protocol. The wristband performs blacklist filtering by using the package name from the data information received by the ANCS, and the application message that adds the blacklist is no longer displayed on the handband interface on.
 Notes:
 1. Due to limited bracelet space, only four blacklist applications are currently supported
 2. The factory does not set a blacklist
 3. Some custom firmware should be set to white list client requirements, iwown common version is set to blacklist
 Set the blacklist protocol as follows:
 Add
              "com.tencent.xin "- WeChat
              "com.tencent.mqq" - QQ
              "com.apple.mobilephone" - Incoming call
              "com.apple.MobileSMS" - message
 For more build identify for third part apps. use 【ios-deploy --id [udid] --list_bundle_id 】in Ternimal got them. Links:https://segmentfault.com/a/1190000010205616
 @code
             NSArray * arr = @ [@ "com.apple.mobilephone",
                                @ "com.apple.MobileSMS"
                                @ "com.tencent.mqq",
                                @ "com.tencent.xin"];
             NSMutableArray * mArr = [NSMutableArray arrayWithCapacity: 0];
             for (int i = 0; i <arr.count; i ++) {
                 ZeronerRoll * zRoll = [[ZeronerRoll alloc] init];
                 zRoll.rId = 100 + i;
                 zRoll.rollName = arr [i];
                 [mArr addObject: zRoll];
             }
             [[BLELib3 shareInstance] addSpecialList: mArr];
 @endcode
 @param sLists The blaklists
 */
- (void)addSpecialList:(NSArray <PBRoll *>*)sLists ;
- (void)clearAllLists;
/**! Set 24 hours weather data ,speacial devices support*/
- (void)set24Weathers:(PB24Weather *)weather;
/**! The device reserves a fixed number of alarm settings (usually eight), this method allows you to set the alarm one by one, the id of the alarm is a continuous natural number, do not exceed the allowable range, if the device has an alarm id 0x07, This is you add an alarm id is still 0x07, which is the total number of alarm clock in the device is still 1, that 0x07 alarm content will be your last set.
 Special device support, device in <BLEProtocol_Colorful> did not support this method ,use method setAlarmClocks:andSchedules: instead.
 @param clockModels alarm clock object.
 */
- (void)setAlarmClocks:(NSArray<PBClock *> *)clockModels;
/**! Same as Clocks*/
- (void)setBandSchedules:(NSArray<PBSchedule *> *)schedules;
/**! Set sedentary warning*/
- (void)setSedentary:(PBSedentary *)sedentaryModel;
/**! Setting device option*/
- (void)setDeviceOption:(PBHWOption *)deOption;
/** Set the vibration mode*/
- (void)setMotors:(NSArray<PBMotor *> *)motors;
/**! Experience the vibration<##>*/
- (void)feelMotor:(PBMotor *)motor;
/**! Read device Info.*/
- (void)readDeviceInfo;
/**! Read device battery.<##>*/
- (void)readDeviceBattery;
/*!
 * setKeyNotify 进入智拍模式设置1. 退出智拍模式设置0   // 通知拍照从 - (void)notifyToTakePicture; 获得
 * call this method to become smart photo or exits. set value 1 to active and set 0 to exit; get photoes @see - (void)notifyToTakePicture;
 */
- (void)setKeyNotify:(PB_BKeyNotify)keyNotify;
/**! Let device entry dfu*/
- (void)deviceUpgrade;

#pragma mark- PB_FileUpdate
/**! Send update request*/
- (void)startFileUpdate;
/****
 fuF.fd = (FUType)[dict[@"fd"] integerValue];
 fuF.fileName = dict[@"fileName"];
 fuF.fileSize = (uint32_t)[dict[@"fileSize"] integerValue];
 fuF.fileCrc32 = (uint32_t)[dict[@"fileCrc32"] integerValue];
 fuF.fileOffset = (uint32_t)[dict[@"fileOffset"] integerValue];
 fuF.crc32AtOffset = (uint32_t)[dict[@"crc32AtOffset"] integerValue];
 */
- (void)pbFileUpdateInit:(NSDictionary *)dict;
/****
 dataR.fd = (FUType)[dataDict[@"fd"] integerValue];
 dataR.fileOffset = (uint32_t)[dataDict[@"fileOffset"] integerValue];
 dataR.crc32AtOffset = (uint32_t)[dataDict[@"crc32AtOffset"] integerValue];
 dataR.buf = dataDict[@"buf"];
 */
- (void)pbFileUpdateData:(NSDictionary *)dataDict;
/**! 0-GPS, 1-FONT*/
- (void)pbFileUpdateExit:(NSInteger)fd;

/**! Mehtod to sysc data .
 @see startSpecialData:startSeq:endSeq:*/
- (void)startSpecialData:(PBSDType)sdType;
/**
 Synchronize the data method, incoming data from the updateNormalHealthDataInfo: method to get your specified time or type of data, the data is packaged in a fixed manner, based on the amount of data, some of the data we are packaged together, But there are some data as a separate data package
 
 @param sdType Type
 @param startSeq Some devices rely on Seq for their data continuity and require that they be passed in when they are synchronized. If you get startSeq & endSeq in your device info is 0, this means your device does not need this seq, Please also 0 value as a parameter to synchronize data, which is ok, or you can use the method does not need to pass in this parameter
 @see startSpecialData:withDate:
 @param endSeq Similar to startSeq.
 */
- (void)startSpecialData:(PBSDType)sdType startSeq:(NSInteger)startSeq endSeq:(NSInteger)endSeq;
@end

NS_ASSUME_NONNULL_END
