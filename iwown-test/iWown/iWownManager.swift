//
//  iWownManager.swift
//  CareChain
//
//  Created by Johan Sellström on 2019-08-17.
//  Copyright © 2019 Apple. All rights reserved.
//

import UIKit

import BLEDragonBoat
import BLEProtoBuf

protocol WatchDelegate {
    func didConnect(model: String, version: String)
    func hasInfo(_ dInfo: DNBDataInfo)
    func connectionFailed()
    func isReady()
    func sequenceComplete(sequences: [DNBHealthData])
    func retry()
    func updateProgress(_ progress: Int)
    func batteryInfo(level: Int, charging: Bool)
    func discovered(watches: [DNBBlePeripheral])
}

public protocol DeviceDelegate {
    func isConnecting()
    func fail()
    func connected(info: String)
    func progress(_ progress: Int)
    func batteryInfo(level: Int, charging: Bool)
    func synchronized()
    func discovered(watches: [DNBBlePeripheral])

}

public protocol DeviceManager {
    func connect(viewController: UIViewController?, callback: @escaping (Bool) -> Void)
    func connect()
    func disconnect()
    func synchronize()
    var isConnected: Bool { get }
    var hasDevice: Bool { get }
}


class StartVibrator: PBMotor {
    override init() {
        super.init()
        type = DNB_ShakeType.ShakeTypeMsg
        modeIndex = DNB_ShakeWay.ShakeWayLight
        shakeCount = 1
    }
}

class DoneVibrator: PBMotor {
    override init() {
        super.init()
        type = DNB_ShakeType.ShakeTypeClock
        modeIndex = DNB_ShakeWay.ShakeWaySymphony
        shakeCount = 1
    }
}


public class IWownManager: NSObject, DeviceManager, WatchDelegate {
    

    var delegate: DeviceDelegate?
    var dInfo: DNBDataInfo = DNBDataInfo()
    var retries = 0
    var eventIndex = 0
    var typeIndex = 0
    var config = Config()
    
    // var indexTypes = [PBSDType_it_ppg]
    // var indexTypes = [PBSDType_it_health]
    // var indexTypes = [PBSDType_summary]
    // var indexTypes = [PBSDType_it_rri]
    // var indexTypes = [PBSDType_it_ecg]

    var indexTypes = [PBSDType_it_ecg, PBSDType_it_health,  PBSDType_it_rri]

    private var didConnect: Bool = false

    var ble = BLEController.shared


    // MARK: WatchDelegate

     func didConnect(model: String, version: String) {
        print("\(model) \(version)")
        didConnect = true
        delegate?.connected(info: model + " " + version)
     }

     func hasInfo(_ dInfo: DNBDataInfo) {
        self.dInfo = dInfo
        
        let indexType = PBSDType(rawValue: UInt32(dInfo.dataType))
        print("*** Events *** for \(indexType.name) \(dInfo) ")
        nextEvent()
     }

     func connectionFailed() {
         didConnect = false
         delegate?.fail()
     }

    func discovered(watches: [DNBBlePeripheral]) {
        delegate?.discovered(watches: watches)
    }
    
     private var readyCount = 0
    
     func isReady() {

        print("isReady")
        if readyCount == 1 {
            delegate?.progress(0)
            nextType()
        }
        readyCount += 1

     }

     func retry() {
        let type = indexTypes[typeIndex-1]
        didConnect = false
        if retries < 3 {
            retries += 1
            print("RETRY # \(retries) for \(type.name)")
            synchronize()
        } else {
            delegate?.fail()
        }
        
        /*isRetrying = true
        //didConnect = false
        print("Retrying")
        eventIndex -= 1
        //nextEvent()
        
        ble.reconnect()*/
     }

     func updateProgress(_ progress: Int) {
        //print(progress)
        delegate?.progress(progress)
     }

    func batteryInfo(level: Int, charging: Bool) {
        delegate?.batteryInfo(level: level, charging: charging)
    }

    public func connect() {

        if didConnect {
            return
        }

        if hasDevice {
                print("Reconnecting watch")
                ble.reconnect()
        } else {
                print("Scanning for watch")
                ble.startScan()
        }

    }

    public func connect(viewController: UIViewController?, callback: @escaping (Bool) -> Void) {
        callback(true)
    }

    public func disconnect() {
        config.watchuuidString = nil
        didConnect = false
    }

    public func synchronize()  {
        connect()
    }

    public var isConnected: Bool {
        return didConnect
    }

    public var hasDevice: Bool {
         return config.watchuuidString != nil
    }

    public static var shared = IWownManager()

    override private init() {
        super.init()

        //log.verbose("Logging to \(ble.bleLogPath()!)")
        ble.watchDelegate = self

    }


