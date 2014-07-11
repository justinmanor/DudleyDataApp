//
//  dsCitizensData.h
//  Dudley
//
//  Created by Sosolimited on 7/11/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxHttpUtils.h"
#include "ofxJSONElement.h"
#include "Poco/LocalDateTime.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeParser.h"
#include "Poco/DateTimeFormat.h"

typedef struct{
  int id;
  Poco::LocalDateTime time;
  string status;
  std::vector<float> latLong;
  string neighborhood;
  string category;
} event;

class dsCitizensData{

public:
  dsCitizensData(string url);
  ~dsCitizensData();
  
//  updateSubscribers()
//  getNewestJSON()
//  addEventSubscriber()
  
private:

  string jsonUrl;
  ofxJSONElement jsonResults;
  std::vector<event*> events;
//  ofxHttpUtils httpUtils
//  ofxJSONElement jsonValueRoot
//  geoJSON
//  std::vector<event*> neighborhoods;
//  std::vector<event*> categories;
//  std::vector<...*> eventSuscribers;
  
};