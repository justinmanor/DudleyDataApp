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
  
  //  Store it in an object.
  for(int i=0; i<jsonResults.size(); i++)
	{
    event e;
    e.id = i;
    e.time = jsonResults[i]["updated_datetime"].asString();
    e.status = jsonResults[i]["status"].asString();
    e.lat = jsonResults[i]["lat"].asFloat();
    e.lon = jsonResults[i]["long"].asFloat();
    e.neighborhood = geojsonBoston.getNeighborhoodForPoint(e.lat, e.lon);
    e.category = jsonResults[i]["service_name"].asString();
    events.push_back(e);
    
    // DEV
    cout << "---------------------------------------------- event["<< i <<"]" << endl;
    cout << e.id << endl;
    cout << e.time << endl;
    cout << e.status << endl;
    cout << e.lat << endl;
    cout << e.lon << endl;
    cout << e.neighborhood << endl;
    cout << e.category << endl;
	}

}

// Get geojson file of Boston neighborhoods.
void dsCitizensData::fetchGeoJson(){
  
  if (geojsonBoston.load("boston_neighborhoods.geojson")) {
    ofLog(OF_LOG_NOTICE, "Succeed to load geojson..");
    
    fetchNewestJson();    // Secondly, get Open311 data once we have neighborhoods.
    
  } else {
    ofLog(OF_LOG_NOTICE, "Failed to load geojson..");
  };
  
}

// Return the geojson.
dsNeighborhoodFactory dsCitizensData::getGeoJson(){
  return geojsonBoston;
}