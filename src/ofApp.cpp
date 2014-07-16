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
  
  realtimeLayer = new ofxObject();
  scene->getRoot()->addChild(realtimeLayer);
  
  for (int i = 0 ; i < citizensData->getNumEvents() ; i ++){
    ofxCircleObject *c = new ofxCircleObject(20, 2);
    c->setTrans(2000.0*(citizensData->getEventCoords(i) - citizensData->getCentroid()));
		c->setAlpha(0);
		string category = citizensData->getEventCategory(i);
		if (category == "Graffiti") {
			//set color for graffiti
			c->setColor(43, 76, 243);
		} else if (category == "Other") {
			//set color for Other
			c->setColor(255, 255, 255);
		} else if (category == "Pothole") {
			//set color for Pothole
			c->setColor(227, 162, 85);
		} else if (category == "Sidewalk Patch") {
			//set color for sidewalk path
			c->setColor(58, 175, 87);
		} else if (category == "Damage Sign") {
			//set color for damage sign
			c->setColor(222, 121, 92);
		} else if (category == "Streetlight") {
			//set color for streetlight
			c->setColor(204, 112, 170);
		}
		
    events.push_back(c);
    realtimeLayer->addChild(c);
  }
	
	//vector<string> catNames = {"Graffiti", "Other", "Pothole", "Sidewalk Patch", "Damage Sign", "Streetlight"};
//	for (int i = 0; i < catNames.size(); i++) {
//		ofxPolygonObject *square = new ofxPolygonObject(4);
//		square->setVertexPos(0, ofVec3f(ofGetWidth()*.7/2, ofGetHeight()*.8/2-20*i));
//
//		square->setVertexPos(1, ofVec3f(ofGetWidth()*.7/2+10, ofGetHeight()*.8/2-20*i));
//
//		square->setVertexPos(2, ofVec3f(ofGetWidth()*.7/2+10, ofGetHeight()*.8/2-10-20*i));
//
//		square->setVertexPos(3, ofVec3f(ofGetWidth()*.7/2, ofGetHeight()*.8/2-10-20*i));
//		realtimeLayer->addChild(square);
//	}
  
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
		for (int i = 0 ; i < events.size() ; i++){
			cout << citizensData->getEventCategory(i) << endl;
			events[i]->doMessage1f(OF_SETALPHA, 0.0, 0.01, OF_LINEAR, 0);
			events[i]->doMessage1f(OF_SETALPHA, citizensData->getAgeInSeconds(i)/10800, 0.5, OF_LINEAR, 255);
			
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
