//
//  Writeable.hpp
//  FinalGame
//
//  Created by rick gessner on 3/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#ifndef Writeable_h
#define Writeable_h

#include <sstream>      
#include <fstream>

namespace ECE141 {

  class Writable {
  public:
        
    bool save(std::stringstream &aStream) {      
      std::ofstream theOutput("gameoutput.txt");
      theOutput << aStream.str();
      theOutput.flush();
      return true;
    }
    
  };

}
#endif /* Writeable_h */
