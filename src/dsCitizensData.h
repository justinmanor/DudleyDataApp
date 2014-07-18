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
#include "dsEvent.h"

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
  ofVec3f getCentroid();
  void draw();
	void addCategory(string iCategoryName);
  void printCategories();
    
	Poco::DateTime dateParser(string iTime);
	int timeFromCurrent(Poco::DateTime iPocoTime);

	dsNeighborhoodFactory getGeoJson();
  
  
  // DEV - events
  float getAgeInSeconds(int index) {return events[index]->getAge(); }
	string getEventCategory(int index) {return events[index]->getCategory();}
  string getNeighborhoodName(int index) { return events[index]->getNeighborhood(); }
  ofVec3f getEventCoords(int index);
  
  
//  updateSubscribers()
//  addEventSubscriber()
  
private:

  string jsonUrl;                 // Contains the Open311 JSON query string originally passed to this class.
  ofxJSONElement jsonResults;     // Contains the raw Open311 data
  dsNeighborhoodFactory geojsonBoston;      // Creates neighborhood objects from geojson of Boston.
  //  ofxGeoJSON bostonMap;         // Contains the raw GeoJSON data of Boston for drawing a map.
	
	map<string, int> neighborhoodEventCounts; // For counting events in the neighborhoods.
  
//  std::vector<event> events;      // Contains the Open311 data transformed into objects.
  std::vector<dsEvent*> events;      // Contains the Open311 data transformed into objects.
  std::vector<dsCategory*> categories;
  map<string, int> categoryCounter;
//  std::vector<event*> neighborhoods;
//  std::vector<...*> eventSuscribers;
  
};