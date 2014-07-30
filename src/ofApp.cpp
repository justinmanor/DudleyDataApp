#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	

  //
  ref = dsGraphicsRef::instance();
  ofDisableSetupScreen();             // Disable the of setupScreen because now each scene has a custom renderer.

  scene = new ofxScene(ofGetWidth(), ofGetHeight());
  scene->setBackgroundColor(10, 10, 10);
	
  //
	citizensData = new dsCitizensData();
	scene->getRoot()->addChild(citizensData);         // Required to have its idle loop work.
  
	// ---- Dev or Production ----
	env = "production"; // set to "dev" or "production" -- dev pull 5 events every 5 seconds.
	initialGrab = Poco::Timespan(7,0,0,0,0); // Initial pull amount days,hr,min,sec,milsec
	setupEnv(env, initialGrab);
  
  //
  realtimeLayer = new dsRealtimeLayer();
  citizensData->addEventSubscriber(realtimeLayer);
	scene->getRoot()->addChild(realtimeLayer);
  
  //
  historicalLayer = new dsHistoricalLayer(citizensData);
  scene->getRoot()->addChild(historicalLayer);         // Required to have its idle loop work.
  
  // Draws/animates circles for each event and neighborhood centroids.
//	eventLayer = new dsEventLayer();
//  eventLayer->buildEvents(citizensData);
//  scene->getRoot()->addChild(eventLayer);

  // Draws the map of Boston neighborhoods.
  neighborhoodLayer = new dsNeighborhoodLayer();
  neighborhoodLayer->buildNeighborhoods(citizensData);
  scene->getRoot()->addChild(neighborhoodLayer);
	
  
  
}

//--------------------------------------------------------------
void ofApp::update(){
  
  scene->update(ofGetElapsedTimef());

}

//--------------------------------------------------------------
void ofApp::draw(){
  
  ofBackground(255, 255, 255);
  ofSetColor(250,0,0);
  scene->draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//animate events in relative to their time
	if (key == 'a') {
		eventLayer->animateEvent(citizensData);
	} else if (key == 's') {
//		eventLayer->animateByEventRate(citizensData, 10.0); // Passing Events and Length
    historicalLayer->animateByEventRate(citizensData, 10.0); // Passing Events and Length
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::setupEnv(string iEnv, Poco::Timespan iTimeSpan) {
	citizensData->setEnvironment(iEnv, iTimeSpan);
}
