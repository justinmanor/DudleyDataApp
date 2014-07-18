//
//  dsCategory.cpp
//  Dudley
//
//  Created by Sosolimited on 7/17/14.
//
//

#include "dsCategory.h"

dsCategory::dsCategory(string iName){
  name = iName;
}

dsCategory::~dsCategory(){}

void dsCategory::addEvent(dsEvent* iEvent){
  events.push_back(iEvent);
}
