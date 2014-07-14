//
//  ofxGeoJSON.cpp
//  example-loading
//
//  Created by Koichiro Mori on 2013/10/21.
//
//

#include "ofMain.h"
#include "ofxGeoJSON.h"

ofxGeoJSON::ofxGeoJSON() {
    mode = OFX_GEO_JSON_MERCATROE;
};

bool ofxGeoJSON::load(string _path) {
    
    std::string file = _path;
    
    bool parsingSuccessful = result.open(file);
    
    if (parsingSuccessful) {
        cout  << "parsingSuccessful to parse JSON" << endl;
        result.save("boston_output_pretty.json",true);
      
        // --- Create meshes to draw the map contained in the geoJSON.
        for (int i = 0; i<result["features"].size(); i++) {
            ofxJSONElement type = result["features"][i]["geometry"]["type"];
            string name = result["features"][i]["properties"]["name"].asString();
            ofxJSONElement coordinates = result["features"][i]["geometry"]["coordinates"];
//            ofLog(OF_LOG_NOTICE) << "index:" << i << result["features"][i]["properties"]["name"];
          
            if ("Polygon" == type.asString()) {
                ofMesh newMesh = ofMesh();
                newMesh.setMode(OF_PRIMITIVE_LINE_STRIP);
                for (int j = 0; j<coordinates[0].size(); j++) {
                    Coodinate coord;
                    coord.latitude = coordinates[0][j][1].asFloat();
                    coord.longtitude = coordinates[0][j][0].asFloat();
                    ofPoint pos = convertToProject(coord);
                    newMesh.addVertex(ofVec3f(pos.x, pos.y, 0));
                    newMesh.addColor(ofFloatColor(0.0, 0.0, 0.0));
                    newMesh.addIndex(j);
                }
                meshes.push_back(newMesh);
            } else if ("MultiPolygon" == type.asString()) {
                for (int j = 0; j<coordinates.size(); j++) {
                    ofMesh newMesh = ofMesh();
                    newMesh.setMode(OF_PRIMITIVE_LINE_STRIP);
                    for (int k = 0; k<coordinates[j][0].size(); k++) {
                        Coodinate coord;
                        coord.latitude = coordinates[j][0][k][1].asFloat();
                        coord.longtitude = coordinates[j][0][k][0].asFloat();
                      cout<< "latitude = "<< coord.latitude <<endl;
                      cout<< "longitude = "<< coord.longtitude <<endl;
                        ofPoint pos = convertToProject(coord);
                        newMesh.addVertex(ofVec3f(pos.x, pos.y, 0));
                        newMesh.addColor(ofFloatColor(0.0, 0.0, 0.0));
                        newMesh.addIndex(k);
                    }
                    meshes.push_back(newMesh);
                }
            }
        }
      
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
void ofxGeoJSON::setupNeighborhoodBoundingBoxes(){
  
  // For each neighborhood...
  for (int i = 0; i<result["features"].size(); i++) {
    ofxJSONElement type = result["features"][i]["geometry"]["type"];
    string name = result["features"][i]["properties"]["name"].asString();
    ofxJSONElement coordinates = result["features"][i]["geometry"]["coordinates"];
    ofLog(OF_LOG_NOTICE) << "index:" << i << result["features"][i]["properties"]["name"];
    
    if ("Polygon" == type.asString()) {
      
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
        
        // Store the coords.
        neighborhoodBoundingBox nBB;
        nBB.name = name;
        nBB.left = minX;
        nBB.right = maxX;
        nBB.bottom = minY;
        nBB.top = maxY;
        neighborhoodBoundingBoxes.push_back(nBB);
      }
      
    } else if ("MultiPolygon" == type.asString()) {
      
      // Setup starting min's & max's.
      float minX=100000000.0,
        maxX=-100000000.0,
        minY=100000000.0,
        maxY=-100000000.0;
      
      // Find the boxs' coords for each neighborhood.
      for (int j = 0; j<coordinates.size(); j++) {
        for (int k = 0; k<coordinates[j][0].size(); k++) {
          
          float curX = coordinates[j][0][k][1].asFloat();
          float curY = coordinates[j][0][k][0].asFloat();
          
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
        }
      }
      
      // Store the coords.
      neighborhoodBoundingBox nBB;
      nBB.name = name;
      nBB.left = minX;
      nBB.right = maxX;
      nBB.bottom = minY;
      nBB.top = maxY;
      neighborhoodBoundingBoxes.push_back(nBB);
    }
    
    //DEV
    cout << "****************************************** neighborhoodBoundingBoxes["<< i <<"]" << endl;
    cout << neighborhoodBoundingBoxes[i].name << endl;
    cout << neighborhoodBoundingBoxes[i].left << endl;
    cout << neighborhoodBoundingBoxes[i].right << endl;
    cout << neighborhoodBoundingBoxes[i].bottom << endl;
    cout << neighborhoodBoundingBoxes[i].top << endl;
    
  }
  
}

// For a given point, return which Boston neighborhood it is part of.
// DEV : for now, just check if point is within BOUDING BOX of a neighborhood (easier).
string ofxGeoJSON::getNeighborhoodForPoint(float testX, float testY){
  
  for (int i = 0; i<result["features"].size(); i++) {
    ofxJSONElement type = result["features"][i]["geometry"]["type"];
    string name = result["features"][i]["properties"]["name"].asString();
    ofxJSONElement coordinates = result["features"][i]["geometry"]["coordinates"];
    ofLog(OF_LOG_NOTICE) << "index:" << i << result["features"][i]["properties"]["name"];
    
    if ("Polygon" == type.asString()) {

//      cout << "coordinates[0][0][1] : " << coordinates[0][0][1].asFloat() <<endl;
//      cout << "coordinates[0][0][0] : " << coordinates[0][0][0].asFloat() <<endl;
      
      float minX=coordinates[0][0][1].asFloat(),
        maxX=0,
        minY=coordinates[0][0][0].asFloat(),
        maxY=0;
      
      for (int j = 0; j<coordinates[0].size(); j++) {

        float curX = coordinates[0][j][1].asFloat();
        float curY = coordinates[0][j][0].asFloat();
        
        // Create bounding box for cur polygon.
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
        
        // Check if point is in bounding box.
        if (testX >= minX || testX <= maxX || testY >= minY || testY <= maxY) {
          return name;
        }
      }
      
    } else if ("MultiPolygon" == type.asString()) {
      
      // Setup starting min's & max's.
      float minX=100000000.0,
        maxX=-100000000.0,
        minY=100000000.0,
        maxY=-100000000.0;

      
      for (int j = 0; j<coordinates.size(); j++) {
        
//        cout << "coordinates[j][0][k][1] : " << coordinates[0][0][0][1].asFloat() <<endl;
//        cout << "coordinates[j][0][k][0] : " << coordinates[0][0][0][0].asFloat() <<endl;
        
        for (int k = 0; k<coordinates[j][0].size(); k++) {
          
          float curX = coordinates[j][0][k][1].asFloat();
          float curY = coordinates[j][0][k][0].asFloat();
          
          // Create bounding box for cur polygon.
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
        }
      }
      
      // Check if point is in bounding box.
      if (testX >= minX && testX <= maxX && testY >= minY && testY <= maxY) {
        return name;
      }
    }
  }

  return "unknown";
  
}

bool ofxGeoJSON::isInNeighborhoodBoundingBox(float testX, float testY, string iNeighborhoodName){
  /*
  switch(iNeighborhoodName){
    case "Roslindale":
      // code
      break;
    default:
      ofLogNotice("ERROR: No such nieghborhood!");
      break;
  }
  
  
//  if (testX >= minX || testX <= maxX || testY >= minY || testY <= maxY) {
//    return true;
   
   */
  
}

void ofxGeoJSON::setMode(ofx_geo_json_mode _mode) {
    mode = _mode;
};

ofPoint ofxGeoJSON::convertToProject (Coodinate _coordinate) {
  ofPoint pos;
  switch (mode) {
    case OFX_GEO_JSON_EQUIRECTANGULAR:
      pos = equirectangular(_coordinate);
      break;
    case OFX_GEO_JSON_MERCATROE:
      pos = mercator(_coordinate);
      break;
    case OFX_GEO_JSON_STEREOGRAPHIC:
    case OFX_GEO_JSON_AZIMUTHAL_EQUALAREA:
      pos = azimuthal(_coordinate);
    default:
      break;
  }
  return pos;
}

ofPoint ofxGeoJSON::mercator(Coodinate _coordinate) {
    ofPoint psition;
    psition.x = (_coordinate.longtitude / 180.0) * scale + translateX;
    psition.y = /*_coordinate.latitude > 85 ? 1 : _coordinate.latitude < -85 ? -1 //<- we should consider about polar regions converting..
    : */ ( log(tan(PI / 4.0 + pvRadians(_coordinate.latitude) / 2.0)) / PI ) * scale - translateY;
    return psition;
};

ofPoint ofxGeoJSON::equirectangular(Coodinate _coordinate) {
    ofPoint position;
    position.x = _coordinate.longtitude / 360 * scale + translateX;
    position.y = _coordinate.latitude / 360  * scale - translateY;
    return position;
};

ofPoint ofxGeoJSON::azimuthal(Coodinate _coordinate) {
    ofPoint position;
    float cy0 = cos(pvRadians(0));
    float sy0 = sin(pvRadians(0));
    float radian = PI / 180.0;
    float x1 = _coordinate.longtitude * radian - pvRadians(0);
    float y1 = _coordinate.latitude * radian;
    float cx1 = cos(x1);
    float sx1 = sin(x1);
    float cy1 = cos(y1);
    float sy1 = sin(y1);
    float cc = sy0 * sy1 + cy0 * cy1 * cx1;
    float k;
    switch(mode) {
        case OFX_GEO_JSON_STEREOGRAPHIC:
            k = 1 / (1 + cc);
            break;
        case OFX_GEO_JSON_AZIMUTHAL_EQUALAREA:
            k = sqrt(2 / (1 + cc));
            break;
        default:
            break;
    }
    position.x = k * cy1 * sx1 * scale + translateX;
    position.y = -1 * k * (sy0 * cy1 * cx1 - cy0 * sy1) * scale + translateY;
    return position;
}

float ofxGeoJSON::pvRadians(float _degrees) {
    float radians = PI / 180.0;
    return radians * _degrees;
};

void ofxGeoJSON::setScale(float _scale) {
    scale = _scale;
};

void ofxGeoJSON::setTranslate(float _transelateX, float _transelateY) {
    translateX = _transelateX;
    translateY = _transelateY;
};

void ofxGeoJSON::draw() {
    for (int i = 0; i < meshes.size(); i++) {
        meshes[i].draw(OF_MESH_FILL);
    }
};

ofMesh* ofxGeoJSON::getMesh() {
    return &meshes[0];
};

