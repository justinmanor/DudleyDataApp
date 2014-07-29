#pragma once

#include "ofMain.h"
#include "dsCitizensData.h"
#include "ofxScene.h"
#include "ofxCircleObject.h"
#include "dsGraphicsRef.h"
#include "dsNeighborhoodLayer.h"
#include "dsEventLayer.h"
#include "dsRealtimeLayer.h"

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

  protected:
  
  dsGraphicsRef               *ref;
  dsCitizensData              *citizensData;
	string											env;
	Poco::Timespan							initialGrab;
  
  // For drawing geoJSON map.

  ofEasyCam										cam;
  ofxScene										*scene;
  dsNeighborhoodLayer					*neighborhoodLayer;
  dsEventLayer								*eventLayer;
  
	vector <ofxPolygonObject *> categories;

  //DEV
  dsRealtimeLayer* realtimeLayer;
};
