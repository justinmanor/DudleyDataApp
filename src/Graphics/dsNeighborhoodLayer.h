//
//  dsNeighborhoodLayer.h
//  Dudley
//
//  Created by Sosolimited on 7/16/14.
//
//

#pragma once

#include "ofxObject.h"
#include "dsGraphicsRef.h"
#include "dsCitizensData.h"

class dsNeighborhoodLayer : public ofxObject {
  
public:
  
	
  dsNeighborhoodLayer();
	~dsNeighborhoodLayer();
  //void doIdle(float iTime) { circle[i]->setRadius(sin(numEvents/pi)); }
	void                        buildNeighborhoods(dsCitizensData *data);
  
public:
  
  dsGraphicsRef               *ref;
  dsCitizensData              *citizensData;
  vector <ofxPolygonObject *> neighborhoods;
  
  
};