//
//  dsUIObject.cpp
//  Dudley
//
//  Created by Sosolimited on 7/30/14.
//
//

#include "dsUIObject.h"
#include <iostream>

dsUIObject::dsUIObject(dsCitizensData* iData)
{
  data = iData;
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
  UI = new ofxUICanvas(0, 0, canvas_width, canvas_height);
  UI->setTheme(OFX_UI_THEME_MACOSX);    //OFX_UI_THEME_GRAYDAY
  
  // Disable app event callbacks because we do it from within render tree (ofxObject-style)
  UI->disableAppEventCallbacks();
  
  // Disable mouse event callbacks because we have to flip the y-coords.
  UI->disableMouseEventCallbacks();
  
  // ------------------------------------------------------------
  // UI items.
  // ------------------------------------------------------------
  
  // Canvas title.
  UI->addLabel("Dudley Data App", OFX_UI_FONT_MEDIUM);
  
  UI->addSpacer();
  
  // Updating FPS label.
  demoLabel = NULL;
  demoLabel = new ofxUILabel("FPS: "+ ofToString(ofGetFrameRate(), 2), OFX_UI_FONT_SMALL);
  UI->addWidgetDown(demoLabel);
  //
  UI->addSpacer();
  //
  numEventsLabel = NULL;
  numEventsLabel = new ofxUILabel("# events: ", OFX_UI_FONT_SMALL);
  UI->addWidgetDown(numEventsLabel);
  timeToNextPullLabel = NULL;
  timeToNextPullLabel = new ofxUILabel("next poll in: ", OFX_UI_FONT_SMALL);
  UI->addWidgetDown(timeToNextPullLabel);
  numNewEventsLabel = NULL;
  numNewEventsLabel = new ofxUILabel("# new events: ", OFX_UI_FONT_SMALL);
  UI->addWidgetDown(numNewEventsLabel);
  //
  UI->addSpacer();
  //
  UI->addLabel("Neighborhood Stats", OFX_UI_FONT_MEDIUM);
  //
  UI->addSpacer();
  //
  UI->addLabel("Category Stats", OFX_UI_FONT_MEDIUM);

}

void dsUIObject::idle(float iTime)
{
  
}

void dsUIObject::update()
{
  
  // Do something to the updating label (so it updates)
  if (demoLabel){ demoLabel->setLabel("FPS: "+ ofToString(ofGetFrameRate(), 2)); }
  if (numEventsLabel){ numEventsLabel->setLabel("# events: "+ ofToString(data->getNumEvents())); }
  if (timeToNextPullLabel){ timeToNextPullLabel->setLabel("next poll in: "+ ofToString(data->getTimeToNextPull())); }
  if (numNewEventsLabel){ numNewEventsLabel->setLabel("# new events: "+ ofToString(data->getNumNewEvents())); }
  
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