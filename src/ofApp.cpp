#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  string url = "https://mayors24.cityofboston.gov/open311/v2/requests.json?page_size=20";
  citizensData = new dsCitizensData(url);
  
  // NOT WORKING YET : For seeing the Boston map. Set the camera
  cam.setAutoDistance(true);
  cam.setNearClip(0.01);
  cam.setFarClip(100000);
  cam.setFov(45);
  cam.setDistance(500);
}

//--------------------------------------------------------------
void ofApp::update(){
  cam.lookAt(ofVec3f(0,0,0));
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(255, 255, 255);
  cam.begin();
  citizensData->getGeoJson().draw();
  cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
