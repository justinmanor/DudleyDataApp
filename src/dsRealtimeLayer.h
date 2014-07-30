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
#include "dsCitizensData.h"
#include "dsEvent.h"
#include "ofxCircleObject.h"

class dsRealtimeLayer : public dsCitizensDataSubscriber {
  
public:
  
  dsRealtimeLayer();
	~dsRealtimeLayer();
  
  void  handleNewEvent(dsEvent* iEvent);
	void	buildEvents(dsEvent* iEvent);
	void	animateEvent(ofxCircleObject* iNewEvent);
  
public:
  
  dsGraphicsRef*               ref;
  dsCitizensData              *citizensData;
	
  
private:
	
	vector <ofxCircleObject *>		newEvents;
	
};