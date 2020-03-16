//
//  DNBModel.h
//  BLEDragonBoat
//
//  Created by A$CE on 2019/4/1.
//  Copyright © 2019年 A$CE. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM (NSInteger,DNB_DNDType){
    DNDTypeNull = 0 ,         // mean closed dndMode
    DNDTypeSaveButNotShow ,
    DNDTypeNotSaveAndNotShow ,
};

typedef NS_ENUM(NSInteger,DNB_WeatherType) {
    WeatherFine = 0,            //晴
    WeatherCloudy = 1,          //多云
    WeatherOvercast = 2,        //阴天
    WeatherLightRain = 3,       //小雨
    WeatherModerateRain = 4,    //中雨
    WeatherHeavyRain = 5,       //大雨
    WeatherShower = 6,          //阵雨
    WeatherSnow = 7,            //雪
    WeatherHaze = 8,            //雾霾
    WeatherSandstorm = 9,       //沙尘暴
    WeatherSunCloud = 10,       //多云转晴
    WeatherThunderStorm = 11,   //雷雨
    WeatherNotContain = 0xff,
};

typedef NS_ENUM(NSInteger,DNB_TempUnit) {
    Centigrade = 0, //摄氏温度
    Fahrenheit = 1, //华氏温度
};

typedef NS_ENUM (NSInteger,DNB_ShakeType){
    ShakeTypeClock = 0,
    ShakeTypeCall = 1,
    ShakeTypeMsg = 2,
    ShakeTypeSedentary = 3,
    ShakeTypeCharging = 4,
    ShakeTypeSchedule = 5,
    ShakeTypeCommon = 6,
    ShakeTypeHRWarning = 7
};

typedef NS_ENUM (NSInteger,DNB_ShakeWay){
    ShakeWayStaccato = 4 ,  //断奏
    ShakeWayWave         ,  //波浪
    
    ShakeWayPitpat   = 7 ,  //心跳
    ShakeWayRadiate      ,  //放射
    
    ShakeWayLight    = 11,  //灯塔
    ShakeWaySymphony     ,  //交响乐
    
    ShakeWayRapid    = 15,  //快速
};

typedef enum {
    UnitTypeInternational = 0, // International units ,like km、meter、kg .国际制单位，如，千米 、米 、千克。
    UnitTypeEnglish            // Imperial units ,like feet、inch、pound .国际制单位，如，英尺 、英寸 、磅。
}DNB_UnitType;

typedef enum {
    TimeFlag24Hour = 0,
    TimeFlag12Hour
}DNB_TimeFlag;

typedef enum{
    braceletLanguageDefault = 0, //default is english equal @code braceletLanguageEnglish
    braceletLanguageEnglish = braceletLanguageDefault,// some smartband did not support it ,use braceletLanguageDefault if you don't want set in simple chinese.
    braceletLanguageSimpleChinese = 1,
    braceletLanguageItalian = 2,
    braceletLanguageJapanese = 3,
    braceletLanguageFrench = 4,
    braceletLanguageGerman = 5,
    braceletLanguagePortugal = 6,
    braceletLanguageSpanish = 7,
    braceletLanguageRussian = 8,
    braceletLanguageKorean = 9,
    braceletLanguageArabic = 10,
    braceletLanguageVietnamese = 11,
    braceletLanguagePolish = 12,
    braceletLanguageRomanian = 13,
    braceletLanguageSwedish = 14,
    braceletLanguageThai = 15,
    braceletLanguageTurkish = 16,
    braceletLanguageDanish = 17,
    braceletLanguageUkrainian = 18,
    braceletLanguageNorwegian = 19,
    braceletLanguageDutch = 20,
    braceletLanguageCzech = 21,
    braceletLanguageChineseTraditional = 22,
    braceletLanguageSimpleMarkings = 0xff, //This setting means no char ,all information replaced by figure. show simple icon only.
}DNB_braceletLanguage;


@interface DNBModel : NSObject

@end

NS_ASSUME_NONNULL_END
