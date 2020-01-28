//
//  Misc.swift
//  iwown-test
//
//  Created by Johan Sellström on 2020-01-28.
//  Copyright © 2020 Johan Sellström. All rights reserved.
//

import Foundation

public typealias JSON = [String: Any]

extension FileManager {
    static var documentDir : URL {
        return FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first!
    }
}

public struct Config {
    
    struct Keys {
        static let watchuuidString = "watchuuidString"
    }

    static let current: Config = Config()

    let defaults: UserDefaults

    public init(
        defaults: UserDefaults = UserDefaults()
    ) {
        self.defaults = defaults
    }
    
    
    public var watchuuidString: String? {
        get {
            let k = defaults.string(forKey: Keys.watchuuidString)
            guard k != nil  else { return nil }
            return k
        }
        set { defaults.set(newValue, forKey: Keys.watchuuidString) }
    }
}
