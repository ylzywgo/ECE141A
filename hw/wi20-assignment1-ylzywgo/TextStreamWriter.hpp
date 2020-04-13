//
//  TextStreamWriter.hpp
//  Assignment2
//
//  Created by rick gessner on 1/9/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef TextStreamWriter_hpp
#define TextStreamWriter_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>

namespace ECE141 {
  class TextStreamWriter {
  public:
    TextStreamWriter(const char* aPath, const char* aFilename);
    ~TextStreamWriter();
    int run(int aLineCount);
    
  protected:
    //STUDENT add data output member here
    std::ofstream output;
    int line;
    int number;
  };
}

#endif /* TextStreamWriter_hpp */
