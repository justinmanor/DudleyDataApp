//
//  dsHistoricalLayer.h
//  Dudley
//
//  Created by Sosolimited on 7/29/14.
//
//

#pragma once

#include "ofxObject.h"
#include "ofMain.h"
#include "dsGraphicsRef.h"
#include "dsCitizensData.h"
#include "dsEvent.h"
#include "ofxCircleObject.h"

class dsHistoricalLayer : public ofxObject {
  
public:
  
  dsHistoricalLayer(dsCitizensData* iData);
	~dsHistoricalLayer();

  void                  animateByEventRate(dsCitizensData *data, float iLength);
  void                  showLastFewEvents(bool iVisible);
  
private:
	
  void									idle(float iTime);
  void                  drawCentroids();
  void                  drawLastFewEvents();

public:

  dsGraphicsRef         *ref;
  
private:
  
  dsCitizensData* data;
  float timeOfLastUpdate;
  float updateInterval;
  
  vector<dsNeighborhood*>     neighborhoodsContainingEvents;     // Stores copy of data of only neighborhoods that have
  vector<ofxCircleObject*>		centroids;
  vector<dsEvent*>            lastEvents;
  vector<ofxPolygonObject*>   lastEventShapes;
  
};