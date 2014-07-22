//
//  dsEventCollection.cpp
//  Dudley
//
//  Created by Sosolimited on 7/22/14.
//
//

#include "dsEventCollection.h"

//
void dsEventCollection::addEvent(dsEvent* iEvent){
  events.push_back(iEvent);
  calculateStats(iEvent);
}
