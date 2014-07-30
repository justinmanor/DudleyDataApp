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
#include "dsGraphicsRef.h"

class dsNeighborhoodFactory{

public:
  dsNeighborhoodFactory();
  ~dsNeighborhoodFactory();
	
  bool													load(string _path);
  void													setupNeighborhoods();
  string												getNeighborhoodForPoint(float testX, float testY);
  bool													isPointInPolygon(int nvert, vector<float> vertx, vector<float> verty, float testx, float testy);
  int														getNeighborhoodCount() { return neighborhoods.size(); }
  dsNeighborhood*								getNeighborhood(int index);
  ofVec3f												getNeighborhoodCentroid(int index);
  std::vector<dsNeighborhood*>	getNeighborhoods(){ return neighborhoods; }
	ofVec3f												getCityCentroid() { return cityCentroid; }
	
  //void generatePolygons();
  
private:
	
	dsGraphicsRef									*ref;
	
  ofxJSONElement								result;
//  std::vector<dsNeighborhood> neighborhoods;      // Stores the coords for each neighborhood's bounding boxes.
  std::vector<dsNeighborhood*>	neighborhoods;      // Stores the coords for each neighborhood's bounding boxes.
	ofVec3f												cityCentroid;
	vector<ofVec3f>								neigCentroids;
  
};