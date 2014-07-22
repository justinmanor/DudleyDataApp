//
//  dsCategory.h
//  Dudley
//
//  Created by Sosolimited on 7/17/14.
//
//

#pragma once

#include "ofMain.h"
#include "dsEventCollection.h"
#include "dsEvent.h"
#include "Poco/DateTime.h"
#include "Poco/Timespan.h"
#include "Poco/Timezone.h"

struct categoryStats {
  int nOpen = 0;
  int nClosed = 0;
  float openClosedRatio = 0;
  int nToday = 0;
  int nThisHour = 0;
  int nThisWeek = 0;
  map<string, int> nEventsPerNeighborhood;      // Counts number of events per cateogry in neighborhood.
};

class dsCategory : public dsEventCollection {
  
public:
  
  dsCategory(string iName);
  ~dsCategory();
  
//  string getName(){ return name; }
//  std::vector<dsEvent*> getEvents(){ return events; }
  int getEventCount(){ return events.size(); }
  int getDayCount(){ return stats.nToday; }
  int getHourCount(){ return stats.nThisHour; }
  int getWeekCount(){ return stats.nThisWeek; }
  int getOpenCount(){ return stats.nOpen; }
  int getClosedCount(){ return stats.nClosed; }
  int getOpenClosedRatio(){ return stats.openClosedRatio; }
  map<string, int> getEventsPerNeighborhood(){ return stats.nEventsPerNeighborhood; }
  
  void addEvent(dsEvent* iEvent);
  void calculateStats(dsEvent* iEvent);
  
  //TODO
  int getNeighborhoodCount(string iNeighborhoodName);
  
private:
  
//  string name;
//  std::vector<dsEvent*> events;

  categoryStats stats;
  
};
