//
//  dsGraphicsRef.h
//  Dudley
//
//  Created by Sosolimited on 7/16/14.
//
//

#pragma once

#include "ofxObject.h"

class dsGraphicsRefColor
{
public:
	dsGraphicsRefColor(string iName, float iR, float iG, float iB, float iA=255);
	~dsGraphicsRefColor();
  
public:
  ofColor                             color;
	string                              name;
};

class dsGraphicsRef {

protected:
  dsGraphicsRef();
  ~dsGraphicsRef();
  
public:
  static dsGraphicsRef*               instance();
  ofColor                             getColorByName(string iName);
  
private:
	static dsGraphicsRef                *graphicsRef;
	static vector<dsGraphicsRefColor *> colors;

  
};