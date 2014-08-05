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
  drawNeighborhoodCentroids();
  drawLastFewEvents();
}

dsHistoricalLayer::~dsHistoricalLayer() {}

void dsHistoricalLayer::idle(float iTime){
  
  /*
  // OLD
  // Infinite animation that uses citizensData events directly so this is continuously updated.
  float freqMultiplier = 20.0;
  for (int i = 0; i < centroids.size(); i++) {
    float freq = float(neighborhoodsContainingEvents[i]->getEventCount()) / float(data->getNumEvents()) * freqMultiplier;
    float scale = (sin(freq * iTime * (M_PI*2)) + 1) / 2;
    centroids[i]->setScale(scale);
    
    //    cout<<"centroid["<<i<<"] | scale = "<< scale << " | freq = "<< freq << " | time = "<< iTime << " | time*freq = "<< freq*iTime <<endl;
  }
  */
  
  /*
  //OLD
  // Redraw centroids only when we hit the interval.
  float timeSinceLastUpdate = ofGetElapsedTimef() - timeOfLastUpdate;
  if (timeSinceLastUpdate > updateInterval){
  cout << "dsHistoricalLayer::idle---------------- UPDATING @ interval: "<< updateInterval << endl;

  timeOfLastUpdate = ofGetElapsedTimef();

  drawNeighborhoodCentroids();        // re-draw visuals. TODO: update so we don't just re-draw from scratch, but smoothly update the drawing to the new values.
  }
  */
}

// Create a small circle on map for the last few events.
void dsHistoricalLayer::drawLastFewEvents(){
  
  // Create a legend for category colors.
	vector <string> labelCategories;
  labelCategories.push_back("Sidewalk Patch");
  labelCategories.push_back("Graffiti");
  labelCategories.push_back("Pothole");
  labelCategories.push_back("Streetlight");
  labelCategories.push_back("Damaged Sign");
  labelCategories.push_back("Other");
	fontCategoryLabels = new ofxSosoTrueTypeFont();
  fontCategoryLabels->loadFont("Arial.ttf", 14, true,  true, false, true);
	fontCategoryLabels->setKerningPair('T', 'y', -2);
  categoryLabelsContainer = new ofxObject();
	for (int i = 0; i < labelCategories.size(); i++ ) {
		ofxObject *labelElement = new ofxObject();
		
		ofxTextObject *labelText = new ofxTextObject(fontCategoryLabels, labelCategories[i]);
		labelText->setColor(255, 255, 255);
		labelText->setPointSize(16);
		labelText->setLeading(19);
		labelText->setColumnWidth(360);
		labelText->setTrans(20, 0, 0);
		labelElement->addChild(labelText);
		
		ofxRectangleObject *labelColorBox = new ofxRectangleObject(10,10);
		labelColorBox->setTrans(0, 0, 0);
		labelColorBox->setColor(ref->getColorByName(labelCategories[i]));
//		boxes.push_back(b);
		labelElement->addChild(labelColorBox);
		
		labelElement->setTrans(ofGetWidth()*.65/2, ofGetHeight()*.8/2-20*i, 0);
    categoryLabels.push_back(labelElement);
//		addChild(labelElement);
    categoryLabelsContainer->addChild(labelElement);
	}
  addChild(categoryLabelsContainer);
  categoryLabelsContainer->setZ(3);

  
  // Copy a slice/subvector of main events vector: the last 5 events.
  int numLastEventsDesired = 10;
  vector<dsEvent*>::const_iterator first = data->getEvents().end() - numLastEventsDesired;
  vector<dsEvent*>::const_iterator last = data->getEvents().end();
  lastEvents.assign(first, last);
  
  // Create triangle shapes for them.
  lastEventShapesContainer = new ofxObject();
  for (int i = 0 ; i < lastEvents.size() ; i ++){
    ofxPolygonObject* triangle = new ofxPolygonObject(3);
    ofVec3f centerPoint = data->getEventCoords(lastEvents[i]->getId());
    triangle->setVertexPos(0, ofVec3f(-6,-6,0));
    triangle->setVertexPos(1, ofVec3f(6,-6,0));
    triangle->setVertexPos(2, ofVec3f(0,6,0));
    triangle->setTrans(2000.0*(centerPoint - data->getCentroid()));

    //    triangle->setColor(ref->getColorByName("lastFewEvents"));
    string category = data->getEventCategory(i);
		triangle->setColor(ref->getColorByName(category));

    triangle->setAlpha(255);
    lastEventShapes.push_back(triangle);
    lastEventShapesContainer->addChild(triangle);
  }
  addChild(lastEventShapesContainer);
  lastEventShapesContainer->setZ(2);
  
}

