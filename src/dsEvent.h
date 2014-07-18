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
  dsEvent(int iId, string iTimestring, string iStatus, float iLat, float iLon, string iCategory);
  ~dsEvent();
  
  int getId(){ return id; }
  int getAgeInSeconds(){ return ageInSeconds; }
  Poco::DateTime getTime(){ return time; }
  int getAge(){ return age; }
  string getTimeString(){ return timeString; }
  string getStatus(){ return status; }
  float getLat(){ return lat; }
  float getLon(){ return lon; }
  string getNeighborhood(){ return neighborhood; }
  string getCategory(){ return category; }
  
  void setTime(Poco::DateTime iTime){ time = iTime; }
  void setAge(int iAge){ age = iAge; }
  void setNeighborhood(string iNeighborhood){ neighborhood = iNeighborhood; }
  
//  string getNeighborhoodName(int index) { return neighborhood; }
//  ofVec3f getEventCoords(int index);
//  string getEventCategory(int index) {return category;}
//  float getAgeInSeconds(int index) {return age; }
  
private:
  // Default Open311 event attributes.
  int id;
  string timeString;
  string status;
  float lat;
  float lon;
  string category;
  
  // Our additional custom attributes.
  Poco::DateTime time;
  int age;
  string neighborhood;
  int ageInSeconds;
};