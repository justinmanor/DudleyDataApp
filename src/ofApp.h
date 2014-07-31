#pragma once

#include "ofMain.h"
#include "ofxScene.h"
#include "dsGraphicsRef.h"
#include "ofxCircleObject.h"

#include "dsUIObject.h"
#include "dsCitizensData.h"
#include "dsNeighborhoodLayer.h"
#include "dsRealtimeLayer.h"
#include "dsHistoricalLayer.h"
#include "dsEventLayer.h"

class ofApp : public ofBaseApp{

public:
  
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);
	
	void setupEnv(string iEnv, Poco::Timespan iTimeSpan);
  
  void UIEvent(ofxUIEventArgs &e);

protected:
  
  dsGraphicsRef               *ref;
  dsCitizensData              *citizensData;
	string											env;
	Poco::Timespan							initialGrab;
  
  dsUIObject                  *UIObject;
  
  ofxScene										*scene;
  dsNeighborhoodLayer					*neighborhoodLayer;
  dsEventLayer								*eventLayer;
  
	vector <ofxPolygonObject *> categories;
  
  dsRealtimeLayer* realtimeLayer;
  dsHistoricalLayer* historicalLayer;
  
  // --- GUI stuff.
  
  // Default Background Color and Related Values
  int defaultR = 100;
  int defaultG = 100;
  int defaultB = 100;
  int defaultRes = 5;
  
  //Slider Values
  int sliderR = 100;
  int sliderG = 150;
  int sliderB = 200;
  int sliderRes = 5;
  float sliderScale = 100;
  
  //For collecting ofxUI2DPad position.
  float xPosition = ofGetWidth()/2;
  float yPosition = ofGetHeight()/2;
  
  //Toggles
  bool bgControl = 0;
  bool bgInvert = 0;
  bool toggleSmile = 0;

};
