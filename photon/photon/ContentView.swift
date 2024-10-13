//
//  ContentView.swift
//  photon
//
//  Created by Amlal on 10/12/24.
//

import SwiftUI

struct ContentView: View {
    private var noTabs: Bool = false;
    public var bookmarks: [Bookmark] = [
    ]
    
    var body: some View {
        NavigationView {
            List(bookmarks) { mark in
                HStack {
                    Image(systemName: mark.markIcon)
                    Text(mark.markName)
                }.foregroundColor(mark.markColor)
            }.listStyle(.sidebar)
        }
        
    }
}

#Preview {
    ContentView()
}
