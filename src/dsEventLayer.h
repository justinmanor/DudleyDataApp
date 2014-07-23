//
//  dsEventLayer.h
//  Dudley
//
//  Created by Sosolimited on 7/16/14.
//
//

#pragma once

#include "dsCitizensDataSubscriber.h"
//#include "ofxObject.h"
#include "dsGraphicsRef.h"
#include "dsCitizensData.h"
#include "ofxCircleObject.h"
#include "ofxRectangleObject.h"
#include "ofxTextObject.h"
#include "dsEvent.h"

#include "Poco/LocalDateTime.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeParser.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Timestamp.h"
#include <ctime>

//class dsEventLayer : public ofxObject {
class dsEventLayer : public dsCitizensDataSubscriber {
  
public:
  
	
  dsEventLayer();
	~dsEventLayer();

  void  handleNewEvent(dsEvent* iEvent);
	void	buildEvents(dsCitizensData *data);
	void	animateEvent(dsCitizensData *data);
	void	animateByEventRate(dsCitizensData *data, float iLength);
	
  
public:
  
  dsGraphicsRef									*ref;
  dsCitizensData								*citizensData;
  vector <ofxCircleObject *>		events;
	vector <ofxCircleObject *>		centroids;
	vector <ofxRectangleObject *> boxes;
	vector <ofxTextObject *>			labels;
	vector <ofxObject *>					elements;
	
	ofxSosoTrueTypeFont						*font16;

private:
	
	Poco::DateTime	dateParser(string iTime);
	int							timeFromCurrent(Poco::DateTime iPocoTime);
	
  std::vector<dsNeighborhood*> neighborhoodsContainingEvents;     // Stores copy of data of only neighborhoods that have events.
	
	float						ageInSeconds;
  
};