//
//  dsEventLayer.cpp
//  Dudley
//
//  Created by Sosolimited on 7/16/14.
//
//

#include "dsEventLayer.h"

dsEventLayer::dsEventLayer() {
	
  ref = dsGraphicsRef::instance();
  
}

dsEventLayer::~dsEventLayer() {}

void dsEventLayer::handleNewEvent(dsEvent* iEvent){
  ofLog()<< "dsEventLayer::handleNewEvent - - - - - - - - - - -"<< endl;
	cout << "Handling New EVENTs" << endl;
}

void dsEventLayer::buildEvents(dsCitizensData *data)
{

  // - - - - - - - - - - - - - - - - - - - - - - - - - -
	// Create a small circle for each event, colored by category.
	// - - - - - - - - - - - - - - - - - - - - - - - - - -

	for (int i = 0 ; i < data->getNumEvents() ; i ++){
    ofxCircleObject *c = new ofxCircleObject(20, 2);
    c->setTrans(2000.0*(data->getEventCoords(i) - data->getCentroid()));
		c->setAlpha(255);
		string category = data->getEventCategory(i);
		c->setColor(ref->getColorByName(category));
		
    events.push_back(c);
    addChild(c);
  }
	
	// Build the categories legend.
	
	vector <string> categories;
  
  categories.push_back("Sidewalk Patch");
  categories.push_back("Graffiti");
  categories.push_back("Pothole");
  categories.push_back("Streetlight");
  categories.push_back("Damaged Sign");
  categories.push_back("Other");
	
	font16 = new ofxSosoTrueTypeFont();
  font16->loadFont("Arial.ttf", 16, true,  true, false, true);
	font16->setKerningPair('T', 'y', -2);
	
	for (int i = 0; i < categories.size(); i++ ) {
		ofxObject *element = new ofxObject();
		
		ofxTextObject *label = new ofxTextObject(font16, categories[i]);
		label->setColor(255, 255, 255);
		label->setPointSize(16);
		label->setLeading(19);
		label->setColumnWidth(360);
		label->setTrans(20, 0, 0);
		element->addChild(label);
		
		ofxRectangleObject *b = new ofxRectangleObject(10,10);
		b->setTrans(0, 0, 0);
		b->setColor(ref->getColorByName(categories[i]));
		boxes.push_back(b);
		element->addChild(b);
		
		element->setTrans(ofGetWidth()*.65/2, ofGetHeight()*.8/2-20*i, 0);
		addChild(element);
		
	}
	
	// - - - - - - - - - - - - - - - - - - - - - - - - - -
	// Create a pulsing circle at each neighborhood's centroid (only if it has events).
	// - - - - - - - - - - - - - - - - - - - - - - - - - -

  // Copy the full neighborhoods vector, remove neighborhoods that don't have events.
  neighborhoodsContainingEvents = data->getGeoJson().getNeighborhoods();
	for (int i = 0; i < neighborhoodsContainingEvents.size(); i++) {
    if (neighborhoodsContainingEvents[i]->getEventCount() == 0){
      neighborhoodsContainingEvents.erase(neighborhoodsContainingEvents.begin() + i);
    }
  }
  // Create the centroid circles.
	for (int i = 0; i < neighborhoodsContainingEvents.size(); i++) {
    ofxCircleObject *centerCircle = new ofxCircleObject(20, 5);
    centerCircle->setTrans(2000*(neighborhoodsContainingEvents[i]->getCentroid() - data->getCentroid()));
    centerCircle->setAlpha(0);
    centerCircle->setColor(255, 255, 255);
    centroids.push_back(centerCircle);
    addChild(centerCircle);
  }
  
}

// Fade-in the event circles (that are colored by category) on a timeline, based on their update date.
void dsEventLayer::animateEvent(dsCitizensData *data) {
	
	for (int i = 0 ; i < events.size() ; i++){
		ageInSeconds = timeFromCurrent(dsEventLayer::dateParser(data->getEventTime(i)));
		events[i]->doMessage1f(OF_SETALPHA, 0.0, 0.01, OF_LINEAR, 0);
		events[i]->doMessage1f(OF_SETALPHA, ageInSeconds/10800, 0.5, OF_LINEAR, 255);
	}
	
}

// Pulses a centroid circle for each neighborhood that has events, the rate depending on its activity level.
void dsEventLayer::animateByEventRate(dsCitizensData *data, float iLength) {
	
	float fadeInLength = 0.5;
	
	for (int i = 0; i < neighborhoodsContainingEvents.size(); i++) {
    std::vector<dsEvent*> curNeighborhoodEvents = neighborhoodsContainingEvents[i]->getEvents();// get events for specific neighborhood
		centroids[i]->doMessage1f(OF_SETALPHA, 0.0, fadeInLength, OF_EASE_OUT, 200);								// fadeIn neighborhood centroid
    for (int j = 0; j < curNeighborhoodEvents.size(); j++) {
			float start = fadeInLength+j*iLength/curNeighborhoodEvents.size();												// start times based on the number of events
      float dur = iLength/curNeighborhoodEvents.size()/2;																				// Duration
      centroids[i]->doMessage1f(OF_SCALE, start, dur, OF_EASE_OUT, 1.6);												// Animate the scale to 1.6.
      centroids[i]->doMessage1f(OF_SCALE, start + dur, dur, OF_EASE_IN, 1.0);										// Animate the scale back to 1.0.
    }
		centroids[i]->doMessage1f(OF_SETALPHA, fadeInLength+iLength, fadeInLength, OF_EASE_OUT, 0);
  }
		
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Parse event time.
Poco::DateTime dsEventLayer::dateParser(string iTime) {
	
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
int dsEventLayer::timeFromCurrent(Poco::DateTime iPocoTime) {
	
	
	Poco::Timespan age;
	Poco::Timestamp current;
	Poco::DateTime currentTime = Poco::DateTime(current);
	
	
	age = currentTime - iPocoTime;
	
	float ageInSeconds = age.totalSeconds() - 14400;
	
	return (ageInSeconds);
	
	
}





