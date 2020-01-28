//
//  ViewController.swift
//  Watch
//
//  Created by Johan Sellström on 2019-06-14.
//  Copyright © 2019 Johan Sellström. All rights reserved.
//

import UIKit
import BLEDragonBoat
import BLEProtoBuf


let heartRateServiceCBUUID = CBUUID(string: "0x180D")
let heartRateMeasurementCharacteristicCBUUID = CBUUID(string: "2A37")
let bodySensorLocationCharacteristicCBUUID = CBUUID(string: "2A38")
let iwownCharacteristicCBUUID = CBUUID(string: "2E8C0001-2D91-5533-3117-59380A40AF8F")

public protocol DeviceConnectorDelegate {
    func connect()
}

class BLEController: NSObject, DnbConnectDelegate, DnbDiscoverDelegate, DNBBlePeripheralDelegate,CBPeripheralDelegate, DNBSolsticeImplDelegate, DNBSolsticeImplConnectDeleagte {

    static let shared: BLEController =  BLEController()
    var config = Config()
    var discoveredWatches = [DNBBlePeripheral]()
    var healthData = [DNBHealthData]()
    var lastSequenceNumberOfEvent = 0
    var watchDelegate: WatchDelegate?
    var dragon: BLEDragon!
    var solstice: BLEProtocBuff?

    func connectDidLosedAndReConnectSoon() {
        print("connectDidLosedAndReConnectSoon")
    }

    func thereIsSomeCmdGotTimeOut(_ sRobj: SCQASCReObj) {

        var type: String  {
            switch sRobj.type {
            case SCQASCTypeNull:
                return "NULL"
            case SCQASCTypeFirst,SCQASCTypeNormal:
                return "Normal"
            case SCQASCTypeResumeNow:
                return "Resume Now"
            case SCQASCTypeResponseTimeOut:
                return "Response"
            case SCQASCTypeLast:
                return "Last"
            default:
                return "unknown"
            }
        }

        var value: String  {
            switch sRobj.value {
            case SCQASCValueNull:
                return "Null"
            case SCQASCValueFirst:
                return "First"
            case SCQASCValueIndexTable, SCQASCValueFirst:
                return "IndexTable"
            case SCQASCValueDetail:
                return "Detail"
            case SCQASCValueLast:
                return "Last"
            default:
                return "unknown"
            }
        }

        print("Timeout \(type) \(value)")
        watchDelegate?.retry()
    }



    override private init() {
        super.init()
        //dragon = BLEDragon.dragonBoat()
        dragon = BLEDragon.dragonBoatWithOutBackMode()
        dragon.discoverDelegate = self
        dragon.connectDelegate = self
    }

    func startScan() {
        guard dragon != nil else {
            return
        }
        dragon.startScan(forTimeInternal: 30, andServiceUuids: [heartRateServiceCBUUID.uuidString, iwownCharacteristicCBUUID.uuidString])
    }

    func stopScan() {

        guard dragon != nil else {
            return
        }

        dragon.stopScan()
    }

    func reconnect() {
        if let uuidString = config.watchuuidString, dragon != nil {
            dragon.recoverConnect(uuidString)
        }
    }

    func peripheralDidUpdateName(_ peripheral: CBPeripheral) {
        print("peripheralDidUpdateName", peripheral.name ?? "")
    }


    func zrBlePeripheralDidDiscoverServices(_ zrBP: DNBBlePeripheral!) {
        print("Discovered \(zrBP.cbDevice.services ?? [] )")
    }

    // MARK: DnbConnectDelegate

    // required
    func solsticeDidConnectDevice(_ device: DNBBlePeripheral!) {
        solstice = dragon.solstice(withConnectedPeripheral: device) as? BLEProtocBuff
        dragon.stopScan()
        config.watchuuidString = device.uuidString
        solstice?.registerDeviceDelegate() //
        solstice?.registerBleQuinox(self) // ??
        solstice?.registerEquinox(self as QuinoxPb)
        solstice?.beginAfterNofityReady() //
        solstice?.implConnectDelegate = self
        solstice?.implDelegate = self
        device.zrpDelegate = self
        //device.cbDevice.delegate = self //
        print("Getting Power State")
        dragon.readManagerPowerState()

        solstice?.braceletReceiveHRData(100)

        solstice?.resumeCmdQueueAfterResponse()

        let dataHandle = DNBDataHandle()

            //dataHandle.bleSolstice = solstice.
        dataHandle.braceletReceiveHRData(10)

     }

    // optional

    func solsticeDidFail(toConnectDevice device: DNBBlePeripheral!, andError error: Error!) {
        print("solsticeDidFail \(error!)")
        watchDelegate?.connectionFailed()
    }

    func solsticeDidDisConnect(withDevice device: DNBBlePeripheral!, andError error: Error!) {
        if let device = device {
            if let error = error {
                print("solsticeDidDisConnect \(device) \(error)")
            } else {
                print("solsticeDidDisConnect \(device)")
            }
        }
    }

    func centralManagerStatePoweredOn() {
        print("centralManagerStatePoweredOn")
    }

    func centralManagerStatePoweredOff() {
        print("centralManagerStatePoweredOff")
    }


    func foundNewWatches(_ watches: [DNBBlePeripheral]) {
        watchDelegate?.discovered(watches: watches)
    }

    // MARK: DnbDiscoverDelegate

    func solsticeDidDiscoverDevice(withMAC iwDevice: DNBBlePeripheral!) {

        if let deviceName = iwDevice.deviceName {
            print("Discovered \(deviceName)")
            discoveredWatches.append(iwDevice)
            watchDelegate?.discovered(watches: discoveredWatches)
        }

     }

