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

//class dsCategory;   // forward-declaration.

class dsCitizensData{

public:

	int day, month, year;
	
  dsCitizensData(string url);
  ~dsCitizensData();

  void fetchNewestJson();
  void fetchGeoJson();
  int getNumEvents( ) {return events.size(); }
  dsNeighborhoodFactory getGeoJson(){ return geojsonBoston; }
  int getNumNeighborhoods() { return geojsonBoston.getNeighborhoodCount(); }
  ofVec3f getCentroid();
  void draw();
	dsCategory* addCategoryToVector(string iCategoryName);
  dsCategory* getCategoryByName(string iCategoryName);
  dsNeighborhood* getNeighborhoodByName(string iNeighborhoodName);
    
	Poco::DateTime dateParser(string iTime);
	int timeFromCurrent(Poco::DateTime iPocoTime);

//	dsNeighborhoodFactory getGeoJson();   //dev_JN
  
  float getAgeInSeconds(int index) {return events[index]->getAge(); }
	string getEventCategory(int index) {return events[index]->getCategory();}
  string getNeighborhoodName(int index) { return events[index]->getNeighborhood(); }
  ofVec3f getEventCoords(int index);
  
  //DEV fcts
  void printCategoryCounter();
  void printCategoryContents();
  void printNeighborhoodContents();
  
  //TODO
//  updateSubscribers()
//  addEventSubscriber()
  
private:

  string jsonUrl;                 // Contains the Open311 JSON query string originally passed to this class.
  ofxJSONElement jsonResults;     // Contains the raw Open311 data
  dsNeighborhoodFactory geojsonBoston;      // Creates neighborhood objects from geojson of Boston.
  //  ofxGeoJSON bostonMap;         // Contains the raw GeoJSON data of Boston for drawing a map.
  
  std::vector<dsEvent*> events;      // Contains the Open311 data transformed into objects.
  std::vector<dsCategory*> categories;
  map<string, int> categoryCounter;
  std::vector<dsNeighborhood*> neighborhoods;

  //TODO
  //  std::vector<...*> eventSuscribers;
  
};