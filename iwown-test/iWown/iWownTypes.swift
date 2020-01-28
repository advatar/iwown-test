//
//  iWownTypes.swift
//  CareChain
//
//  Created by Johan Sellström on 2019-08-19.
//  Copyright © 2019 Apple. All rights reserved.
//

import Foundation
import BLEDragonBoat
import BLEProtoBuf

extension PBSDType {

    var name: String {
        switch self {

        case PBSDType_it_health:
            return "healthIndex"
        case PBSDType_it_gnss:
            return "gnssIndex"
        case PBSDType_it_ecg:
            return "ecgIndex"
        case PBSDType_it_ppg:
            return "ppgIndex"
        case PBSDType_it_rri:
            return "rriIndex"

        case PBSDType_dt_health:
            return "healthData"
        case PBSDType_dt_gnss:
            return "gnsshData"
       case PBSDType_dt_ecg:
            return "ecgData"
        case PBSDType_dt_ppg:
            return "ppgData"
        case PBSDType_dt_rri:
            return "rriData"

            
        case PBSDType_summary:
            return "summaryData"
        default:
            return "unknown"
        }
    }
}

public struct H: Codable {
    public let a: Int
    public let x: Int
    public let n: Int
}

public struct P: Codable {
    public let d: Int
    public let s: Int
    public let c: Int
    public let t: Int
}

public struct E: Codable {
    public let a: [Int]
}

public struct SleepPoint: Codable {
    public let E: E?
    public let H: H?
    public let P: P?
    public let Q: Int?
    public let T: [Int]?
}
