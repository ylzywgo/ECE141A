//
//  TextStreamTokenizer.hpp
//  Assignment2
//
//  Created by rick gessner on 1/9/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef TextStreamTokenizer_hpp
#define TextStreamTokenizer_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>

namespace ECE141 {
  class TextStreamTokenizer {
  public:
        TextStreamTokenizer(const char* aPath, const char* aFilename);
    int run(std::ostream &output);
    
  protected:
    //STUDENT: declare an input stream here...
    std::ifstream input;
    
  };
}

#endif /* TextStreamTokenizer_hpp */
