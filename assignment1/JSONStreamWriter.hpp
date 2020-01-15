//
//  JSONStreamWriter.hpp
//  Assignment2
//
//  Created by rick gessner on 1/9/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef JSONStreamWriter_hpp
#define JSONStreamWriter_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>

namespace ECE141 {
  class JSONStreamWriter {
  public:
        JSONStreamWriter(const char* aPath, const char* aFilename);
    int run();
    
  protected:
    //STUDNET: declare an output stream here...
    std::ofstream output;
  };
  
}


#endif /* JSONStreamWriter_hpp */
