//
//  PBDataHealth.h
//  BLEProtocBuff
//
//  Created by A$CE on 2019/3/20.
//  Copyright © 2019年 Iwown. All rights reserved.
//

#import <BLEDragonBoat/BLEDragonBoat.h>

NS_ASSUME_NONNULL_BEGIN

@interface PBDataRtHealth : DNBHealthData
@property (nonatomic, assign)NSInteger step;
@property (nonatomic, assign)float     distance;
@property (nonatomic, assign)float     calorie;
@end


@interface PBDataHealth : DNBHealthData

//16进制   0010 0001=21
@property (nonatomic, assign)NSInteger data_type;
//10进制 运动类型 dnb_sd_sportType
@property (nonatomic, assign)NSInteger sport_type;
@property (nonatomic, assign)NSInteger step;
@property (nonatomic, assign)float     distance;    //单位：米
@property (nonatomic, assign)float     calorie;     //单位：千卡
//10进制，运动状态，1-开始，2-结束，3-暂停，4-运动持续中
@property (nonatomic, assign)NSInteger state_type;

//自动识别某项运动，开始前已经运动的一段时间（单位：分钟），大于0表示运动为自动识别
@property (nonatomic, assign)NSInteger pre_minute;
//心率
@property (nonatomic, assign)NSInteger min_bpm;
@property (nonatomic, assign)NSInteger max_bpm;
@property (nonatomic, assign)NSInteger avg_bpm;
//hrv相关参数
@property (nonatomic, assign)NSInteger level;
@property (nonatomic, assign)NSInteger sdnn;
@property (nonatomic, assign)NSInteger rmssd;
@property (nonatomic, assign)NSInteger pnn50;
@property (nonatomic, assign)NSInteger mean;
//疲劳度
@property (nonatomic, assign)NSInteger fatigue;
//血压，sbp-收缩压 ；dbp-舒张压
@property (nonatomic, assign)NSInteger sbp;
@property (nonatomic, assign)NSInteger dbp;
@property (nonatomic, assign)NSInteger bpm;
//睡眠数据，用于计算睡眠用的，需写入.json文件中
@property (nonatomic, strong) id sleepCmd;

@end


@interface PBDataGnss : DNBHealthData

@property (nonatomic, strong) NSString  *uid;
@property (nonatomic, assign) NSInteger freq;
@property (nonatomic, assign) NSInteger num;//经纬度个数
@property (nonatomic ,strong) NSArray *dataArray;//经纬度 数组

@end


@interface PBDataEcg : DNBHealthData

@property (nonatomic ,strong) NSArray *dataArray;

@end


@interface PBDataPpg : DNBHealthData

@property (nonatomic ,strong) NSArray *dataArray;

@end


@interface PBDataRri : DNBHealthData

@property (nonatomic ,strong) NSArray *dataArray;

@end

NS_ASSUME_NONNULL_END
