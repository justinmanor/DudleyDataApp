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

//
void dsCategory::calculateStats(dsEvent* iEvent){

  // Add to counter vars.
  if (iEvent->getStatus() == "open") { stats.nOpen++; }
  else if (iEvent->getStatus() == "closed") { stats.nClosed++; }
  
  Poco::DateTime now;
  Poco::Timespan diff = now - iEvent->getTime();
  
  int diffDaysFromEventToNow = diff.days();
  if (diffDaysFromEventToNow == 0) { stats.nToday++; }    // If the diff is 0, then it was in this current day.
  
  int diffHoursFromEventToNow = diff.totalHours();    // DEV: is off by 3 hours... timezone problem?
  if (diffHoursFromEventToNow == 0) { stats.nThisHour++; }    // If the diff is 0, then it was in this current hour.
  
  Poco::Timespan spanOneWeek(7 * Poco::Timespan::DAYS);
  Poco::DateTime dateAWeekAgo = now - spanOneWeek;
  Poco::Timespan spanFromEventToAWeekAgo = iEvent->getTime() - dateAWeekAgo;
  int diffDaysFromEventToAWeekAgo = spanFromEventToAWeekAgo.days();
  if (diffDaysFromEventToAWeekAgo >= 0){ stats.nThisWeek++; }   // If its 7 to 0 days ago, it's within this week.
  
  // Recalculate ratio.
  stats.openClosedRatio = stats.nClosed == 0 ? stats.nOpen/1 : (float)stats.nOpen/(float)stats.nClosed;
  
  // Increment count of event's category.
  ++stats.nEventsPerNeighborhood[iEvent->getNeighborhood()];

}

int dsCategory::getNeighborhoodCount(string iNeighborhoodName){
  return stats.nEventsPerNeighborhood[iNeighborhoodName];
}

