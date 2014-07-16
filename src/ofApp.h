#pragma once

#include "ofMain.h"
#include "dsCitizensData.h"
#include "ofxScene.h"
#include "ofxCircleObject.h"
#include "dsGraphicsRef.h"
#include "dsNeighborhoodLayer.h"

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

  protected:
  
  dsGraphicsRef               *ref;
  dsCitizensData              *citizensData;
  
  // For drawing geoJSON map.
  ofEasyCam                   cam;
  ofxScene                    *scene;
  ofxObject                   *realtimeLayer;
  ofxObject                   *historicLayer;
  dsNeighborhoodLayer         *neighborhoodLayer;
  vector <ofxCircleObject *>  events;

};
