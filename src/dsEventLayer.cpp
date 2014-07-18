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

void dsEventLayer::buildEvents(dsCitizensData *data)
{
  
	for (int i = 0 ; i < data->getNumEvents() ; i ++){
    ofxCircleObject *c = new ofxCircleObject(20, 2);
    c->setTrans(2000.0*(data->getEventCoords(i) - data->getCentroid()));
		c->setAlpha(255);
		string category = data->getEventCategory(i);
		c->setColor(ref->getColorByName(category));
		
    events.push_back(c);
    addChild(c);
  }
	
	// - - - - - - - - - - - - - - - - - - - - - - - - - -
	// Build Event Legend
	// - - - - - - - - - - - - - - - - - - - - - - - - - -
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
	// Create the neighborhood event counts
	// - - - - - - - - - - - - - - - - - - - - - - - - - -
	for (int i = 0; i < data->getNumNeighborhoods(); i++) {
		int theCount = data->getGeoJson().getNeighborhood(i)->getEventCount();
		//++neighborhoodEventCounts[theName];
		float xPos = data->getGeoJson().getNeighborhood(i)->getCentroid().x;
		cout << xPos << endl;
		ofxCircleObject *centerCircle = new ofxCircleObject(20, 20);
		//cout << setTrans(data->getGeoJson().getNeighborhood(i)->getCentroid() << endl;
		centerCircle->setTrans(data->getGeoJson().getNeighborhood(i)->getCentroid().x, 10*i, 0);
		centerCircle->setAlpha(255);
	

		centerCircle->setColor(255, 255, 255);
		
    centroids.push_back(centerCircle);
    addChild(centerCircle);


	}
  
}

void dsEventLayer::animateEvent(dsCitizensData *data) {
	
	for (int i = 0 ; i < events.size() ; i++){

		events[i]->doMessage1f(OF_SETALPHA, 0.0, 0.01, OF_LINEAR, 0);
		events[i]->doMessage1f(OF_SETALPHA, data->getAgeInSeconds(i)/10800, 0.5, OF_LINEAR, 255);
		
	}
	
}

void dsEventLayer::animateByEventRate(dsCitizensData *data) {

	for (int i = 0 ; i < events.size() ; i++){
		
		events[i]->doMessage1f(OF_SETALPHA, 0.0, 0.01, OF_LINEAR, 0);
		events[i]->doMessage1f(OF_SETALPHA, data->getAgeInSeconds(i)/10800, 0.5, OF_LINEAR, 255);
		
	}

}





