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
	
  vector <string> categories;
  
  categories.push_back("Sidewalk Patch");
  categories.push_back("Graffiti");
  categories.push_back("Pothole");
  categories.push_back("Streetlight");
  categories.push_back("Damaged Sign");
  categories.push_back("Other");
  
  //for (auto c : categories)
    colors.push_back(new dsGraphicsRefColor("Sidewalk Patch", 43, 76, 243 ));
		colors.push_back(new dsGraphicsRefColor("Graffiti", 227, 162, 85 ));
		colors.push_back(new dsGraphicsRefColor("Pothole", 58, 175, 87 ));
		colors.push_back(new dsGraphicsRefColor("Streetlight", 222, 121, 92 ));
		colors.push_back(new dsGraphicsRefColor("Damaged Sign", 204, 112, 170 ));
		colors.push_back(new dsGraphicsRefColor("Other", 190, 190, 230 ));
	
  
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