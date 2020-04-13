//
//  JSONStreamWriter.cpp
//  Assignment2
//
//  Created by rick gessner on 1/9/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "JSONStreamWriter.hpp"
#include "Student.hpp"

namespace ECE141 {
    
  JSONStreamWriter::JSONStreamWriter(const char* aPath, const char* aFilename) {
    char thePath[512];
    sprintf(thePath, "%s/%s", aPath, aFilename);
    //STUDENT: open your output stream here...
    output.open(thePath, std::ofstream::out | std::ofstream::app);
  }

  JSONStreamWriter::~JSONStreamWriter(){
    output.close();
  }
  
  int JSONStreamWriter::run() {
    
    ECE141::Student theStudent;
    
    //STUDENT: Initialize the fields of your Student object here...
    theStudent.setName("Yawen Zhao");
    theStudent.setStudentId("A53280596");
    theStudent.setEmail("yaz005@ucsd.edu");
    theStudent.setOs("mac");
    theStudent.setCourse("ECE141A");

    //STUDENT: finish implementation in the Student class (see operator<<)
    output << theStudent;
    return 0;
  }
}
