//
//  TextStreamWriter.cpp
//  Assignment2
//
//  Created by rick gessner on 1/9/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "TextStreamWriter.hpp"

namespace ECE141 {

  TextStreamWriter::TextStreamWriter(const char* aPath, const char* aFilename) {
    char thePath[512];
    sprintf(thePath, "%s/%s", aPath, aFilename);  //this is the full path+filename
    output.open(thePath, std::ofstream::out | std::ofstream::app);
    //STUDENT: add logic to open your output stream here...
    this->line = 0;
    this->number = 0;
  }
  
  int TextStreamWriter::run(int aLineCount) {
    
    //STUDENT: implement your output logic here... 2 ints (separated by a space) per line...
    output << aLineCount;    
    this->number++;
    if (this->number % 2 == 0){
      output << std::endl ;
      this->line++;
    }
    else{
      output << " ";
    }
    return this->line; //return the number of lines written...
  }
}
