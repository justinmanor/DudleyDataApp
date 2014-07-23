//
//  dsCitizensDataSuscriber.h
//  Dudley
//
//  Created by Sosolimited on 7/22/14.
//
//

#pragma once
#include "ofxObject.h"
#include "ofMain.h"
#include "dsEvent.h"

class dsCitizensDataSuscriber : public ofxObject {
  
public:
  virtual void handleNewEvent(dsEvent* iEvent)=0;

protected:

  
};