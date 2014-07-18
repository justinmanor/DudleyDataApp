#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  
  ref = dsGraphicsRef::instance();
  
  string url = "https://mayors24.cityofboston.gov/open311/v2/requests.json?page_size=250";
  citizensData = new dsCitizensData(url);
  
  // Disable the of setupScreen because now each scene has a custom renderer.
  ofDisableSetupScreen();
  
  scene = new ofxScene(ofGetWidth(), ofGetHeight());
  scene->setBackgroundColor(10, 10, 10);
  

  
	eventLayer = new dsEventLayer();
  eventLayer->buildEvents(citizensData);
  scene->getRoot()->addChild(eventLayer);

  
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
		eventLayer->animateByEventRate(citizensData);
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
