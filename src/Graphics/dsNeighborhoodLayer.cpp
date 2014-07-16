//
//  dsNeighborhoodLayer.cpp
//  Dudley
//
//  Created by Sosolimited on 7/16/14.
//
//

#include "dsNeighborhoodLayer.h"

dsNeighborhoodLayer::dsNeighborhoodLayer() {}

dsNeighborhoodLayer::~dsNeighborhoodLayer() {}

void dsNeighborhoodLayer::buildNeighborhoods(dsCitizensData *data)
{
  
  float mapScale = 45.0;
  
  for (int i = 0 ; i < data->getNumNeighborhoods() ; i ++){
    
    vector<float> vX = data->getGeoJson().getNeighborhood(i).getVertsX();
    vector<float> vY = data->getGeoJson().getNeighborhood(i).getVertsY();
    
    
    ofxPolygonObject *poly = new ofxPolygonObject(vX.size());
    poly->setColor(0, 200, 200);
    poly->setDrawMode(OF_OUTLINE);
    //poly->setTrans(2000.0*(citizensData->getGeoJson().getNeighborhood(i).getCentroid()  - citizensData->getCentroid()));
    
    for (int i = 0 ; i < vX.size() ; i++) {
      
      ofVec3f xyz(vX[i], vY[i], 0);
      ofVec3f mapped = xyz.mapped(-mapScale*data->getCentroid(), ofVec3f(mapScale,0,0) ,ofVec3f(0,mapScale,0), ofVec3f(0,0,mapScale));
      
      poly->setVertexPos(i, mapScale*mapped);
    }
    //poly->addChild(new ofxCircleObject(20,3));
    neighborhoods.push_back(poly);
    addChild(poly);
    
    ofLogNotice(ofToString(poly->getVertexPos(5)));
    
  }
  
}