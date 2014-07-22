//
//  dsNeighborhood.cpp
//  Dudley
//
//  Created by Sosolimited on 7/15/14.
//
//

#include "dsNeighborhood.h"

dsNeighborhood::dsNeighborhood(){
  polygon = NULL;
}

dsNeighborhood::~dsNeighborhood(){
  if (polygon != NULL)
    delete(polygon);
}

void dsNeighborhood::setName(string iName){
  name = iName;
}
string dsNeighborhood::getName(){
  return name;
}

void dsNeighborhood::addVertX(float iVertX){
  vertsX.push_back(iVertX);
}
vector<float> dsNeighborhood::getVertsX(){
  return vertsX;
}

void dsNeighborhood::addVertY(float iVertY){
  vertsY.push_back(iVertY);
}
vector<float> dsNeighborhood::getVertsY(){
  return vertsY;
}

void dsNeighborhood::addBounds(float iLeftBound, float iRightBound, float iBottomBound, float iTopBound){
  leftBound = iLeftBound;
  rightBound = iRightBound;
  bottomBound = iBottomBound;
  topBound = iTopBound;
  
  // Now that we have the bounds, calculate the centroid/center of the neighborhood.
  calculateCentroid();
}

float dsNeighborhood::getBound(string iBound){
  if (iBound == "left") { return leftBound; }
  else if (iBound == "right") { return rightBound; }
  else if (iBound == "bottom") { return bottomBound; }
  else if (iBound == "top") { return topBound; }
}

void dsNeighborhood::calculateCentroid(){
  if (leftBound && rightBound && bottomBound && topBound){
    centroid.x = (leftBound + rightBound)/2.0;
    centroid.y = (bottomBound + topBound)/2.0;
    centroid.z = 0;
  } else {
    ofLog() << "dsNeighborhood- ERROR : Cannot calculate centroid!";
  }
}

ofVec3f dsNeighborhood::getCentroid(){
  return centroid;
}

ofxPolygonObject* dsNeighborhood::getPolygon(){

  if (polygon == NULL) {
    ofLogNotice("polygon getting created of size " + ofToString(vertsX.size()));
    polygon = new ofxPolygonObject(vertsX.size());
    polygon->setDrawMode(OF_OUTLINE);
    
    for (int i = 0 ; i < vertsX.size() ; i ++) {
      polygon->setVertexPos(i, ofVec3f(vertsX[i], vertsY[i], 0));
    }
    
  } else {
    ofLogNotice("NO DATA MADE");

  }
  
  return polygon;
}

void dsNeighborhood::addEvent(dsEvent* iEvent){
  events.push_back(iEvent);
  
  //  DEV_JN
  calculateStats(iEvent);
}

//
void dsNeighborhood::calculateStats(dsEvent* iEvent){
  // Add to counter vars.
  if (iEvent->getStatus() == "open") { stats.nOpen++; }
  else if (iEvent->getStatus() == "closed") { stats.nClosed++; }
  
  Poco::DateTime now;
  Poco::Timespan diff = now - iEvent->getTime();
  if (diff.days() == 0) { stats.nToday++; }
  if (diff.totalHours() == 0) { stats.nThisHour++; }
//  if (diff.() == 0) { stats.nThisWeek++; }
  
  int diffDays = diff.days();
  int diffHours = diff.totalHours();    // is off... timezone problem?

  Poco::Timespan span(7 * Poco::Timespan::DAYS);
  Poco::DateTime a = now - span;
  Poco::Timespan b = now - a;
  int diffC = b.days();
  
  
  // Recalculate ratio.
  stats.openClosedRatio = stats.nClosed == 0 ? stats.nOpen/1 : (float)stats.nOpen/(float)stats.nClosed;
  
}
