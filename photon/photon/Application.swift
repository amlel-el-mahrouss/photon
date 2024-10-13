//
//  Application.swift
//  photon
//
//  Created by Amlal on 10/13/24.
//

import Foundation

struct Application: Identifiable {
    let appName: String = "Photon";
    let appVersion: String = "1.0.0";
    
    var id: String { appName }
}
