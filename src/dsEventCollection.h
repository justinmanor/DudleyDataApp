//
//  dsEventCollection.h
//  Dudley
//
//  Created by Sosolimited on 7/22/14.
//
//

#pragma once
#include "ofMain.h"
#include "dsEvent.h"
#include "Poco/DateTime.h"
#include "Poco/Timespan.h"
#include "Poco/Timezone.h"

class dsEventCollection{

public:
  
  string getName(){ return name; }
  std::vector<dsEvent*> getEvents(){ return events; }
  
protected:

  string name;
  std::vector<dsEvent*> events;
  
};