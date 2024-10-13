//
//  photonApp.swift
//  photon
//
//  Created by Amlal on 10/12/24.
//

import SwiftUI

@main
struct PhotonApp: App {
    init() {
        appInfo = Application();
    }
    
    public var bookmarkList: [Bookmark] = [];
    public var appInfo: Application;
    
    var body: some Scene {
        WindowGroup {
            ContentView().navigationTitle(appInfo.appName)
        }
    }
}
