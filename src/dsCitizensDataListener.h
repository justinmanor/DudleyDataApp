//
//  dsCitizensDataListener.h
//  Dudley
//
//  Created by Sosolimited on 7/22/14.
//
//

#pragma once
#include "ofMain.h"
#include "dsEvent.h"

class dsCitizensDataListener{
  
public:
  virtual void handleNewEvent(dsEvent* iEvent)=0;

protected:

  
};