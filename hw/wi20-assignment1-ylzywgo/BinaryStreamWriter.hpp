//
//  BinaryStreamWriter.hpp
//  Assignment2
//
//  Created by rick gessner on 1/9/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef BinaryStreamWriter_hpp
#define BinaryStreamWriter_hpp

#include <stdio.h>
#include <fstream>

namespace ECE141 {
  class BinaryStreamWriter {
  public:
        BinaryStreamWriter(const char* aPath, const char* aFilename);
        ~BinaryStreamWriter();
    int run(int aBlockCount, size_t aBlockSize=32);
    
  protected:
    //STUDENT: declare your binary stream here...
    std::ofstream output;
  };
}

#endif /* BinaryStreamWriter_hpp */