void dsHistoricalLayer::showLastFewEvents(bool iVisible){
//  for (auto e : lastEventShapes){
//    (iVisible) ? e->show() : e->hide();
//  }
  if(iVisible){
    lastEventShapesContainer->show();
    categoryLabelsContainer->show();
  } else {
    lastEventShapesContainer->hide();
    categoryLabelsContainer->hide();
  }
  
  
}

// Create a pulsing circle at each neighborhood's centroid (only if it has events).
void dsHistoricalLayer::drawNeighborhoodCentroids(){
  
  // Copy the full neighborhoods vector, remove neighborhoods that don't have events.
  neighborhoodsContainingEvents = data->getGeoJson().getNeighborhoods();
	for (int i = 0; i < neighborhoodsContainingEvents.size(); i++) {
    if (neighborhoodsContainingEvents[i]->getEventCount() == 0){
      neighborhoodsContainingEvents.erase(neighborhoodsContainingEvents.begin() + i);
    }
  }
  
  vector<int> neighborhoodNumRange = data->getNeighborhoodEventsNumRange();
  fontCentroids = new ofxSosoTrueTypeFont();
  fontCentroids->loadFont("Arial.ttf", 14, true,  true, false, true);
	fontCentroids->setKerningPair('T', 'y', -2);

  // Create the centroid circles & labels.
  centroidsContainer = new ofxObject();
  centroidLabelsContainer = new ofxObject();
	for (int i = 0; i < neighborhoodsContainingEvents.size(); i++) {
    // Circle.
    float radius = ofMap(neighborhoodsContainingEvents[i]->getEventCount(), neighborhoodNumRange[0], neighborhoodNumRange[1], 2, 25);
    ofVec3f center = 2000*(neighborhoodsContainingEvents[i]->getCentroid() - data->getCentroid());
    ofxCircleObject *centroid = new ofxCircleObject(20, radius);
    centroid->setTrans(center);
    centroid->setAlpha(150);
    centroid->setColor(255, 255, 255);
    centroids.push_back(centroid);
    centroidsContainer->addChild(centroid);
    // Label.
    string labelText = ofToString(neighborhoodsContainingEvents[i]->getEventCount());
    ofxTextObject *label = new ofxTextObject(fontCentroids, labelText);
    label->setColor(ofColor::magenta);
		label->setPointSize(14);
		label->setTrans(center.x-(label->getWidth()/2), center.y, center.z);
    label->hide();
    centroidLabels.push_back(label);
    centroidLabelsContainer->addChild(label);
    
//    string labelText = neighborhoodsContainingEvents[i]->getName() +" : "+ ofToString(neighborhoodsContainingEvents[i]->getEventCount());
//    ofxTextObject *label = new ofxTextObject(fontCentroids, labelText);
//    label->setColor(255, 255, 255);
//		label->setPointSize(12);
//		label->setTrans(ofGetWidth()*.65/2, ofGetHeight()*.8/2-20*i, 0);
//    centroidLabels.push_back(label);
//		addChild(label);

  }
  addChild(centroidsContainer);
  centroidsContainer->setZ(1);
  addChild(centroidLabelsContainer);
  centroidLabelsContainer->setZ(3);
  
}

void dsHistoricalLayer::showCentroidLabels(bool iVisible){
  for (auto cl : centroidLabels){
    (iVisible) ? cl->show() : cl->hide();
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
