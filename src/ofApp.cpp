#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  string url = "https://mayors24.cityofboston.gov/open311/v2/requests.json?page_size=250";
  citizensData = new dsCitizensData(url);
  
  // Disable the of setupScreen because now each scene has a custom renderer.
  ofDisableSetupScreen();
  
  scene = new ofxScene(ofGetWidth(), ofGetHeight());
  scene->setBackgroundColor(10, 10, 10);
  
  realtimeLayer = new ofxObject();
  scene->getRoot()->addChild(realtimeLayer);
  
  for (int i = 0 ; i < citizensData->getNumEvents() ; i ++){
    ofxCircleObject *c = new ofxCircleObject(20, 2);
    c->setTrans(2000.0*(citizensData->getEventCoords(i) - citizensData->getCentroid()));
		c->setAlpha(0);
    events.push_back(c);
    realtimeLayer->addChild(c);
  }
  
  historicLayer = new ofxObject();
  scene->getRoot()->addChild(historicLayer);
  
  for (int i = 0 ; i < citizensData->getNumNeighborhoods() ; i ++){
    ofxCircleObject *c = new ofxCircleObject(20, 20, 18);
    c->setColor(0, 200, 200);
    c->setTrans(2000.0*(citizensData->getGeoJson().getNeighborhoodCentroid(i)  - citizensData->getCentroid()));
    neighborhoodCircles.push_back(c);
    historicLayer->addChild(c);
  }
  
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
		for (int i = 0 ; i < events.size() ; i++){
			
			events[i]->doMessage1f(OF_SETALPHA, i/100.0, 0.5, OF_LINEAR, 255);
		}
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
