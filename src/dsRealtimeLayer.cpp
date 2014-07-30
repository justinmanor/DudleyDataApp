//
//  dsRealtimeLayer.cpp
//  Dudley
//
//  Created by Sosolimited on 7/22/14.
//
//

#include "dsRealtimeLayer.h"

dsRealtimeLayer::dsRealtimeLayer() {
	
  ref = dsGraphicsRef::instance();
  
}

dsRealtimeLayer::~dsRealtimeLayer() {}

void dsRealtimeLayer::handleNewEvent(dsEvent* iEvent){
  ofLog()<< "dsRealtimeLayer::handleNewEvent - - - - - - - - - - -"<< endl;
	//cout << "Handling New EVENTs" << endl;
  //cout<< iEvent->getId() <<endl;
	buildEvents(iEvent);
	
}

void dsRealtimeLayer::buildEvents(dsEvent* iEvent){
	
	cout << "buildEvent from RealtimeLayer Fired" << endl;
	ofxCircleObject *newEvents = new ofxCircleObject(20,10);
	ofVec3f coords = ofVec3f(iEvent->getLat(), iEvent->getLon(), 0);
	cout << iEvent->getLon() << " : " << iEvent->getLat() << endl;
	newEvents->setTrans(2000.0*(coords - ref->getDrawingCentroid()));
	newEvents->setAlpha(255);
	newEvents->setColor(100, 150, 240);
	addChild(newEvents);
	animateEvent(newEvents);

}

void dsRealtimeLayer::animateEvent(ofxCircleObject* iNewEvent){

	iNewEvent->doMessage1f(OF_SCALE, 0.1, 5.0, OF_LINEAR, 0);

}
