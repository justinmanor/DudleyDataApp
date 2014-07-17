//
//  dsCitizensData.cpp
//  Dudley
//
//  Created by Sosolimited on 7/11/14.
//
//

#include "dsCitizensData.h"


dsCitizensData::dsCitizensData(string url){
  
  jsonUrl = url;

  fetchGeoJson();       // Get neighborhood data first.
  
}

dsCitizensData::~dsCitizensData(){}

// Get the json data of requests from the Open311 system.
void dsCitizensData::fetchNewestJson(){
  
  bool parsingSuccessful = jsonResults.open(jsonUrl);
  if (parsingSuccessful) {
    cout  << "---------------- Successfully parsed JSON" << endl;
//    cout << jsonResults.getRawString() << endl;
    
    // Save to file : pretty print
    if(!jsonResults.save("example_output_pretty.json",true)) {
      //      cout << "example_output_pretty.json written unsuccessfully." << endl;
    } else {
      //      cout << "example_output_pretty.json written successfully." << endl;
    }
    // Save to file : raw
    if(!jsonResults.save("example_output_fast.json",false)) {
      //      cout << "example_output_pretty.json written unsuccessfully." << endl;
    } else {
      //      cout << "example_output_pretty.json written successfully." << endl;
    }
    
	} else {
    //		cout  << "---------------- Failed to parse JSON" << endl;
	}
  
	//create
	
  //  Store it in an object.
  for(int i=0; i<jsonResults.size(); i++)
	{
    event e;
    e.id = i;
		//e.ageInSeconds;
		e.time = dateParser(jsonResults[i]["updated_datetime"].asString());
		e.age = timeFromCurrent(e.time);
    e.timeString = jsonResults[i]["updated_datetime"].asString();
    e.status = jsonResults[i]["status"].asString();
    e.lat = jsonResults[i]["lat"].asFloat();
    e.lon = jsonResults[i]["long"].asFloat();
    e.neighborhood = geojsonBoston.getNeighborhoodForPoint(e.lat, e.lon);
    e.category = jsonResults[i]["service_name"].asString();
    events.push_back(e);
    
    // DEV
    cout << "---------------------------------------------- event["<< i <<"]" << endl;
    cout << e.id << endl;
		cout << e.timeString << endl;
    cout << e.age << endl;
    cout << e.status << endl;
    cout << e.lat << endl;
    cout << e.lon << endl;
    cout << e.neighborhood << endl;
    cout << e.category << endl;
	}

}

// Parse event time.
Poco::DateTime dsCitizensData::dateParser(string iTime) {
	
	Poco::DateTimeParser parser;
	Poco::DateTime time;
	int GMT = 5;
	time = parser.parse(iTime, GMT);
  
//	int year = time.year();
//	int month = time.month();
//	int day = time.day();
//	int hour = time.hour();
//	int minute = time.minute();
//	int second = time.second();
	
	return (time);
}

// Time From this current moment in time.
int dsCitizensData::timeFromCurrent(Poco::DateTime iPocoTime) {
	
	
	Poco::Timespan age;
	Poco::Timestamp current;
	Poco::DateTime currentTime = Poco::DateTime(current);
	
	
	age = currentTime - iPocoTime;
	
	int ageInSeconds = age.totalSeconds() - 14400;
	//cout << current << endl;
	return (ageInSeconds);

	
}

// Get geojson file of Boston neighborhoods.
void dsCitizensData::fetchGeoJson(){
  
  if (geojsonBoston.load("boston_neighborhoods.geojson")) {
    ofLog(OF_LOG_NOTICE, "Succeed to load geojson..");
    
    fetchNewestJson();    // Secondly, get Open311 "event" data once we have neighborhoods.
    
  } else {
    ofLog(OF_LOG_NOTICE, "Failed to load geojson..");
  };
  
}

// Return the geojson.

dsNeighborhoodFactory dsCitizensData::getGeoJson(){

  return geojsonBoston;

}

ofVec3f dsCitizensData::getEventCoords(int index) {
  
  if (index < events.size()) {
    ofVec3f xyz(events[index].lat, events[index].lon, 0);
    return xyz;
  }
  else
    return ofVec3f(0,0,0);
  
}

ofVec3f dsCitizensData::getCentroid() {
  
  ofVec3f centroid;
  
  for (auto e : events ) {
    centroid.x += e.lat/((float)events.size());
    centroid.y += e.lon/((float)events.size());
    
  }
  return centroid;
}

//debug function for making sure there is data, uses basic oF drawing tools
void dsCitizensData::draw() {
  
  //ofLogNotice("drawing");
  ofSetColor(250, 0, 0);
  for (int i = 0 ; i < events.size() ; i++) {
    
    ofCircle(400 + 400.0*(events[i].lat - 42.34), 500 -400.0*(events[i].lon + 72.06), 2);
    //ofLogNotice(ofToString(i));
  }
}