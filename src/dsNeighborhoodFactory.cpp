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
    
    // --- Setup the bounding boxes.
    setupNeighborhoodBoundingBoxes();
    
    // --- Return true if loading was a success.
    return true;
  } else {
    ofLog(OF_LOG_WARNING, "Failed to parse JSON");
    return false;
  }
  
  return false;
};

// Calculate the bouding boxes for each neighborhood.
void dsNeighborhoodFactory::setupNeighborhoodBoundingBoxes(){
  
  // For each neighborhood...
  for (int i = 0; i<result["features"].size(); i++) {
    ofxJSONElement type = result["features"][i]["geometry"]["type"];
    string name = result["features"][i]["properties"]["name"].asString();
    ofxJSONElement coordinates = result["features"][i]["geometry"]["coordinates"];
    ofLog(OF_LOG_NOTICE) << "index:" << i << result["features"][i]["properties"]["name"];
    
    if ("Polygon" == type.asString()) {
      
      neighborhoodBoundingBox nBB;
      nBB.name = name;
      
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
        nBB.vertsX.push_back(curX);
        nBB.vertsY.push_back(curY);
        
      }
      
      // Store the box coords.
      nBB.left = minX;
      nBB.right = maxX;
      nBB.bottom = minY;
      nBB.top = maxY;
      nBB.centroid = ofVec3f((minX+maxX)/2.0, (minY+maxY)/2.0, 0);
      neighborhoodBoundingBoxes.push_back(nBB);
      
    } else if ("MultiPolygon" == type.asString()) {
      
      neighborhoodBoundingBox nBB;
      nBB.name = name;
      
      // Setup starting min's & max's.
      float minX=100000000.0,
      maxX=-100000000.0,
      minY=100000000.0,
      maxY=-100000000.0;
      
      // Find the boxs' coords for each neighborhood.
      for (int j = 0; j<coordinates.size(); j++) {
        for (int k = 0; k<coordinates[j][0].size(); k++) {
          
          cout << "* * * * * * curX = " << coordinates[j][0][k][1] << endl;
          cout << "* * * curY = " << coordinates[j][0][k][0] << endl;

//          string s = std::stof(coordinates[j][0][k][1]);
//          cout<< s << endl;

          float curX = coordinates[j][0][k][1].asFloat();
          float curY = coordinates[j][0][k][0].asFloat();

          cout << "curX = " << curX << endl;
          cout << "curY = " << curY << endl;
          
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
          nBB.vertsX.push_back(curX);
          nBB.vertsY.push_back(curY);
        }
      }
      
      // Store the box coords.
      nBB.left = minX;
      nBB.right = maxX;
      nBB.bottom = minY;
      nBB.top = maxY;
      nBB.centroid = ofVec3f((minX+maxX)/2.0, (minY+maxY)/2.0, 0);      
      neighborhoodBoundingBoxes.push_back(nBB);
    }
    
    //DEV
//    cout << "****************************************** neighborhoodBoundingBoxes["<< i <<"]" << endl;
//    cout << neighborhoodBoundingBoxes[i].name << endl;
//    cout << neighborhoodBoundingBoxes[i].left << endl;
//    cout << neighborhoodBoundingBoxes[i].right << endl;
//    cout << neighborhoodBoundingBoxes[i].bottom << endl;
//    cout << neighborhoodBoundingBoxes[i].top << endl;
//    cout << neighborhoodBoundingBoxes[i].vertsX.size() << endl;
//    cout << neighborhoodBoundingBoxes[i].vertsY.size() << endl;
    
  }
  
}

// For a given point, return which Boston neighborhood it is part of.
// DEV : for now, just check if point is within BOUDING BOX of a neighborhood (easier).
string dsNeighborhoodFactory::getNeighborhoodForPoint(float testX, float testY){
  
  for (int i = 0; i<neighborhoodBoundingBoxes.size(); i++) {
    
    // If the point is in the neighborhood's bounding box, perform the point-in-polygon algorith.
    if (testX >= neighborhoodBoundingBoxes[i].left &&
        testX <= neighborhoodBoundingBoxes[i].right &&
        testY >= neighborhoodBoundingBoxes[i].bottom &&
        testY <= neighborhoodBoundingBoxes[i].top) {
      
      bool isInNeighborhood = isPointInPolygon(neighborhoodBoundingBoxes[i].vertsX.size(), neighborhoodBoundingBoxes[i].vertsX, neighborhoodBoundingBoxes[i].vertsY, testX, testY);
//      cout << "% % % % % % % isInNeighborhood = " << isInNeighborhood <<endl;

      if (isInNeighborhood){
        return neighborhoodBoundingBoxes[i].name;
      }

    }
  }
  return "unknown";
  
}

ofVec3f dsNeighborhoodFactory::getNeighborhoodCentroid(int index) {
  
  if (index >= 0 && index < neighborhoodBoundingBoxes.size()) {

    ofLogNotice( "neighborhood X value = " + ofToString(neighborhoodBoundingBoxes[index].centroid[0]));
    
    return neighborhoodBoundingBoxes[index].centroid;

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

