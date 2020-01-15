//
//  Student.hpp
//  Assignment2
//
//  Created by rick gessner on 1/9/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef Student_hpp
#define Student_hpp

#include <stdio.h>
#include <iostream>

namespace ECE141 {
  class Student {
  public:
          Student();
    
    Student&    setName(const char* aName);
    Student&    setEmail(const char* anEmail);
    Student&    setStudentId(const char* anId);
    Student&    setOs(const char* anOs);
    Student&    setCourse(const char* aCourse);
    
    const char* getName() const {return name;}
    const char* getEmail() const {return email;}
    const char* getStudentId() const {return studentid;}
    const char* getOs() const {return os;}
    const char* getCourse() const {return course;}
    
    //STUDENT: declare stream output operator (<<) as a friend method here...
   friend std::ostream& operator<<(std::ostream &output, Student &student);
    
  protected:
    char name[100];
    char email[50];
    char studentid[50];
    char os[20];
    char course[50];
  };
}



#endif /* Student_hpp */
