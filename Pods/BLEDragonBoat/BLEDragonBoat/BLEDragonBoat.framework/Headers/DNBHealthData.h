//
//  DNBHealthData.h
//  BLE3Framework
//
//  Created by 曹凯 on 16/10/12.
//  Copyright © 2016年 ZR. All rights reserved.
//
#import <Foundation/Foundation.h>

/***
 *  Sport Type
 *  数据所属运动模式
 */
typedef NS_ENUM(NSInteger, dnb_sd_sportType) {
    SD_SPORT_TYPE_SLEEP                          = 0x00 ,//睡眠
    
    SD_SPORT_TYPE_WALKING                        = 0x01 ,//走路
    SD_SPORT_TYPE_NORMAL_MODE                    = 0x01 ,//彩屏非运动模式
    SD_SPORT_TYPE_SITE_UPS                       = 0x02 ,//仰卧起坐
    SD_SPORT_TYPE_PUSH_UP                        = 0x03 ,//俯卧撑
    SD_SPORT_TYPE_ROPE_SKIPPING                  = 0x04 ,//跳绳
    SD_SPORT_TYPE_MOUNTAINEERING                 = 0x05 ,//登山
    SD_SPORT_TYPE_PULL_UP                        = 0x06 ,//引体向上
    SD_SPORT_TYPE_RUNNING                        = 0x07 ,//跑步
    SD_SPORT_TYPE_APP_JIANMEICAO                 = 0x08 ,//健美操
    
    SD_SPORT_TYPE_CRUNCHES                       = 0x09 ,//卷腹
    SD_SPORT_TYPE_DEEP_SQUAT                     = 0x0a ,//深蹲
    SD_SPORT_TYPE_AIR_PEDAL                      = 0x0b ,//空中蹬车
    SD_SPORT_TYPE_HIP_BRIDGE                     = 0x0c ,//臀桥
    SD_SPORT_TYPE_DUMB_BELL                      = 0x0d ,//哑铃锻炼
    SD_SPORT_TYPE_APP_KAIHETIAO                  = 0x0e ,//开合跳
    SD_SPORT_TYPE_APP_JIANBUDUN                  = 0x0f ,//箭步蹲
    SD_SPORT_TYPE_SLIMMING_EXERCISE              = 0x10 ,//蹦床
    SD_SPORT_TYPE_CLIMB_STAIRS                   = 0x11 ,//爬楼梯
    
    SD_SPORT_TYPE_APP_BUYU                       = 0x12 ,//捕鱼
    SD_SPORT_TYPE_APP_SHOULIE                    = 0x13 ,//狩猎
    SD_SPORT_TYPE_APP_JIAWU                      = 0x14 ,//家务活动
    SD_SPORT_TYPE_APP_JIATINGXIULI               = 0x15 ,//家庭修理
    SD_SPORT_TYPE_APP_ANJINGBUDONG               = 0x16 ,//安静不动
    SD_SPORT_TYPE_APP_XUEXI                      = 0x17 ,//学习
    SD_SPORT_TYPE_APP_CAOPINGTINGXUE             = 0x18 ,//草坪庭院
    SD_SPORT_TYPE_APP_JIAOTAN                    = 0x19 ,//交谈
    SD_SPORT_TYPE_APP_YUEQIYANZOU                = 0x1a ,//乐器演奏
    SD_SPORT_TYPE_APP_ZHIYEHUODONG               = 0x1b ,//职业活动
    SD_SPORT_TYPE_APP_ZILIHUODONG                = 0x1c ,//自理活动
    SD_SPORT_TYPE_APP_XINGSHENGHUO               = 0x1d ,//性生活
    SD_SPORT_TYPE_APP_XIUXIAN                    = 0x1e ,//休闲
    
    SD_SPORT_TYPE_APP_GONGLVZIXINGCHE            = 0x91 ,//功率自行车
    SD_SPORT_TYPE_APP_TABUJI                     = 0x92 ,//踏步机
    SD_SPORT_TYPE_APP_HUABAN                     = 0x93 ,//滑板
    SD_SPORT_TYPE_APP_PULATI                     = 0x94 ,//普拉提
    SD_SPORT_TYPE_APP_SHIPINYUNDONG              = 0x95 ,//视频运动
    SD_SPORT_TYPE_APP_TAIQIU                     = 0x96 ,//台球
    SD_SPORT_TYPE_APP_QUANJI                     = 0x97 ,//拳击
    SD_SPORT_TYPE_APP_JIANLIAN                   = 0x98 ,//教练
    SD_SPORT_TYPE_APP_ZHIBIAO                    = 0x9a ,//掷镖
    SD_SPORT_TYPE_APP_TUOLABISAI                 = 0x9b ,//拖拉比赛
    SD_SPORT_TYPE_APP_JIANSHU                    = 0x9c ,//剑术
    SD_SPORT_TYPE_APP_GANLANQIU                  = 0x9d ,//橄榄球
    SD_SPORT_TYPE_APP_FEIPAN                     = 0x9e ,//飞盘
    SD_SPORT_TYPE_APP_GAOERFU                    = 0x9f ,//高尔夫
    SD_SPORT_TYPE_APP_TICAO                      = 0xa0 ,//体操
    SD_SPORT_TYPE_APP_SHOUQIU                    = 0xa1 ,//手球
    SD_SPORT_TYPE_APP_HUAXIANG                   = 0xa2 ,//滑翔
    SD_SPORT_TYPE_APP_QUGUNQIU                   = 0xa3 ,//曲棍球
    SD_SPORT_TYPE_APP_BINGQIU                    = 0xa4 ,//冰球
    SD_SPORT_TYPE_APP_QIMA                       = 0xa5 ,//骑马
    SD_SPORT_TYPE_APP_HUILIQIU                   = 0xa6 ,//回力球
    SD_SPORT_TYPE_APP_WUSHU                      = 0xa7 ,//武术
    SD_SPORT_TYPE_APP_YUEYE                      = 0xa8 ,//越野
    SD_SPORT_TYPE_APP_BANQIU                     = 0xa9 ,//板球
    SD_SPORT_TYPE_APP_MANQIU                     = 0xaa ,//马球
    SD_SPORT_TYPE_APP_TIAOSAN                    = 0xab ,//跳伞
    SD_SPORT_TYPE_APP_LEIQIU                     = 0xac ,//垒球
    SD_SPORT_TYPE_APP_BIQIU                      = 0xad ,//壁球
    SD_SPORT_TYPE_TAIJI                          = 0xae ,//太极
    SD_SPORT_TYPE_APP_SHUAIJIAO                  = 0xaf ,//摔跤
    SD_SPORT_TYPE_APP_JIAOSHI                    = 0xb0 ,//驾驶
    SD_SPORT_TYPE_APP_SHEJIAN                    = 0xb1 ,//射箭
    SD_SPORT_TYPE_BRISK_WALKING                  = 0xb5 ,//快走
    SD_SPORT_TYPE_APP_JIACHUAN                   = 0xb6 ,//驾船
    SD_SPORT_TYPE_APP_PIHUATING                  = 0xb7 ,//皮划艇
    SD_SPORT_TYPE_APP_FANCHUAN                   = 0xb8 ,//帆船
    SD_SPORT_TYPE_APP_HUASHUI                    = 0xb9 ,//滑水
    SD_SPORT_TYPE_APP_QIANSHUI                   = 0xba ,//潜水
    SD_SPORT_TYPE_APP_CHONGLANG                  = 0xbb ,//冲浪
    SD_SPORT_TYPE_APP_SHUIQIU                    = 0xbc ,//水球
    SD_SPORT_TYPE_APP_TIAOXUE                    = 0xbd ,//跳雪
    SD_SPORT_TYPE_APP_XUEQIAO                    = 0xbe ,//雪橇
    SD_SPORT_TYPE_APP_XUESHANGQICHE              = 0xbf ,//雪上骑车
    SD_SPORT_TYPE_APP_TIAOSHUI                   = 0xc0 ,//跳水
    
    SD_SPORT_TYPE_MASK                           = 0x80 ,//掩码
    
    SD_SPORT_TYPE_GROUPCLASS                     = 0x30 ,//团课
    SD_SPORT_TYPE_PERSONALEDUCATION              = 0x31 ,//私教
    SD_SPORT_TYPE_TREADMILL                      = 0x32 ,//跑步机
    SD_SPORT_TYPE_FREETRAINING                   = 0x33 ,//自由训练
    SD_SPORT_TYPE_BADMINTON                      = 0x80 ,//羽毛球
    SD_SPORT_TYPE_BASKETBALL                     = 0x81 ,//篮球
    SD_SPORT_TYPE_FOOTBALL                       = 0x82 ,//足球
    SD_SPORT_TYPE_SWIM                           = 0x83 ,//游泳
    SD_SPORT_TYPE_VOLLEYBALL                     = 0x84 ,//排球
    SD_SPORT_TYPE_TABLE_TENNIS                   = 0x85 ,//乒乓球
    SD_SPORT_TYPE_BOWLING                        = 0x86 ,//保龄球
    SD_SPORT_TYPE_TENNIS                         = 0x87 ,//网球
    SD_SPORT_TYPE_CYCLING                        = 0x88 ,//骑行
    SD_SPORT_TYPE_SKI                            = 0x89 ,//滑雪
    SD_SPORT_TYPE_SKATE                          = 0x8a ,//滑冰
    SD_SPORT_TYPE_ROCK_CLIMBING                  = 0x8b ,//攀岩
    SD_SPORT_TYPE_GYM                            = 0x8c ,//健身房健身
    SD_SPORT_TYPE_DANCE                          = 0x8d ,//跳舞
    SD_SPORT_TYPE_TABLET_SUPPORT                 = 0x8e ,//平板撑
    SD_SPORT_TYPE_GYM_EXERCISE                   = 0x8f ,//健身操
    SD_SPORT_TYPE_YOGA                           = 0x90 ,//瑜伽
    SD_SPORT_TYPE_SHUTTLECOCK                    = 0x91 ,//毽球
    SD_SPORT_TYPE_ALLBALL                        = 0x92 ,//所有球类
    SD_SPORT_TYPE_POWALKING                      = 0x93 ,//健步走
    SD_SPORT_TYPE_GOLF                           = 0x94 ,//高尔夫
    SD_SPORT_TYPE_CANOEING                       = 0x95 ,//皮划艇
    
    SD_SPORT_TYPE_HEART_RATE                     = 0xf0 ,//心率
    
    SD_SPORT_TYPE_OTHER                          = 0xFF ,//其他'
    SD_SPORT_TYPE_WALKING_SAVE                   = 0x100 ,//步行
} ;

typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
}DNB_RecorDate;

typedef struct {
    DNB_RecorDate rcDate;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
}DNB_RecortDate;

typedef struct {
    uint16_t seqStart;
    uint16_t seqEnd;
    DNB_RecortDate storeDate;
}DNB_DateDataInfo;

typedef struct {
    uint8_t dataType;
    uint8_t totaldays;
    DNB_DateDataInfo ddInfos[7];
}DNB_TDateStoreInfo;

@interface DNBDDInfo : NSObject

+ (instancetype)objectFrom:(DNB_DateDataInfo)ddInfo;
@property (nonatomic ,strong) NSDate *date;
@property (nonatomic ,assign) NSInteger seqStart;
@property (nonatomic ,assign) NSInteger seqEnd;

@end


@interface DNBDataInfo : NSObject

@property (nonatomic ,strong) NSArray <DNBDDInfo *> *ddInfos;
@property (nonatomic ,assign) NSUInteger dataType;

- (NSArray <NSDate *>*)getDateArray;

@end


@interface DNBHealthData : NSObject
/**! Sequence number*/
@property (assign ,nonatomic) NSInteger seq;
/**! Specifical data type*/
@property (nonatomic ,assign) NSInteger sdType;
/**! Timestamp of data*/
@property (strong ,nonatomic) NSDate *recordDate;
/**! Device name*/
@property (class, copy ,nonatomic)NSString *dataFrom;

@end
