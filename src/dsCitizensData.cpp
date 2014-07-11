//
//  dsCitizensData.cpp
//  Dudley
//
//  Created by Sosolimited on 7/11/14.
//
//

#include "dsCitizensData.h"

dsCitizensData::dsCitizensData(string url){
  
  jsonUrl = url;
  //  Get the data.
  bool parsingSuccessful = jsonResults.open(url);
  if (parsingSuccessful) {
    cout  << "---------------- Successfully parsed JSON" << endl;
    cout << jsonResults << endl;
//		cout << jsonResults.getRawString() << endl;
    /*
    // now write pretty print
    if(!jsonResults.save("example_output_pretty.json",true)) {
      cout << "example_output_pretty.json written unsuccessfully." << endl;
    } else {
      cout << "example_output_pretty.json written successfully." << endl;
    }
    
    // now write without pretty print
    if(!jsonResults.save("example_output_fast.json",false)) {
      cout << "example_output_pretty.json written unsuccessfully." << endl;
    } else {
      cout << "example_output_pretty.json written successfully." << endl;
    }
     */
	} else {
		cout  << "---------------- Failed to parse JSON" << endl;
	}
 
  //  Store it in an object.
  for(int i=0; i<jsonResults.size(); i++)
	{
    cout << "--- " << i << endl;
    
//    string title  = json["results"][i]["title"].asString();
//		string author = json["results"][i]["byline"].asString();
//		string date   = json["results"][i]["created_date"].asString();
//		string text   = title + " - " + author + " (" + date + ")";
//		ofDrawBitmapString(text, 20, i*24+40);
	}
  
}

dsCitizensData::~dsCitizensData(){
  
}