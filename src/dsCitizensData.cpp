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
  
  fetchNewestJson();
  fetchGeoJson();
  
}

dsCitizensData::~dsCitizensData(){}

// Get the json data of requests from the Open311 system.
void dsCitizensData::fetchNewestJson(){
  
  bool parsingSuccessful = jsonResults.open(jsonUrl);
  if (parsingSuccessful) {
    //    cout  << "---------------- Successfully parsed JSON" << endl;
    //		cout << jsonResults.getRawString() << endl;
    
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
    e.neighborhood = "unkown";
    e.category = jsonResults[i]["service_name"].asString();
    events.push_back(e);
    
    //    cout << "---- event["<< i <<"]" << endl;
    //    cout << e.id << endl;
    //    cout << e.time << endl;
    //    cout << e.status << endl;
    //    cout << e.lat << endl;
    //    cout << e.lon << endl;
    //    cout << e.neighborhood << endl;
    //    cout << e.category << endl;
	}

}

// Get geojson file of Boston neighborhoods.
void dsCitizensData::fetchGeoJson(){
  //  From the ofxGeoJSON example:
  geojsonBoston.setMode(OFX_GEO_JSON_MERCATROE);
  geojsonBoston.setTranslate(-71.07, 42.32);     //TODO: find the proper translation to see the map in the canvas.
  geojsonBoston.setScale(550);

  
  if (geojsonBoston.load("boston_neighborhoods.geojson")) {
    ofLog(OF_LOG_NOTICE, "Succeed to load geojson..");
  } else {
    ofLog(OF_LOG_NOTICE, "Failed to load geojson..");
  };
  
}

// Return the geojson.
ofxGeoJSON dsCitizensData::getGeoJson(){
  return geojsonBoston;
}