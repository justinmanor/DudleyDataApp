//
//  dsEventLayer.h
//  Dudley
//
//  Created by Sosolimited on 7/16/14.
//
//

#pragma once

#include "ofxObject.h"
#include "dsGraphicsRef.h"
#include "dsCitizensData.h"
#include "ofxCircleObject.h"
#include "ofxRectangleObject.h"
#include "ofxTextObject.h"

class dsEventLayer : public ofxObject {
  
public:
  
	
  dsEventLayer();
	~dsEventLayer();
  
	void	buildEvents(dsCitizensData *data);
	void	animateEvent(dsCitizensData *data);
	void	animateByEventRate(dsCitizensData *data);
	
  
public:
  
  dsGraphicsRef               *ref;
  dsCitizensData              *citizensData;
  vector <ofxCircleObject *> events;
	vector <ofxCircleObject *> centroids;
	vector <ofxRectangleObject *> boxes;
	vector <ofxTextObject *>	labels;
	vector <ofxObject *>			elements;
	
	ofxSosoTrueTypeFont				*font16;

private:
	
	map<string, int> neighborhoodEventCounts;
	vector<string> simpleCount;
  
};