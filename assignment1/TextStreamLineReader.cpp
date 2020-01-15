//
//  TextStreamLineReader.cpp
//  Assignment2
//
//  Created by rick gessner on 1/9/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "TextStreamLineReader.hpp"
#include <string>

namespace ECE141 {
  
  TextStreamLineReader::TextStreamLineReader(const char* aPath, const char* aFilename) {
    char thePath[512];
    sprintf(thePath, "%s/%s", aPath, aFilename);
    //STUDENT construct your input stream here...
    input.open (thePath, std::ifstream::in);
  }
  
  int TextStreamLineReader::run(std::ofstream &output) {
    
    //STUDENT: read each line in your input stream, parse the int's, write result to anOutput...
    // int theFirst, theSecond; //for reading integers...
  
    // std::string theLine;
    // while (std::getline(input, theLine)) {
      // //add code to parse the two integers from within *theLine*...
      // std::string word = ""; 
      // for (auto x : theLine) 
      // { 
      //     if (x == ' ') 
      //     { 
      //         theFirst = std::stoi(word);
      //         word = ""; 
      //     } 
      //     else
      //     { 
      //         word = word + x; 
      //     } 
      // }  
      // if (word != ""){
      //   theSecond = std::stoi(word);
      // }
      // // process pair (a,b)
      int first, second;
      while (input >> first >> second) {
          output << first << "+" << second << "=" << first+second << std::endl;
      } 
    // }    
    return 0;
  }
}
