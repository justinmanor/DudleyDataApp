//
//  dsEvent.h
//  Dudley
//
//  Created by Sosolimited on 7/17/14.
//
//

#pragma once

#include "ofMain.h"

#include "Poco/LocalDateTime.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeParser.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Timestamp.h"
#include <ctime>

class dsEvent {
  
public:
  dsEvent();
  ~dsEvent();
  
  string getNeighborhoodName(int index) { return neighborhood; }
  ofVec3f getEventCoords(int index);
  string getEventCategory(int index) {return category;}
  float getAgeInSeconds(int index) {return age; }
  
private:
  int id;
	int ageInSeconds;
  Poco::DateTime time;
	int age;
  string timeString;
  string status;
  float lat;
  float lon;
  string neighborhood;
  string category;
  
};