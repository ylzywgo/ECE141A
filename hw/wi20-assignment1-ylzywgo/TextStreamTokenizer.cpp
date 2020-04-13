//
//  TextStreamTokenizer.cpp
//  Assignment2
//
//  Created by rick gessner on 1/9/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "TextStreamTokenizer.hpp"

namespace ECE141 {
  
  TextStreamTokenizer::TextStreamTokenizer(const char* aPath, const char* aFilename) {
    char thePath[512];
    sprintf(thePath, "%s/%s", aPath, aFilename);
    //STUDENT: open your input stream (from thePath) here...
    input.open (thePath, std::ifstream::in);
  }

  TextStreamTokenizer::~TextStreamTokenizer(){
    input.close();
  }
  
  int TextStreamTokenizer::run(std::ostream &output) {
    
    //STUDENT: implement this method. read numbers from each line, sum them, send result to output...
    std::string line;
    while (std::getline(input, line))
    {
        int sum = 0;
        std::string word = ""; 
        for (auto x : line) 
        { 
            if (x == ' ') 
            { 
                sum += std::stoi(word);
                word = ""; 
            } 
            else
            { 
                word = word + x; 
            } 
        }  
        if (word != ""){
          sum += std::stoi(word);
        }
        output << sum << std::endl;
        // process pair (a,b)
    }
    return 0;
  }
  
}
