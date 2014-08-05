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
#include "ofxSosoTrueTypeFont.h"
#include "ofxTextObject.h"
#include "ofxLineSegmentObject.h"
#include "ofxRectangleObject.h"
#include "ofColor.h"

class dsHistoricalLayer : public ofxObject {
  
public:
  
  dsHistoricalLayer(dsCitizensData* iData);
	~dsHistoricalLayer();

  void                  animateByEventRate(dsCitizensData *data, float iLength);
  void                  showLastFewEvents(bool iVisible);
  void                  showCentroidLabels(bool iVisible);
  
private:
	
  void									idle(float iTime);
  void                  drawNeighborhoodCentroids();
  void                  drawLastFewEvents();

public:

  dsGraphicsRef         *ref;
  
private:
  
  dsCitizensData* data;
  float timeOfLastUpdate;
  float updateInterval;
  
  vector<dsNeighborhood*>     neighborhoodsContainingEvents;     // Stores copy of data of only neighborhoods that have
  vector<ofxCircleObject*>		centroids;
  ofxObject*                  centroidsContainer;
  vector<ofxTextObject*>      centroidLabels;
  ofxObject*                  centroidLabelsContainer;
  vector<dsEvent*>            lastEvents;
  vector<ofxPolygonObject*>   lastEventShapes;
  ofxObject*                  lastEventShapesContainer;
  vector<ofxObject*>          categoryLabels;
  ofxObject*                  categoryLabelsContainer;
  
  ofxSosoTrueTypeFont*        fontCentroids;
  ofxSosoTrueTypeFont*        fontCategoryLabels;
  
};