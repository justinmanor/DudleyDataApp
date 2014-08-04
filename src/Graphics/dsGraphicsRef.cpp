//
//  dsGraphicsRef.cpp
//  Dudley
//
//  Created by Sosolimited on 7/16/14.
//
//

#include "dsGraphicsRef.h"

//class dsGraphicsRefColor
dsGraphicsRefColor::dsGraphicsRefColor(string iName, float iR, float iG, float iB, float iA)
{
	name = iName;
	color.set(iR, iG, iB, iA);
}

dsGraphicsRefColor::~dsGraphicsRefColor(){}


//class scGraphicsRef
dsGraphicsRef* dsGraphicsRef::graphicsRef = NULL;	//single instance of ref object
vector<dsGraphicsRefColor *> dsGraphicsRef::colors;


//private constructor enforces single instance of ref object
dsGraphicsRef::dsGraphicsRef()
{
	
  // Create colors for event categories.
  vector <string> categories;
  categories.push_back("Sidewalk Patch");
  categories.push_back("Graffiti");
  categories.push_back("Pothole");
  categories.push_back("Streetlight");
  categories.push_back("Damaged Sign");
  categories.push_back("Other");
  colors.push_back(new dsGraphicsRefColor("Sidewalk Patch", 43, 76, 243 ));   // blue
  colors.push_back(new dsGraphicsRefColor("Graffiti", 255, 127, 14 ));        // orange
  colors.push_back(new dsGraphicsRefColor("Pothole", 58, 175, 87 ));          // green
  colors.push_back(new dsGraphicsRefColor("Streetlight", 214, 39, 40 ));      // red
  colors.push_back(new dsGraphicsRefColor("Damaged Sign", 255, 152, 150 ));   // pink
  colors.push_back(new dsGraphicsRefColor("Other", 255, 255, 0 ));            // yellow
  //  colors.push_back(new dsGraphicsRefColor("Other", 148, 103, 189 ));          // purple
	
  // Create other dev colors.
  colors.push_back(new dsGraphicsRefColor("lastFewEvents", 255, 0, 255 ));    //magenta
}

dsGraphicsRef::~dsGraphicsRef(){}

//call this to get access to the single instance
dsGraphicsRef* dsGraphicsRef::instance()
{
	if(!graphicsRef){
		graphicsRef = new dsGraphicsRef();
	}
  
	return graphicsRef;
}

//ofVec4f scGraphicsRef::getColorByName(string iName)
ofColor dsGraphicsRef::getColorByName(string iName)
{
	
	for(int i=0; i < colors.size(); i++){
		if(colors[i]->name == iName)
			return colors[i]->color;
	}
	
	//return ofVec4f(255,255,255,255);
  return ofColor(255,255,255);
}

void dsGraphicsRef::setDrawingCentroid (ofVec3f iDrawingCentroid) {
	
	drawingCentroid = iDrawingCentroid;
	
}

ofVec3f dsGraphicsRef::getDrawingCentroid() {
	
	return drawingCentroid;

};