#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  string url = "https://mayors24.cityofboston.gov/open311/v2/requests.json?page_size=250";
  citizensData = new dsCitizensData(url);
  
  // Disable the of setupScreen because now each scene has a custom renderer.
  ofDisableSetupScreen();
  /*
  // NOT WORKING YET : For seeing the Boston map. Set the camera
  cam.setAutoDistance(true);
  cam.setNearClip(0.01);
  cam.setFarClip(100000);
  cam.setFov(45);
  cam.setDistance(500);
  */
  
  scene = new ofxScene(ofGetWidth(), ofGetHeight());
  scene->setBackgroundColor(10, 10, 10);
  
  canvas = new ofxObject();
  //canvas->setScale(2);
  scene->getRoot()->addChild(canvas);
  
  for (int i = 0 ; i < citizensData->getNumEvents() ; i ++){
    ofxCircleObject *c = new ofxCircleObject(20, 2);
    c->setTrans(2000*(citizensData->getEventCoords(i) - citizensData->getCentroid()));
    events.push_back(c);
    canvas->addChild(c);
  }
  
  ofxCircleObject *d = new ofxCircleObject(10,5);
  d->setColor(200,0,0);
  //d->setTrans(900, -500,0);
  scene->getRoot()->addChild(d);
  
  
}

//--------------------------------------------------------------
void ofApp::update(){
  
  scene->update(ofGetElapsedTimef());
  //cam.lookAt(ofVec3f(0,0,0));
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(255, 255, 255);
  ofSetColor(250,0,0);
  //citizensData->draw();
  scene->draw();
  /*
  cam.begin();
  citizensData->getGeoJson().draw();
  cam.end();
   */
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
