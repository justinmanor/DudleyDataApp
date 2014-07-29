//
//  dsRealtimeLayer.cpp
//  Dudley
//
//  Created by Sosolimited on 7/22/14.
//
//

#include "dsRealtimeLayer.h"

dsRealtimeLayer::dsRealtimeLayer() {
	
  ref = dsGraphicsRef::instance();
  
}

dsRealtimeLayer::~dsRealtimeLayer() {}

void dsRealtimeLayer::handleNewEvent(dsEvent* iEvent){
  ofLog()<< "dsRealtimeLayer::handleNewEvent - - - - - - - - - - -"<< endl;
//  cout<< iEvent <<endl;
}
