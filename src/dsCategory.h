//
//  dsCategory.h
//  Dudley
//
//  Created by Sosolimited on 7/17/14.
//
//

#pragma once
#include "ofMain.h"
#include "dsEvent.h"

class dsCategory {
  
public:
  
  dsCategory(string iName);
  ~dsCategory();
  
  int getId(){ return id; }
  string getName(){ return name; }
  std::vector<dsEvent*> getEvents(){ return events; }
  int getEventCount(){ return events.size(); }
  
  void addEvent(dsEvent* iEvent);
  
  //TODO
  float getNeighborhoodCount(string iNeighborhoodName);
  
private:
  
  int id;
  string name;
  std::vector<dsEvent*> events;
  
};
