//
//  Bookmark.swift
//  photon
//
//  Created by Amlal on 10/13/24.
//

import Foundation
import SwiftUI

struct Bookmark: Identifiable, Hashable {
    let markName: String = "Bookmark";
    let markURL: String = "photon:blank";
    let markIcon: String = "network";
    let markColor: Color = .blue;
    
    var id: String { markURL }
}
