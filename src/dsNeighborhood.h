//
//  dsNeighborhood.h
//  Dudley
//
//  Created by Sosolimited on 7/15/14.
//
//

#pragma once

#include "ofMain.h"
#include "dsEvent.h"
#include "ofxPolygonObject.h"

class dsNeighborhood {

public:
  dsNeighborhood();
  ~dsNeighborhood();
  
  int getEventCount(){ return events.size(); }
  
  void setName(string iName);
  string getName();
  void addVertX(float iVertX);
  vector<float> getVertsX();
  void addVertY(float iVertY);
  vector<float> getVertsY();
  void addBounds(float iLeftBound, float iRightBound, float iBottomBound, float iUpBound);
  float getBound(string iBound);
  void calculateCentroid();
  ofVec3f getCentroid();
  ofxPolygonObject* getPolygon();
	void addToEventCount(int iCount);
  void addEvent(dsEvent* iEvent);
  std::vector<dsEvent*> getEvents(){ return events; }
  
private:
  
  string name;
  vector<float> vertsX;
  vector<float> vertsY;
  float leftBound;
  float rightBound;
  float bottomBound;
  float topBound;
  ofVec3f centroid;
  ofxPolygonObject *polygon;

  std::vector<dsEvent*> events;
  
  int eventCount = 0;
  
  //TODO
  //polygon
  //events
};
