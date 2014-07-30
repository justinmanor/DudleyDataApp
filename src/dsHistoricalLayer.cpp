//
//  dsHistoricalLayer.cpp
//  Dudley
//
//  Created by Sosolimited on 7/29/14.
//
//

#include "dsHistoricalLayer.h"

dsHistoricalLayer::dsHistoricalLayer(dsCitizensData* iData) {
	
  // Setup.
  data = iData;
  ref = dsGraphicsRef::instance();
  timeOfLastUpdate = ofGetElapsedTimef();
  updateInterval = 30.0;                      // Set to update the layer at this interval.
  
  // Init drawing.
  drawCentroids();
}

dsHistoricalLayer::~dsHistoricalLayer() {}

void dsHistoricalLayer::idle(float iTime){
  
  float freqMultiplier = 20.0;
  
  //DEV: infinite animation that uses citizensData events directly so this is continuously updated.
  for (int i = 0; i < centroids.size(); i++) {
    float freq = float(neighborhoodsContainingEvents[i]->getEventCount()) / float(data->getNumEvents()) * freqMultiplier;
    float scale = (sin(freq * iTime * (M_PI*2)) + 1) / 2;
    centroids[i]->setScale(scale);
    
//    cout<<"centroid["<<i<<"] | scale = "<< scale << " | freq = "<< freq << " | time = "<< iTime << " | time*freq = "<< freq*iTime <<endl;
  }
  
  
  /*
  float timeSinceLastUpdate = ofGetElapsedTimef() - timeOfLastUpdate;
  if (timeSinceLastUpdate > updateInterval){
    cout << "dsHistoricalLayer::idle---------------- UPDATING @ interval: "<< updateInterval << endl;
    
    timeOfLastUpdate = ofGetElapsedTimef();
    
    drawCentroids();        // re-draw visuals. TODO: update so we don't just re-draw from scratch, but smoothly update the drawing to the new values.
  }
  */
}

void dsHistoricalLayer::drawCentroids(){
  
  // - - - - - - - - - - - - - - - - - - - - - - - - - -
	// Create a pulsing circle at each neighborhood's centroid (only if it has events).
	// - - - - - - - - - - - - - - - - - - - - - - - - - -
  
  // range = [0.5, 5] secs
  // domain = [minNumEventsInNeigh, maxNumEventsInNeigh]
  
  // Copy the full neighborhoods vector, remove neighborhoods that don't have events.
  neighborhoodsContainingEvents = data->getGeoJson().getNeighborhoods();
	for (int i = 0; i < neighborhoodsContainingEvents.size(); i++) {
    if (neighborhoodsContainingEvents[i]->getEventCount() == 0){
      neighborhoodsContainingEvents.erase(neighborhoodsContainingEvents.begin() + i);
    }
  }
  // Create the centroid circles.
	for (int i = 0; i < neighborhoodsContainingEvents.size(); i++) {
    ofxCircleObject *centerCircle = new ofxCircleObject(20, 5);
    centerCircle->setTrans(2000*(neighborhoodsContainingEvents[i]->getCentroid() - data->getCentroid()));
//    centerCircle->setAlpha(0);
    centerCircle->setAlpha(200);
    centerCircle->setColor(255, 255, 255);
    centroids.push_back(centerCircle);
    addChild(centerCircle);
  }
  
}

// Pulses a centroid circle for each neighborhood that has events, the rate depending on its activity level.
void dsHistoricalLayer::animateByEventRate(dsCitizensData *data, float iLength) {
	
	float fadeInLength = 0.5;
	
	for (int i = 0; i < neighborhoodsContainingEvents.size(); i++) {
    std::vector<dsEvent*> curNeighborhoodEvents = neighborhoodsContainingEvents[i]->getEvents();// get events for specific neighborhood
		centroids[i]->doMessage1f(OF_SETALPHA, 0.0, fadeInLength, OF_EASE_OUT, 200);								// fadeIn neighborhood centroid
    for (int j = 0; j < curNeighborhoodEvents.size(); j++) {
			float start = fadeInLength+j*iLength/curNeighborhoodEvents.size();												// start times based on the number of events
      float dur = iLength/curNeighborhoodEvents.size()/2;																				// Duration
      centroids[i]->doMessage1f(OF_SCALE, start, dur, OF_EASE_OUT, 1.6);												// Animate the scale to 1.6.
      centroids[i]->doMessage1f(OF_SCALE, start + dur, dur, OF_EASE_IN, 1.0);										// Animate the scale back to 1.0.
    }
		centroids[i]->doMessage1f(OF_SETALPHA, fadeInLength+iLength, fadeInLength, OF_EASE_OUT, 0);
  }
  
}
