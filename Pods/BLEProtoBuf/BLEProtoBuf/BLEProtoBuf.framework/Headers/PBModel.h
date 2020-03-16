//
//  PBModel.h
//  BLEProtocBuff
//
//  Created by A$CE on 2019/3/18.
//  Copyright © 2019年 Iwown. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BLEDragonBoat/BLEDragonBoat.h>


NS_ASSUME_NONNULL_BEGIN

@interface PBModel : DNBModel

@end


@interface PBPersonalInfo : PBModel

@property (nonatomic ,assign) uint32_t height;
@property (nonatomic ,assign) uint32_t weight;
@property (nonatomic ,assign) uint32_t age;
@property (nonatomic ,assign) uint32_t gender;

@end


@interface PBBloodPressureConf : PBModel

/**! systolic pressure By Band 收缩压，手环测结果*/
@property (nonatomic ,assign) uint32_t syoicPsureBand;
/**! diastolic pressure By Band 舒张压*/
@property (nonatomic ,assign) uint32_t dsoicPsureBand;

/**! systolic pressure By Sphygmomanometer 收缩压，血压计测结果*/
@property (nonatomic ,assign) uint32_t syoicPsureSmeter;
/**! diastolic pressure By Sphygmomanometer*/
@property (nonatomic ,assign) uint32_t dsoicPsureSmeter;

@end


@interface PBHrAlarmConf : PBModel

/** Switch of this feature ,default is YES*/
@property (nonatomic ,assign) BOOL enable;
/** Alarm upper limit of heart rate, higher than this value to trigger alarm, the range of 50 ~ 200, the default 160*/
@property (nonatomic ,assign) uint32_t threshold_high;
/** Alarm lower limit of heart rate, lower than the value of the trigger alarm, the range of 40 ~ 190, the default 50*/
@property (nonatomic ,assign) uint32_t threshold_low;
/** Alarm detection time in seconds, the default 30*/
@property (nonatomic ,assign) uint32_t timerOut;
/** Alarm trigger interval, unit minutes, default 2*/
@property (nonatomic ,assign) uint32_t interval;

@end


@interface PBGoalOnceDay : PBModel

/**
 * The number of single day goal in step.
 */
@property (nonatomic ,assign) uint32_t stepOnceDay;

/**
 * The number of single day goal in calorie.
 */
@property (nonatomic ,assign) uint32_t calorieOnceDay;

@end


@interface PBGnssParam : PBModel
/*经度*/
@property (nonatomic ,assign) float latitude;
/*纬度*/
@property (nonatomic ,assign) float longitude;
/*海拔*/
@property (nonatomic ,assign) uint32_t altitude;

@end


@interface PBDNDModel : PBModel

/**
 When dndtype == DNDTypeNull, mean this smartBand has not set dnd model; you can also set dndType = 0 to close dnd model
 */
@property(nonatomic,assign)NSInteger dndType;

/**
 Value range of Hour：0~23
 Value range of Minute：0~59
 */
@property(nonatomic,assign)NSInteger startHour;
@property(nonatomic,assign)NSInteger startMinute;
@property(nonatomic,assign)NSInteger endHour;
@property(nonatomic,assign)NSInteger endMinute;

@end


@interface PBWeather : PBModel

@property (nonatomic,assign)NSInteger temp;
@property (nonatomic,assign)DNB_TempUnit unit;
@property (nonatomic,assign)DNB_WeatherType  type;
@property (nonatomic,assign)NSInteger pm;

@end


@interface PBDayWeather : PBModel

@property (nonatomic,assign)NSInteger tempMax;
@property (nonatomic,assign)NSInteger tempMin;
@property (nonatomic,assign)DNB_WeatherType type;
@property (nonatomic,assign)NSInteger pm;

@end


@interface PB24Weather : PBModel

@property (nonatomic,assign)NSInteger year;
@property (nonatomic,assign)NSInteger month;
@property (nonatomic,assign)NSInteger day;
@property (nonatomic,assign)NSInteger hour;

@property (nonatomic,assign)DNB_TempUnit unit;
/**! Groups numbers 24, means 24 hours weather data ,You must sort the data by date*/
@property (nonatomic,strong)NSArray <PBWeather *>*weather24Arrs;

@property (nonatomic,strong)NSArray <PBDayWeather *>*weather7Arrs;

@end


@interface PBRoll : PBModel
/**! rollId (hash_id): Please use an integer, the size should not exceed 0xFFFFFFFF*/
@property (nonatomic ,assign) NSInteger rId;

@property (nonatomic ,copy) NSString *rollName;

@end


@interface PBClock : PBModel

/**
 * Index of clock .Most device valiable range is 0～3, special device valiable range is 0～7
 */
@property (nonatomic ,assign) NSUInteger clockId;

/***
 * Description: Use a Byte number identify repeat day ,recycle by a week .Detail of every byte as follows ,use b7~b1 declared :
 * b7:Valid mark, b6:Satueday, b5:Friday, b4:Thursday, b3:Wednesday, b2:Tuesday, b1:Monday, b0:Sunday
 * 1 means on ,0 indicate off .
 */
