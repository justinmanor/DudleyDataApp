#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
  //
  ref = dsGraphicsRef::instance();
  ofDisableSetupScreen();             // Disable the of setupScreen because now each scene has a custom renderer.

  scene = new ofxScene(ofGetWidth(), ofGetHeight());
  scene->setBackgroundColor(10, 10, 10);
	
  // ------------------------------------------------------------
  // Data stuff.
  // ------------------------------------------------------------
  
	citizensData = new dsCitizensData();
	scene->getRoot()->addChild(citizensData);         // Required to have its idle loop work.
  
	// ---- Dev or Production ----
	env = "dev"; // set to "dev" or "production" -- dev pull 5 events every 5 seconds.
	initialGrab = Poco::Timespan(7,0,0,0,0); // Initial pull amount days,hr,min,sec,milsec
	setupEnv(env, initialGrab);
  
  // ------------------------------------------------------------
  // Graphic layers stuff.
  // ------------------------------------------------------------
  
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
	
  // ------------------------------------------------------------
  // GUI stuff.
  // ------------------------------------------------------------
  
  // Build UIObject
  UIObject = new dsUIObject();
  UIObject->setup();
  scene->getRoot()->addChild(UIObject);
  UIObject->setVisible(true);
  
  int cornerOffset = 20;
  
  int UI_x = -ofGetWindowWidth()/2 + cornerOffset;
  int UI_y = ofGetWindowHeight()/2 - cornerOffset;
  UIObject->setTrans(UI_x, UI_y, 0);
  
  // Add Event Listeners
  ofAddListener(UIObject->UI->newGUIEvent, this, &ofApp::UIEvent);
  
}

//--------------------------------------------------------------
void ofApp::update(){
  
  scene->update(ofGetElapsedTimef());
  
  UIObject->update(); // This could also be done with an idle() method in UIObject.

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

//--------------------------------------------------------------
// Monitor UI events to update the appropriate values based on input.
void ofApp::UIEvent(ofxUIEventArgs &e){
  
  string name = e.widget->getName();
  
  if (name == "toggle bg control") {
    ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget;
    bgControl = toggle->getValue();
  } else if (name == "red"){
    ofxUIMinimalSlider *slider = (ofxUIMinimalSlider *) e.widget;
    sliderR = (int) slider->getValue();
  } else if (name == "green"){
    ofxUIMinimalSlider *slider = (ofxUIMinimalSlider *) e.widget;
    sliderG = (int) slider->getValue();
  } else if (name == "blue"){
    ofxUIMinimalSlider *slider = (ofxUIMinimalSlider *) e.widget;
    sliderB = (int) slider->getValue();
  } else if (name == "invert bg color"){
    ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
    bgInvert = button->getValue();
  } else if (name == "position") {
    ofxUI2DPad *padPos = (ofxUI2DPad *) e.widget;
    xPosition = (float) padPos->getValue().x*ofGetWidth();
    yPosition = (float) padPos->getValue().y*ofGetHeight();
  } else if (name == "resolution") {
    ofxUIMinimalSlider *slider = (ofxUIMinimalSlider *) e.widget;
    sliderRes = (int) slider->getValue();
  } else if (name == "scale") {
    ofxUIMinimalSlider *slider = (ofxUIMinimalSlider *) e.widget;
    sliderScale = (float) slider->getValue();
  } else if (name == "Smile") {
    ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
    toggleSmile = toggle->getValue();
  }
  
  
}

