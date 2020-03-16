//
//  BLEProtocBuf.h
//  AutumnTest
//
//  Created by A$CE on 2018/8/9.
//  Copyright © 2018年 A$CE. All rights reserved.
//

#import <BLEDragonBoat/BLEDragonBoat.h>
#import "SolsticePb.h"
#import "QuinoxPb.h"

@class PBDataHandle;
@interface BLEProtocBuff : DNBSolsticeImpl<SolsticePb>

@property (nonatomic ,strong) PBDataHandle *dataHandle;
@property (nonatomic ,weak) id<QuinoxPb> pbQuinox;

@end
