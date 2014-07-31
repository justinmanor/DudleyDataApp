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
  
  //dev_jn

};
