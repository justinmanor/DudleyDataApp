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
#include "Poco/DateTime.h"
#include "Poco/Timespan.h"

struct categoryCount{
  string categoryName;
  int eventCount;
};

struct neighborhoodStats{
  int nOpen = 0;
  int nClosed = 0;
  float openClosedRatio = 0;
  int nToday = 0;
  int nThisHour = 0;
  int nThisWeek = 0;
  std::vector<categoryCount> categoryCounts;
};

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
  void addEvent(dsEvent* iEvent);
  std::vector<dsEvent*> getEvents(){ return events; }
  void calculateStats(dsEvent* iEvent);
  
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
  neighborhoodStats stats;
  
  std::vector<dsEvent*> events;
  
  //TODO
  //polygon
  //events
};
