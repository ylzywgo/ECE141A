//
//  Task.hpp
//  Assignment2
//
//  Created by rick gessner on 1/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#ifndef Task_hpp
#define Task_hpp

#include <stdio.h>
#include "DateTime.hpp"
#include <string>

namespace ECE141 {

  class Task : public DateTime {
  public:
    Task(const DateTime &aDT, const std::string &aTitle, const std::string &aPerson);  
    //add copy constructor
    Task(const Task &aCopy);
    //add assignment operator
    Task& operator=(const Task &aTask);
    //add destructor
    ~Task();
        
    //add specified methods here...
    Task& setDate(const DateTime & aDate);
    Task& setTitle(const std::string aTitle);
    Task& setPerson(const std::string aPerson);

    DateTime& getDate()  {return dateTime;};
    virtual const char * getTitle()  {return title.c_str();};
    std::string& getPerson() {return person;};
    virtual char* getType();

  protected:
    //add data members here...
    DateTime dateTime;
    std::string title;
    std::string person;
  };

}

#endif /* Task_hpp */
