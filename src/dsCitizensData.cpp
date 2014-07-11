//
//  dsCitizensData.cpp
//  Dudley
//
//  Created by Sosolimited on 7/11/14.
//
//

#include "dsCitizensData.h"

dsCitizensData::dsCitizensData(string url){
  
  // Now parse the JSON
	  bool parsingSuccessful = jsonReader.open(url);
	
  if (parsingSuccessful) {
		cout << jsonReader.getRawString() << endl;
    
    // now write pretty print
    if(!jsonReader.save("example_output_pretty.json",true)) {
      cout << "example_output_pretty.json written unsuccessfully." << endl;
    } else {
      cout << "example_output_pretty.json written successfully." << endl;
    }
    
    // now write without pretty print
    if(!jsonReader.save("example_output_fast.json",false)) {
      cout << "example_output_pretty.json written unsuccessfully." << endl;
    } else {
      cout << "example_output_pretty.json written successfully." << endl;
    }
		
	} else {
		cout  << "Failed to parse JSON" << endl;
	}
  
}

dsCitizensData::~dsCitizensData(){
  
}