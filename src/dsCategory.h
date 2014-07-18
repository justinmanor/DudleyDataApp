//
//  dsCategory.h
//  Dudley
//
//  Created by Sosolimited on 7/17/14.
//
//

#pragma once
#include "ofMain.h"
//#include "dsCitizensData.h"

//class dsCitizensData;   // forward-declaration.

class dsCategory {
  
public:
  
  dsCategory(string iName);
  ~dsCategory();
  
//  void addEvent(event* iEvent);
  float getNeighborhoodCount(string iNeighborhoodName);
  
private:
  
  string id;
  string name;
//  vector<event*> events;
  
};
