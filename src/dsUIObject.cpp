//
//  dsUIObject.cpp
//  Dudley
//
//  Created by Sosolimited on 7/30/14.
//
//

#include "dsUIObject.h"
#include <iostream>

dsUIObject::dsUIObject()
{
  bool isVisible = true;
  
  // Initialize "hack" variables for window bar and screen width corrections in Soso universe
  windowBarHack = 0;
  screenWidthHack = 0;
  
  // Reassign mouse callback to flip y-coords
  ofAddListener(ofEvents().mouseReleased, this, &dsUIObject::onMouseReleased);
  ofAddListener(ofEvents().mousePressed, this, &dsUIObject::onMousePressed);
  ofAddListener(ofEvents().mouseMoved, this, &dsUIObject::onMouseMoved);
  ofAddListener(ofEvents().mouseDragged, this, &dsUIObject::onMouseDragged);
}

dsUIObject::~dsUIObject()
{
  delete UI;
  delete demoToggleBG;
  delete demoSliderR;
  delete demoSliderG;
  delete demoSliderB;
  delete demoButtonInv;
  delete demoLabel;
  delete demoPos;
  delete demoCircleRes;
  delete demoCircleScale;
  delete demoToggle1;
  
}

void dsUIObject::setup()
{
  // Define UI Canvas Size Parameters
  int canvas_width = 280;
  int canvas_height = 600;
  
  //Define UI Object Parameters
  int UIButtonWidth = 200;
  int UIButtonHeight = 20;
  int UIRadioWidth = 20;
  
  // Define an arbitrary string vector for radio buttons
  vector<string> radioNames;
  radioNames.push_back("radio_1");
  radioNames.push_back("radio_2");
  radioNames.push_back("radio_3");
  
  // Build the UI Canvas
  UI = new ofxUICanvas(0, 0, canvas_width, canvas_height);
  // Use zeros for translation here and setTrans on dsUIObject in App.
  
  // Disable app event callbacks because we do it from within render tree (ofxObject-style)
  UI->disableAppEventCallbacks();
  
  // Disable mouse event callbacks because we have to flip the y-coords.
  UI->disableMouseEventCallbacks();
  
  // Add a label to the top of the canvas
  UI->addLabel("Dudley Data App", OFX_UI_FONT_MEDIUM);
  
  UI->addSpacer();
  
  // Build an updating label
  demoLabel = NULL;
  demoLabel = new ofxUILabel("updating label", OFX_UI_FONT_MEDIUM);
  UI->addWidgetDown(demoLabel);
  
}

void dsUIObject::idle(float iTime)
{
  
}

void dsUIObject::update()
{
  
  // Do something to the updating label (so it updates)
  float t = ofGetElapsedTimef();
  if (demoLabel)
    demoLabel->setLabel("updating label: "+ ofToString(t, 2));
  
  // Update the UI (ofxUICanvas)
  UI->update();
  
}

void dsUIObject::render()
{
  if (isVisible){
    ofPushMatrix();
    
    // Flip y-coords to draw correctly in Soso universe.
    ofScale(1, -1, 1);
    
    UI->draw();
    
    ofPopMatrix();
  }
}

void dsUIObject::exit()
{
  UI->exit();
}

// Mouse callbacks that flip the y to bring interactions into soso universe.

void dsUIObject::onMouseReleased(ofMouseEventArgs & iArgs)
{
  windowBarHack = (0 - ofGetHeight() )/2.0;
  screenWidthHack = (0 - ofGetWidth() )/2.0;
  
  UI->mouseReleased(iArgs.x - getTrans().x + screenWidthHack, iArgs.y+getTrans().y + windowBarHack, iArgs.button);
  
}

void dsUIObject::onMousePressed(ofMouseEventArgs & iArgs)
{
  windowBarHack = (0 - ofGetHeight() )/2.0;
  screenWidthHack = (0 - ofGetWidth() )/2.0;
  
  UI->mousePressed(iArgs.x - getTrans().x + screenWidthHack, iArgs.y+getTrans().y + windowBarHack, iArgs.button);
}

void dsUIObject::onMouseMoved(ofMouseEventArgs & iArgs)
{
  windowBarHack = (0 - ofGetHeight() )/2.0;
  screenWidthHack = (0 - ofGetWidth() )/2.0;
  
  UI->mouseMoved(iArgs.x - getTrans().x + screenWidthHack, iArgs.y+getTrans().y + windowBarHack);
}

void dsUIObject::onMouseDragged(ofMouseEventArgs & iArgs)
{
  windowBarHack = (0 - ofGetHeight() )/2.0;
  screenWidthHack = (0 - ofGetWidth() )/2.0;
  
  UI->mouseDragged(iArgs.x - getTrans().x + screenWidthHack, iArgs.y+getTrans().y + windowBarHack, iArgs.button);
}