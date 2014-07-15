//
//  dsNeighborhood.h
//  Dudley
//
//  Created by Sosolimited on 7/15/14.
//
//

#pragma once

#include "ofMain.h"

class dsNeighborhood {

public:
  dsNeighborhood();
  ~dsNeighborhood();
  
  void setName(string iName);
  string getName();
  void addVertX(float iVertX);
  vector<float> getVertsX();
  void addVertY(float iVertY);
  vector<float> getVertsY();
  void addBounds(float iLeft, float iRight, float iBottom, float iUp);
  float getBound(string iBound);
  
private:
  
  string name;
  vector<float> vertsX;
  vector<float> vertsY;
  float left;
  float right;
  float bottom;
  float top;
  
  //TODO
  //centroid
  //polygon
  //events
};
