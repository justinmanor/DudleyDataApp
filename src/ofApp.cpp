#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//  string file = "dudley-june23-750results-manuallycollated.json";
//  string url = "https://mayors24test.cityofboston.gov:6443/open311/v2/requests.json?callback=handledata&page_size=200";   //JSONP doesn't work with ofxJSON
  string url = "https://mayors24.cityofboston.gov/open311/v2/requests.json?page_size=250";
  citizensData = new dsCitizensData(url);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

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
