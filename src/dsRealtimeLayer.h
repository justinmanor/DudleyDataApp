//
//  dsRealtimeLayer.h
//  Dudley
//
//  Created by Sosolimited on 7/22/14.
//
//

#pragma once

#include "dsCitizensDataSubscriber.h"
#include "dsGraphicsRef.h"
#include "dsEvent.h"

class dsRealtimeLayer : public dsCitizensDataSubscriber {
  
public:
  
  dsRealtimeLayer();
	~dsRealtimeLayer();
  
  void  handleNewEvent(dsEvent* iEvent);
  
public:
  
  dsGraphicsRef               *ref;
  
private:
	
};