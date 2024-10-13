//
//  Bookmark.swift
//  photon
//
//  Created by Amlal on 10/13/24.
//

import Foundation
import SwiftUI

var kPhotonUrlProtocol = "pht://";

struct PhotonDevice: Identifiable, Hashable {
    init(markName: String, markURL: String) {
        self.markName = markName;
        self.markURL = markURL;
    }
    
    var markName: String = "Photon Phone";
    var markURL: String = "photon:blank";
    var markIcon: String = "iphone";
    var markColor: Color = .blue;
    
    var id: String { markURL }
}
