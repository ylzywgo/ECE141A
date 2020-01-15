//
//  Student.cpp
//  Assignment2
//
//  Created by rick gessner on 1/9/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "Student.hpp"

namespace ECE141 {
  
  Student::Student() {}
  
  Student& Student::setName(const char* aName) {
    //STUDENT: set the name field here...
    strcpy(name, aName);
    return *this;
  }
  
  Student& Student::setEmail(const char* anEmail) {
    //STUDENT: set the email field here...
    strcpy(email, anEmail);
    return *this;
  }
  
  Student& Student::setStudentId(const char* anId) {
    //STUDENT: set the student field here...
    strcpy(studentid, anId);
    return *this;
  }

  Student& Student::setOs(const char* anOs) {
    //STUDENT: set the mobile field here...
    strcpy(os, anOs);
    return *this;
  }

  Student& Student::setCourse(const char* aCourse) {
    //STUDENT: set the mobile field here...
    strcpy(course, aCourse);
    return *this;
  }
  
  //STUDENT: implement the stream output operator (<<) here...
  //         and write your student data to output
  std::ostream& operator<<(std::ostream &output, Student &student) {
    output << "{" << std::endl;
    output << "  " << "\"name\":\"" << student.name << "\"," << std::endl;
    output << "  " << "\"pid\":\"" << student.studentid << "\"," << std::endl;
    output << "  " << "\"email\":\"" << student.email << "\"," << std::endl;
    output << "  " << "\"os\":\"" << student.os << "\"," << std::endl;
    output << "  " << "\"course\":\"" << student.course << "\"" << std::endl;
    output << "}" << std::endl;
    return output;
   }

}
