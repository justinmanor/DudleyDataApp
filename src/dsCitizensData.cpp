//
//  dsCitizensData.cpp
//  Dudley
//
//  Created by Sosolimited on 7/11/14.
//
//

#include "dsCitizensData.h"


dsCitizensData::dsCitizensData(){
  
  //jsonUrl = url;

  //fetchAllJson();
	
}

void dsCitizensData::setEnvironment(string iEnv, int iUTCTimeDiff){
	
	baseUrl = "https://mayors24.cityofboston.gov/open311/v2/requests.json";
	timeZone = iUTCTimeDiff;
	pageSize = "page_size=250";
	pageNum = "page=1";
	
	if (iEnv == "dev") {
    cout << "System Environment: dev" <<endl;
		cout << " TimeZone from UTC: " << iUTCTimeDiff << endl;
		start = "end_date=" + dateTimeToString(currentDateTime());
	} else if (iEnv == "production") {
		cout << "System Environment: production" <<endl;
		cout << " TimeZone from UTC: " << iUTCTimeDiff << endl;
	} else {
		cout << "***** error with production setup *****" << endl;
		start = "start_date=" + dateTimeToString(currentDateTime());
	}
	
	jsonUrl = baseUrl + "?" + start + "&" + pageSize + "&" + pageNum;
	fetchAllJson();
	
}

dsCitizensData::~dsCitizensData(){}

// IDLE
void dsCitizensData::idle(float iTime){
	
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// realtime pulling
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	if (timeOfLastPull) {
    int timeSinceLastPull = ofGetElapsedTimef() - timeOfLastPull;
		if (timeSinceLastPull > 5.0) {
			cout << "5 seconds!" <<endl;
			
			string baseUrl = "https://mayors24.cityofboston.gov/open311/v2/requests.json";
			string pageSize = "page_size=5";
			string pageNum = "page=1";
			string start = dateTimeToString(dateTimeOfLastPull);
			
			// jsonUrl = baseUrl + "?start_date=" + "2014-07-20T08:00:00-8:00" + "&" + pageSize + "&" + pageNum;
			jsonUrl = baseUrl + "?end_date=" + start + "&" + pageSize + "&" + pageNum;
			
			cout << start << endl;
			cout << jsonUrl << endl;
			//dateParser(start);
			fetchEventJson();
			// or
			//dateTimeOfLastPull = currentDateTime();
			//timeOfLastPull = ofGetElapsedTimef();
		}
	}
  
}


//
void dsCitizensData::fetchAllJson(){
  fetchGeoJson();       // Get neighborhood data first.
}

// Get geojson file of Boston neighborhoods.
void dsCitizensData::fetchGeoJson(){
  
  if (geojsonBoston.load("boston_neighborhoods.geojson")) {
    ofLog(OF_LOG_NOTICE, "Succeed to load geojson..");
    
    // Copy the neighborhoods from the factory so it also resides here, in this main data object.
    neighborhoods = geojsonBoston.getNeighborhoods();
    
    // Get Open311 "event" data once we have neighborhoods.
    fetchEventJson();
    
  } else {
    ofLog(OF_LOG_NOTICE, "Failed to load geojson..");
  };
  
}

// Get the json data of requests from the Open311 system.
void dsCitizensData::fetchEventJson(){
  
  bool parsingSuccessful = jsonResults.open(jsonUrl);
  
	if (parsingSuccessful) {
		
    cout  << "---------------- Successfully parsed JSON" << endl;
		
		// cout << jsonResults.getRawString() << endl;
    
		if (jsonResults.size() > 0) {
			
			cout << "New event(s): " << jsonResults.size() << endl;
			
		
			//  Create an event for each piece of data.
			for(int i=0; i<jsonResults.size(); i++) {
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
				cout << "        Time: "<< dateTimeToString( e->getTime() ) << endl;
				cout << "      Status: "<< e->getStatus() << endl;
				cout << "         Lat: "<< e->getLat() << endl;
				cout << "         Lon: "<< e->getLon() << endl;
				cout << "Neighborhood: "<< e->getNeighborhood() << endl;
				cout << "    Category: "<< e->getCategory() << endl;
				
			}
			
			//DEV
			//printCategoryCounter();
			//printCategoryContents();
			//printNeighborhoodContents();
			
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
			
			
			cout << "Total Event Size: " << events.size() << endl;
			updateSubscribers();
		} else {
			cout << " - - - No new events - - - " << endl;
		}
		
	} else {
		cout  << "---------------- Failed to parse JSON" << endl;
	}
	
	// setting the current time for pulling reference
	timeOfLastPull = ofGetElapsedTimef();
	dateTimeOfLastPull = currentDateTime();
  
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


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Time Tools
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// String to Poco::DateTime
Poco::DateTime dsCitizensData::dateParser(string iTime) {
	
	Poco::DateTimeParser parser;
	Poco::DateTime time;
	int tzd;
	parser.parse(Poco::DateTimeFormat::ISO8601_FORMAT, iTime, time, tzd);
	cout << "UTC Time Diff: " << tzd << endl;
	return (time);
}

// Poco::DateTime to String, matching server format
string dsCitizensData::dateTimeToString(Poco::DateTime iDateTime) {

	int utcOffset = Poco::Timezone::utcOffset();
	//cout << utcOffset << endl;
	string s = (Poco::DateTimeFormatter::format(iDateTime, Poco::DateTimeFormat::ISO8601_FORMAT, timeZone));
	return s;
	
}

// Get current local Poco::DateTime
Poco::DateTime dsCitizensData::currentDateTime() {
	
	Poco::LocalDateTime::LocalDateTime now;
	Poco::Timestamp ts = now.timestamp();
	Poco::DateTime current = Poco::DateTime(ts);
	
	return current;
	
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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

// Returns the number of events for a certain neighborhood, and optionally, specific to a category in said neighborhood.
int dsCitizensData::getNumEventsForNeighborhood(string iNeighborhoodName, string iCategoryName){
  for (auto n : neighborhoods){
    if (n->getName() == iNeighborhoodName){
      
      if (iCategoryName.empty()){ return n->getEventCount(); }
      else { return n->getCategoryCount(iCategoryName); }
      
    }
  }
}

//
string dsCitizensData::getEventCategory(int index) {
	if (index >= 0 && index < events.size()) {
		return events[index]->getCategory();
	}
}
string dsCitizensData::getNeighborhoodName(int index) {
	if (index >= 0 && index < events.size()) {
		return events[index]->getNeighborhood();
	}
}
string dsCitizensData::getEventTime(int index) {
	if (index >= 0 && index < events.size()) {
		return events[index]->getTimeString();
	}
}

//
void dsCitizensData::addEventSubscriber(dsCitizensDataSubscriber* iSubscriber){
  eventSubscribers.push_back(iSubscriber);
}

//
void dsCitizensData::updateSubscribers(){
	//newEvents
  for (auto es : eventSubscribers){
    es->handleNewEvent(events[15]);
  }
}
