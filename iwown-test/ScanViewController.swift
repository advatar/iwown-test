//
//  ViewController.swift
//  iwown-test
//
//  Created by Johan Sellström on 2020-01-28.
//  Copyright © 2020 Johan Sellström. All rights reserved.
//

import UIKit
import BLEDragonBoat
import BLEProtoBuf

class ScanViewController: UITableViewController, DeviceDelegate {

    var iwownManager: IWownManager!
    var watches = [DNBBlePeripheral]()
    var config = Config()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        iwownManager = IWownManager.shared
        iwownManager.delegate = self
        iwownManager.synchronize()
        
        tableView.register(UITableViewCell.self, forCellReuseIdentifier: "reuseIdentifier")
        // Do any additional setup after loading the view.
    }

    override func numberOfSections(in tableView: UITableView) -> Int {
        // #warning Incomplete implementation, return the number of sections
        return 1
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        // #warning Incomplete implementation, return the number of rows
        return watches.count
    }

    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "reuseIdentifier", for: indexPath)

        let watch = watches[indexPath.row]
        cell.textLabel?.text = watch.deviceName
        print("reloading table")
        return cell
    }
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let watch = watches[indexPath.row]
        config.watchuuidString = watch.uuidString
        iwownManager.connect()
    }
    
     // MARK: DeviceDelegate
    
    func isConnecting() {
       print("is connecting")
    }

    func fail() {
       print("fail")
    }

    func connected(info: String) {
       print("connected \(info)")
    }

    func progress(_ progress: Int) {
       print("progress \(progress)")
    }

    func batteryInfo(level: Int, charging: Bool) {
       print("Battery level \(level) charging \(charging)")
    }

    func synchronized() {
       print("synchronized")
    }
    
    func discovered(watches: [DNBBlePeripheral]) {
        self.watches = watches
        
        
        for watch in watches {
            print("Discovered \(watch.deviceName)")
        }
        
        DispatchQueue.main.async {
            self.tableView.reloadData()
        }
    }

}