    func sequenceComplete(sequences: [DNBHealthData]) {

        print("SYNC sequenceComplete \(eventIndex) ")

        let trueIndex = eventIndex - 1

        guard trueIndex <= dInfo.ddInfos.count, trueIndex >= 0  else {
            print("SYNC Index")
            return
        }

        print("SYNC using \(eventIndex) ")

        let info = dInfo.ddInfos[trueIndex]

        guard let date = info.date, let first = sequences.first else { return }
        let indexType = PBSDType(rawValue: UInt32(dInfo.dataType))

        print("SYNC \(indexType.name) event has \(sequences.count) sequences for \(info.date.description)")

        let sdType = first.sdType

        print("SYNC \(dInfo)")


        if sdType == PBSDType_dt_ppg.rawValue {
            for sequence in sequences {
                if let recordedDate = sequence.recordDate, let ppgData = sequence as? PBDataPpg, let array = ppgData.dataArray as? [NSNumber] {
                    print("PPG date \(recordedDate)")
                    print("PPG num values \(array.count)")
                    //print("PPG array \(array)")
                }
            }
        } else if sdType == PBSDType_dt_rri.rawValue {
            var points = [CGPoint]()
            var rriArray = [Double]()
            for sequence in sequences {
                if let rriData = sequence as? PBDataRri, let array = rriData.dataArray as? [NSNumber] {
                    for i in 0..<array.count/2 {
                        let x = array[2*i].intValue
                        let y = array[2*i+1].intValue
                        // a very crude filter
                        if x < 60000 && y < 60000 && x > 400 && y > 400 {
                            let point = CGPoint(x: x, y: y)
                            points.append(point)
                            let rri = 2.0*Double(y-x)/Double(y+x)
                            rriArray.append(rri)
                        }
                    }
                }
            }
            
            points.append(CGPoint(x:0,y:0))
            points.append(CGPoint(x:2000,y:2000))
            
            print("RRI")
        
            print(points)

        } else if sdType == PBSDType_dt_ecg.rawValue {
            var points = [CGPoint]()
            var i = 0
            print("ECG Dump")
            for sequence in sequences {
                if /*let recordedDate = sequence.recordDate,*/ let ecgData = sequence as? PBDataEcg {
                    //print(recordedDate)
                    for data in ecgData.dataArray as! [NSNumber] {
                        let volt = Int(data.uint8Value)
                        //print(volt)
                        let point = CGPoint(x: i, y: volt)
                        points.append(point)
                        i += 1
                    }
                }
            }
            print(points)

        } else if sdType == PBSDType_dt_health.rawValue {

            // Sleep Quality
            var jsonArr = [JSON]()
            // Average Heart Rate
            var points = [CGPoint]()
            let startOfDay = Calendar.current.startOfDay(for: date)
            let endOfDay = Calendar.current.date(byAdding: DateComponents(day: 1, second: -1), to: startOfDay)!
            points.append(CGPoint(x:startOfDay.timeIntervalSince1970 ,y: 0.0))
            for sequence in sequences {
                if let recordedDate = sequence.recordDate, let healthData = sequence as? PBDataHealth   {

                    //print(healthData.sleepCmd)

                    let bpm = healthData.avg_bpm
                    if bpm > 0 {
                        let point = CGPoint(x: recordedDate.timeIntervalSince1970, y: Double(bpm))
                        points.append(point)
                    }

                    // Sleep Quality
                    if let jsonObj = healthData.sleepCmd as? JSON {
                        jsonArr.append(jsonObj)
                    }

                }
            }
            
            print("BPM")
            
            print(points)

        }

        self.nextEvent()

    }

    func nextType()  {
        ble.solstice?.pbFileUpdateInit([:])
        ble.solstice?.startFileUpdate()
        let motor = StartVibrator()
        ble.solstice?.feel(motor)
        eventIndex = 0
        if typeIndex < indexTypes.count && typeIndex >= 0  {
            let type = indexTypes[typeIndex]
            print("Download all recent \(type.name) \(type) events")
            ble.solstice?.startSpecialData(type)
            typeIndex += 1
        } else {
            let motor = DoneVibrator()
            ble.solstice?.feel(motor)
            delegate?.synchronized()
            print("Download complete")
        }
    }


    func nextEvent() {

        if eventIndex < dInfo.ddInfos.count && eventIndex >= 0 {
            let info = dInfo.ddInfos[eventIndex]
            self.ble.lastSequenceNumberOfEvent = info.seqEnd
            let dataType = PBSDType(rawValue: UInt32(self.dInfo.dataType) + 0x10)
            self.ble.solstice?.startSpecialData(dataType, startSeq: info.seqStart, endSeq: info.seqEnd)
            self.eventIndex += 1
        } else {
            nextType()
        }
    }

}
