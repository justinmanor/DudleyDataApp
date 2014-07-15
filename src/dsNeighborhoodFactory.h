//
//  dsNeighborhoodFactory.h
//  Dudley
//
//  Created by Sosolimited on 7/11/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxJSONElement.h"
#include "dsNeighborhood.h"
#include "ofxPolygonObject.h"

class dsNeighborhoodFactory{

public:
  dsNeighborhoodFactory();
  ~dsNeighborhoodFactory();
  bool load(string _path);
  void setupNeighborhoods();
  string getNeighborhoodForPoint(float testX, float testY);
  bool isPointInPolygon(int nvert, vector<float> vertx, vector<float> verty, float testx, float testy);
  int getNeighborhoodCount() { return neighborhoods.size(); }
  ofVec3f getNeighborhoodCentroid(int index);
  //void generatePolygons();
  
private:
  ofxJSONElement result;
  std::vector<dsNeighborhood> neighborhoods;      // Stores the coords for each neighborhood's bounding boxes.
};