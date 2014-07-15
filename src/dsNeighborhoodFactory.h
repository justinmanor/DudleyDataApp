//
//  dsNeighborhoodFactory.h
//  Dudley
//
//  Created by Sosolimited on 7/11/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofUtils.h"
#include "ofxJSONElement.h"
#include "ofxPolygonObject.h"

class dsNeighborhoodFactory{

struct neighborhoodBoundingBox {
  string name;
  float left;
  float right;
  float bottom;
  float top;
  ofVec3f centroid;
  vector<float> vertsX;
  vector<float> vertsY;
};

public:
  dsNeighborhoodFactory();
  ~dsNeighborhoodFactory();
  bool load(string _path);
  void setupNeighborhoodBoundingBoxes();
  string getNeighborhoodForPoint(float testX, float testY);
  bool isPointInPolygon(int nvert, vector<float> vertx, vector<float> verty, float testx, float testy);
  int getNeighborhoodCount() { return neighborhoodBoundingBoxes.size(); }
  ofVec3f getNeighborhoodCentroid(int index);
  //void generatePolygons();
  
private:
  ofxJSONElement result;
  std::vector<neighborhoodBoundingBox> neighborhoodBoundingBoxes;      // Stores the coords for each neighborhood's bounding boxes.

};