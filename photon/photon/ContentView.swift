//
//  ContentView.swift
//  photon
//
//  Created by Amlal on 10/12/24.
//

import SwiftUI

struct ContentView: View {
    private var noTabs: Bool = false;
    public var devices: [PhotonDevice] = [
    ]
    
    init() {
        let photonDevice = PhotonDevice(markName: "Add...", markURL: kPhotonUrlProtocol + "new");
    
        var login = PhotonDevice(markName: "Profile", markURL: "https://www.el-mahrouss-logic.com/login");
        
        login.markIcon = "person.crop.circle";
        
        devices.append(login);
        devices.append(photonDevice);
    }
    
    var body: some View {
        NavigationView {
            List(devices) { mark in
                HStack {
                    Image(systemName: mark.markIcon)
                    Link(mark.markName, destination: URL(string: mark.markURL)!)
                }
            }.listStyle(.sidebar)
        }.frame(width: 720, height: 500)
    }
}

#Preview {
    ContentView()
}
