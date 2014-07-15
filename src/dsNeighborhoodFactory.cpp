//
//  dsNeighborhoodFactory.cpp
//  Dudley
//
//  Created by Sosolimited on 7/15/14.
//
//

#include "dsNeighborhoodFactory.h"


dsNeighborhoodFactory::dsNeighborhoodFactory(){
  
}

dsNeighborhoodFactory::~dsNeighborhoodFactory(){}

bool dsNeighborhoodFactory::load(string _path) {
  
  std::string file = _path;
  
  bool parsingSuccessful = result.open(file);
  
  if (parsingSuccessful) {
    cout  << "parsingSuccessful to parse JSON" << endl;
    result.save("boston_output_pretty.json",true);
    
    // --- Setup the neighborhoods & their bounding boxes.
    setupNeighborhoods();
    
    // --- Return true if loading was a success.
    return true;
  } else {
    ofLog(OF_LOG_WARNING, "Failed to parse JSON");
    return false;
  }
  
  return false;
};

// Calculate the bounding boxes for each neighborhood.
void dsNeighborhoodFactory::setupNeighborhoods(){
  
  // For each neighborhood...
  for (int i = 0; i<result["features"].size(); i++) {
    ofxJSONElement type = result["features"][i]["geometry"]["type"];
    string name = result["features"][i]["properties"]["name"].asString();
    ofxJSONElement coordinates = result["features"][i]["geometry"]["coordinates"];
    ofLog(OF_LOG_NOTICE) << "index:" << i << result["features"][i]["properties"]["name"];
    
    if ("Polygon" == type.asString()) {
      
      dsNeighborhood n;
      n.setName(name);
      
      // Setup starting min's & max's.
      float minX=100000000.0,
      maxX=-100000000.0,
      minY=100000000.0,
      maxY=-100000000.0;
      
      for (int j = 0; j<coordinates[0].size(); j++) {
        
        float curX = coordinates[0][j][1].asFloat();
        float curY = coordinates[0][j][0].asFloat();
        
        if (curX < minX){
          minX = curX;
        }
        if (curX > maxX){
          maxX = curX;
        }
        if (curY < minY){
          minY = curY;
        }
        if (curY > maxY){
          maxY = curY;
        }
        
        // Also, store all x & y's seperately in the neighborhood object for point-in-poly algo later.
        n.addVertX(curX);
        n.addVertY(curY);
        
      }
      
      // Store the box coords.
      n.addBounds(minX, maxX, minY, maxY);
//      n.left = minX;
//      n.right = maxX;
//      n.bottom = minY;
//      n.top = maxY;
      neighborhoods.push_back(n);
      
    } else if ("MultiPolygon" == type.asString()) {
      
      dsNeighborhood n;
      n.setName(name);
      
      // Setup starting min's & max's.
      float minX=100000000.0,
      maxX=-100000000.0,
      minY=100000000.0,
      maxY=-100000000.0;
      
      // Find the boxs' coords for each neighborhood.
      for (int j = 0; j<coordinates.size(); j++) {
        for (int k = 0; k<coordinates[j][0].size(); k++) {
          
          //DEV
//          cout << "* * * * * * curX = " << coordinates[j][0][k][1] << endl;
//          cout << "* * * curY = " << coordinates[j][0][k][0] << endl;

          //DEV
//          string s = std::stof(coordinates[j][0][k][1]);
//          cout<< s << endl;

          float curX = coordinates[j][0][k][1].asFloat();
          float curY = coordinates[j][0][k][0].asFloat();

          //DEV
//          cout << "curX = " << curX << endl;
//          cout << "curY = " << curY << endl;
          
          if (curX < minX){
            minX = curX;
          }
          if (curX > maxX){
            maxX = curX;
          }
          if (curY < minY){
            minY = curY;
          }
          if (curY > maxY){
            maxY = curY;
          }
          
          // Also, store all x & y's seperately in the neighborhood object for point-in-poly algo later.
          n.addVertX(curX);
          n.addVertY(curY);
        }
      }
      
      // Store the box coords.
      n.addBounds(minX, maxX, minY, maxY);
//      n.left = minX;
//      n.right = maxX;
//      n.bottom = minY;
//      n.top = maxY;
      neighborhoods.push_back(n);
    }
    
    //DEV
    cout << "****************************************** neighborhoods["<< i <<"]" << endl;
    cout << "name : " << neighborhoods[i].getName() << endl;
    cout << "leftBound : "  << neighborhoods[i].getBound("left") << endl;
    cout << "rightBound : "  << neighborhoods[i].getBound("right") << endl;
    cout << "bottomBound : "  << neighborhoods[i].getBound("bottom") << endl;
    cout << "topBound : "  << neighborhoods[i].getBound("top") << endl;
    cout << "vertsX.size() : "  << neighborhoods[i].getVertsX().size() << endl;
    cout << "vertsY.size() : "  << neighborhoods[i].getVertsY().size() << endl;
    cout << "centroid.x : "  << neighborhoods[i].getCentroid().x << endl;
    cout << "centroid.y : "  << neighborhoods[i].getCentroid().y << endl;
    
  }
  
}

// For a given point, return which Boston neighborhood it is part of.
// DEV : for now, just check if point is within BOUDING BOX of a neighborhood (easier).
string dsNeighborhoodFactory::getNeighborhoodForPoint(float testX, float testY){
  
  for (int i = 0; i<neighborhoods.size(); i++) {
    
    // If the point is in the neighborhood's bounding box, perform the point-in-polygon algorith.
    if (testX >= neighborhoods[i].getBound("left") &&
        testX <= neighborhoods[i].getBound("right") &&
        testY >= neighborhoods[i].getBound("bottom") &&
        testY <= neighborhoods[i].getBound("top")) {
      
      bool isInNeighborhood = isPointInPolygon(neighborhoods[i].getVertsX().size(), neighborhoods[i].getVertsX(), neighborhoods[i].getVertsY(), testX, testY);
//      cout << "% % % % % % % isInNeighborhood = " << isInNeighborhood <<endl;

      if (isInNeighborhood){
        return neighborhoods[i].getName();
      }

    }
  }
  return "unknown";
  
}

ofVec3f dsNeighborhoodFactory::getNeighborhoodCentroid(int index) {
  
  if (index >= 0 && index < neighborhoods.size()) {

    ofLogNotice( "neighborhood X value = " + ofToString(neighborhoods[index].getCentroid()[0]));
    
    return neighborhoods[index].getCentroid();

  } else
    
    return ofVec3f(0,0,0);

}

// Point-in-polygon algorithm.
// http://stackoverflow.com/questions/217578/point-in-polygon-aka-hit-test/
// http://www.codeproject.com/Tips/84226/Is-a-Point-inside-a-Polygon
bool dsNeighborhoodFactory::isPointInPolygon(int nvert, vector<float> vertx, vector<float> verty, float testx, float testy)
{
  int i, j;
  bool c = false;
  
  for (i = 0, j = nvert-1; i < nvert; j = i++) {
    if ( ((verty[i]>testy) != (verty[j]>testy)) &&
        (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
      c = !c;
  }
  return c;
}

