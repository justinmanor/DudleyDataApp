//
//  dsNeighborhoodLayer.h
//  Dudley
//
//  Created by Sosolimited on 7/16/14.
//
//

#pragma once

#include "ofxObject.h"
#include "dsCitizensData.h"

class dsNeighborhoodLayer : public ofxObject {
  
public:
  
	
  dsNeighborhoodLayer();
	~dsNeighborhoodLayer();
  
	void                        buildNeighborhoods(dsCitizensData *data);
  
public:
  
  dsCitizensData              *citizensData;
  vector <ofxPolygonObject *> neighborhoods;
  
  
};