@property (nonatomic ,assign) NSUInteger weekRepeat;
@property (nonatomic ,assign) NSUInteger clockHour;
@property (nonatomic ,assign) NSUInteger clockMinute;

/***
 * RingSetting
 */
@property (nonatomic ,assign) NSUInteger clockRingSetting;

@property (nonatomic ,assign) NSUInteger clockTipsLenth;

@property (nonatomic ,copy) NSString *clockTips;

@end

@interface PBSedentary : PBModel

/**
 * the state of reminder switch, default is NO ,means off.
 */
@property (nonatomic ,assign) BOOL switchStatus;

/*
 eg： @｛sedentaryId：0，startHour：8:00，endHour：12:00｝
 */
@property (nonatomic ,assign) NSUInteger sedentaryId;

/**
 * the repeats of sedentary ,to know more details to see @code weekRepeat methods。
 */
@property (nonatomic ,assign) NSUInteger weekRepeat ;

/**
 * the startTime of sedentary ,unit is hour .
 */
@property (nonatomic ,assign) NSUInteger startHour;

/**
 * the endTime of sedentary ,unit is hour .
 */
@property (nonatomic ,assign) NSUInteger endHour;

/**
 * the monitor duration ,unit is minute . your may demanded set a num is multiple of 5.
 * default duration is 60 minutes and threshold is 50 steps if you set both zero.
 * Special device support
 */
@property (nonatomic ,assign) NSUInteger sedentaryDuration;
@property (nonatomic ,assign) NSUInteger sedentaryThreshold;

/**
 *  Switch for ”No break during lunch break”. Default time in 12:00-14:00.
 */
@property (nonatomic ,assign) BOOL noDisturbing;

@end


@interface PBMotor : PBModel

@property (nonatomic,assign)DNB_ShakeType type;
@property (nonatomic,assign)DNB_ShakeWay modeIndex;
@property (nonatomic,assign)NSInteger shakeCount;

@end


@interface PBHWOption : PBModel

/**
 * switch of wrist gesture,default is YES.
 * 翻腕开关,默认为YES。
 */
@property (nonatomic ,assign) BOOL wristSwitch;
/**
 * Valid only when @ \ wristSwitch is YES, turning on the wrist lit screen function is available at set intervals. The value range is 0-24, indicating the whole hour.
 * 仅在 @\wristSwitch 为YES的时候有效，在设置的时间间隔内，翻腕点亮屏幕功能可用。取值范围在0-24，表示每个整点。
 */
@property (nonatomic, assign) NSInteger wristBlightStart;
@property (nonatomic, assign) NSInteger wristBlightEnd;

/**
 * switch of unitType changed ,default is UnitTypeInternational.
 * 公英制单位切换开关 ，默认是国际单位制。
  */
@property (nonatomic ,assign) DNB_UnitType unitType;

/**
 * switch of timeFlag changed ,default is TimeFlag24Hour.
 * 时间制式切换开关 ,默认是24小时制。
 */
@property (nonatomic ,assign) DNB_TimeFlag timeFlag;
/**
 * switch of what's language bracelet is used ,default is followed by iOS or use braceletLanguageDefault ,to know more about language that bracelet supported. @see braceletLanguage .
 * 手环使用的语言设置开关，默认设置受系统语言影响，未作适配的系统语言情况下为braceletLanguageDefault。
 */
@property (nonatomic ,assign) DNB_braceletLanguage language;
/**
 *  type formatter of date on smartband‘s screen ,0 means formatter is MM/dd ,type 1 means dd/MM .Default is 0
 *  手环显示的日期格式，0表示 月月／日日 ，1表示 日日／月月.默认是0
 */
@property (nonatomic, assign) NSInteger dateFormatter;

/**
 * switch of monitor heart rate automatilly ,turn off smart band would not motinor heart rate unless in sport time. default is YES .
 * 自动监测心率开关 ,关闭自动心率后非运动状态时不检测心率，默认为YES,。
 */
@property (nonatomic, assign) BOOL autoHeartRate;

/**
 * Switch used for control "Automatic recognition motion" feature
 * 自动运动识别
 */
@property (nonatomic ,assign) BOOL autoSport;

/** 0[default]: Celsius, 1: Fahrenheit */
@property (nonatomic ,assign) BOOL temperatureUnit;

/** 0[default]: left hand 惯用手 默认左手*/
@property (nonatomic,assign) BOOL leftHand;

@property (nonatomic ,copy) NSString *nickName;

@end


@interface PBSchedule : PBModel

@property(nonatomic,copy) NSString *title;

@property(nonatomic, strong) NSDate *date;

@end

@interface PBAfConfModel : PBModel

@property (nonatomic, assign) BOOL isAutoRun;

@property (nonatomic, assign) NSUInteger interval;

@end


NS_ASSUME_NONNULL_END
