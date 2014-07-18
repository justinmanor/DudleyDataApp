//
//  dsCitizensData.h
//  Dudley
//
//  Created by Sosolimited on 7/11/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxJSONElement.h"
#include "dsNeighborhoodFactory.h"
#include "dsCategory.h"
//#include "ofxGeoJSON.h"

#include "Poco/LocalDateTime.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeParser.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Timestamp.h"
#include <ctime>

struct event{
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

class dsCitizensData{

public:

	int day, month, year;
	
  dsCitizensData(string url);
  ~dsCitizensData();

  void fetchNewestJson();
  void fetchGeoJson();
  int getNumEvents( ) {return events.size(); }
  int getNumNeighborhoods() { return geojsonBoston.getNeighborhoodCount(); }
  ofVec3f getEventCoords(int index);
  ofVec3f getCentroid();
  void draw();
	string getEventCategory(int index) {return events[index].category;}
	
	Poco::DateTime dateParser(string iTime);
	int timeFromCurrent(Poco::DateTime iPocoTime);
	float getAgeInSeconds(int index) {return events[index].age; }

  dsNeighborhoodFactory getGeoJson();
  
//  updateSubscribers()
//  addEventSubscriber()
  
private:

  string jsonUrl;                 // Contains the Open311 JSON query string originally passed to this class.
  std::vector<event> events;      // Contains the Open311 data transformed into objects.
  ofxJSONElement jsonResults;     // Contains the raw Open311 data
  dsNeighborhoodFactory geojsonBoston;      // Creates neighborhood objects from geojson of Boston.
  //  ofxGeoJSON bostonMap;         // Contains the raw GeoJSON data of Boston for drawing a map.
  
  std::vector<dsCategory*> categories;
//  std::vector<event*> neighborhoods;
//  std::vector<...*> eventSuscribers;
  
};