    func solsticeStopScan() {
        print("solsticeStopScan")
        stopScan()
        if solstice == nil {
            watchDelegate?.connectionFailed()
        }
        foundNewWatches(discoveredWatches)
    }


    // MARK: CBPeripheralDelegate

    func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: Error?) {
        print("*******************")
        print("didDiscoverCharacteristicsFor \(service)")

        guard let characteristics = service.characteristics else { return }

        for characteristic in characteristics {
            print(characteristic.uuid,characteristic.properties, characteristic.isNotifying)
            if characteristic.properties.contains(.read) {
                print("\(characteristic.uuid): properties contains .read")
                peripheral.readValue(for: characteristic)
            }

            if characteristic.properties.contains(.notify) {
                print("\(characteristic.uuid): properties contains .notify")
                peripheral.setNotifyValue(true, for: characteristic)
                print("setNotifyValue enable")
            }

        }

    }

    func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
        print("didDiscoverServices", peripheral.services ?? "")

        for service in peripheral.services! {
            print("didDiscoverServices ", service)
            peripheral.discoverCharacteristics(nil, for: service)
        }
    }

    func peripheral(_ peripheral: CBPeripheral, didUpdateValueFor characteristic: CBCharacteristic, error: Error?) {
        
        switch characteristic.uuid {
        case bodySensorLocationCharacteristicCBUUID:
            let bodySensorLocation = bodyLocation(from: characteristic)
            print("bodySensorLocation \(bodySensorLocation)")
        case heartRateMeasurementCharacteristicCBUUID:
            let bpm = heartRate(from: characteristic)
            print("Current bpm \(bpm)")
        case iwownCharacteristicCBUUID:
            print("iWown Watch")
            handleIwown(from: characteristic)
        default:
            otherData(from: characteristic)
            print("Unhandled Characteristic UUID: \(characteristic.uuid)")
        }
    }

    private func bodyLocation(from characteristic: CBCharacteristic) -> String {
        guard let characteristicData = characteristic.value,
            let byte = characteristicData.first else { return "Error" }
        switch byte {
        case 0: return "Other"
        case 1: return "Chest"
        case 2: return "Wrist"
        case 3: return "Finger"
        case 4: return "Hand"
        case 5: return "Ear Lobe"
        case 6: return "Foot"
        default:
            return "Reserved for future use"
        }
    }

    private func handleIwown(from characteristic: CBCharacteristic) {
        guard let characteristicData = characteristic.value  else { return }
        let byteArray = [UInt8](characteristicData)
        print("handleIwown \(byteArray)")
    }

    private func otherData(from characteristic: CBCharacteristic) {
        guard let characteristicData = characteristic.value  else { return }
        let byteArray = [UInt8](characteristicData)
        
        if let descriptors = characteristic.descriptors {
            print(descriptors)
        }
        print("otherData \(byteArray)")
    }

    private func heartRate(from characteristic: CBCharacteristic) -> Int {
        guard let characteristicData = characteristic.value else { return -1 }
        let byteArray = [UInt8](characteristicData)
        // See: https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.characteristic.heart_rate_measurement.xml
        // The heart rate mesurement is in the 2nd, or in the 2nd and 3rd bytes, i.e. one one or in two bytes
        // The first byte of the first bit specifies the length of the heart rate data, 0 == 1 byte, 1 == 2 bytes

        let firstBitValue = byteArray[0] & 0x01
        if firstBitValue == 0 {
            // Heart Rate Value Format is in the 2nd byte
            return Int(byteArray[1])
        } else {
            // Heart Rate Value Format is in the 2nd and 3rd bytes
            return (Int(byteArray[1]) << 8) + Int(byteArray[2])
        }
    }

    var bleLogPath: String {
          let foldPath:String = NSHomeDirectory() + "/Documents"
          let logFilePath = foldPath + "/BLE.txt";
          return logFilePath;
      }
}

extension DNBSolsticeImpl {

   var bleLogPath: String {
        let foldPath:String = NSHomeDirectory() + "/Documents"
        let logFilePath = foldPath + "/BLE.txt";
        return logFilePath;
    }

}

extension BLEController: QuinoxPb {


     public func bleSolsticeIsReady() {
        solstice?.readDeviceInfo()
        solstice?.readDeviceBattery()
        watchDelegate?.isReady()
    }

    public func bleSolsticeUpdate(_ deviceInfo: DNBDeviceInfo!) {
        watchDelegate?.didConnect(model: deviceInfo.model ?? "", version: deviceInfo.version ?? "" )
    }


    public func bleSolsticeUpdateBatteryLevel(_ battery: DNBBattery!) {
        watchDelegate?.batteryInfo(level: battery.batLevel, charging: battery?.charging == 1)
    }

    public func updateNormalHealthData(_ hData: DNBHealthData!) {
        healthData.append(hData)
        if hData.seq == lastSequenceNumberOfEvent - 1 {
            watchDelegate?.sequenceComplete(sequences: healthData)
            healthData = []
        }
    }

     public func updateNormalHealthDataInfo(_ dInfo: DNBDataInfo!) {
        print(PBSDType_it_ecg,PBSDType_it_ppg,PBSDType_it_rri,PBSDType_it_health,PBSDType_it_gnss)
        print(PBSDType_dt_ecg,PBSDType_dt_ppg,PBSDType_dt_rri,PBSDType_dt_health,PBSDType_dt_gnss)
        watchDelegate?.hasInfo(dInfo)
    }

     public func responseDataProgress(_ progress: Int) {
        if progress < 0 {
            let intProgress = Int(Double(-progress)/100.0)
            print("responseDataProgress ",intProgress)
            watchDelegate?.updateProgress(intProgress)
        } else {
            print("responseDataProgress ",progress)
            watchDelegate?.updateProgress(progress)
        }
    }

}

