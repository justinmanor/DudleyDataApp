//
//  dsNeighborhood.cpp
//  Dudley
//
//  Created by Sosolimited on 7/15/14.
//
//

#include "dsNeighborhood.h"

dsNeighborhood::dsNeighborhood(){
  
}

dsNeighborhood::~dsNeighborhood(){}

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

void dsNeighborhood::addBounds(float iLeft, float iRight, float iBottom, float iTop){
  left = iLeft;
  right = iRight;
  bottom = iBottom;
  top = iTop;
}

float dsNeighborhood::getBound(string iBound){
  if (iBound == "left") { return left; }
  else if (iBound == "right") { return right; }
  else if (iBound == "bottom") { return bottom; }
  else if (iBound == "top") { return top; }
}