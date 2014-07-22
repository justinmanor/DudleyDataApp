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
    
    //  Create an event for each piece of data.
    for(int i=0; i<jsonResults.size(); i++)
    {
      // Event attributes based on default Open311 data attributes.
      dsEvent* e = new dsEvent(
                               i,
                               jsonResults[i]["updated_datetime"].asString(),
                               jsonResults[i]["status"].asString(),
                               jsonResults[i]["lat"].asFloat(),
                               jsonResults[i]["long"].asFloat(),
                               jsonResults[i]["service_name"].asString()
                               );
      events.push_back(e);
      // Add a few custom attributes of our own.
      e->setTime(dateParser(jsonResults[i]["updated_datetime"].asString()));
      e->setAge(timeFromCurrent(e->getTime()));
      e->setNeighborhood(geojsonBoston.getNeighborhoodForPoint(e->getLat(), e->getLon()));
      // Add current category to the category vector.
      dsCategory* c = addCategoryToVector(e->getCategory());
      // Add reference to this event in the category object.
      c->addEvent(e);
      // Add reference to this event in the neighborhood object.
      dsNeighborhood* n = getNeighborhoodByName(e->getNeighborhood());
      if (e->getNeighborhood() != "unknown"){
        n->addEvent(e);
      }
      
      // DEV
      cout << "---------------------------------------------- events["<< i <<"]" << endl;
      cout << "          id: "<< e->getId() << endl;
      cout << "        Time: "<< e->getTimeString() << endl;
      cout << "    Age(sec): "<< e->getAge() << endl;
      cout << "      Status: "<< e->getStatus() << endl;
      cout << "         Lat: "<< e->getLat() << endl;
      cout << "         Lon: "<< e->getLon() << endl;
      cout << "Neighborhood: "<< e->getNeighborhood() << endl;
      cout << "    Category: "<< e->getCategory() << endl;
      
    }
    
    int test = categories[0]->getNeighborhoodCount("Allston");
    int test2 = neighborhoods[0]->getCategoryCount("Other");
    
    //DEV
    printCategoryCounter();
    printCategoryContents();
    printNeighborhoodContents();
    
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
  
}

dsNeighborhood* dsCitizensData::getNeighborhoodByName(string iNeighborhoodName){
  for (auto neighborhood : neighborhoods){
    if(neighborhood->getName() == iNeighborhoodName){
      return neighborhood;
    }
  }
}

dsCategory* dsCitizensData::getCategoryByName(string iCategoryName){
  for (auto category : categories){
    if(category->getName() == iCategoryName){
      return category;
    }
  }
}

// Adds the provided category to the categories vector if we haven't seen it already, and returns the category object.
dsCategory* dsCitizensData::addCategoryToVector(string iCategoryName){
  
  dsCategory* cat;
  if(!categoryCounter[iCategoryName]){
    cat = new dsCategory(iCategoryName);
    categories.push_back(cat);
  } else {
    cat = getCategoryByName(iCategoryName);
  }
  
  ++categoryCounter[iCategoryName];
  
  return cat;
}

// FOR DEV: Prints out the categories.
void dsCitizensData::printCategoryCounter(){
//  cout<< "* * * * * * * * * * * * * * * * * * * * * * * * * PRINTING CATEGORY COUNTER" <<endl;
  for(map<string, int>::const_iterator it = categoryCounter.begin(); it != categoryCounter.end(); it++){
    cout<< it->first <<"\t"<< it->second <<endl;
  }
}

void dsCitizensData::printCategoryContents(){
//  cout<< "* * * * * * * * * * * * * * * * * * * * * * * * * PRINTING CATEGORY CONTENTS" <<endl;
  for(auto category : categories){
    cout<< "name : " << category->getName() <<endl;
    cout<< "#events : " << category->getEvents().size() <<endl;
  }
}

void dsCitizensData::printNeighborhoodContents(){
//  cout<< "* * * * * * * * * * * * * * * * * * * * * * * * * PRINTING NEIGHBORHOOD CONTENTS" <<endl;
  for(auto neighborhood : neighborhoods){
    cout<< "name : " << neighborhood->getName() <<endl;
    cout<< "#events : " << neighborhood->getEvents().size() <<endl;
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

    // Copy the neighborhoods from the factory so it also resides here, in this main data object.
    neighborhoods = geojsonBoston.getNeighborhoods();
    
    // Get Open311 "event" data once we have neighborhoods.
    fetchNewestJson();
    
  } else {
    ofLog(OF_LOG_NOTICE, "Failed to load geojson..");
  };
  
}

// Return the geojson.
//dsNeighborhoodFactory dsCitizensData::getGeoJson(){
//  return geojsonBoston;
//}

ofVec3f dsCitizensData::getEventCoords(int index) {
  
  if (index < events.size()) {
    ofVec3f xyz(events[index]->getLat(), events[index]->getLon(), 0);
    return xyz;
  }
  else
    return ofVec3f(0,0,0);
  
}

ofVec3f dsCitizensData::getCentroid() {
  
  ofVec3f centroid;
  
  for (auto e : events ) {
    centroid.x += e->getLat()/((float)events.size());
    centroid.y += e->getLon()/((float)events.size());
    
  }
  return centroid;
}

//debug function for making sure there is data, uses basic oF drawing tools
void dsCitizensData::draw() {
  
  //ofLogNotice("drawing");
  ofSetColor(250, 0, 0);
  for (int i = 0 ; i < events.size() ; i++) {
    
    ofCircle(400 + 400.0*(events[i]->getLat() - 42.34), 500 -400.0*(events[i]->getLon() + 72.06), 2);
    //ofLogNotice(ofToString(i));
  }
}