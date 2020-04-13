//
//  Meeting.hpp
//  Assignment2
//
//  Created by rick gessner on 1/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#ifndef Meeting_hpp
#define Meeting_hpp

#include <stdio.h>
#include <string>
#include "DateTime.hpp"

namespace ECE141 {

  class Meeting : public DateTime {
  public:
    Meeting(const DateTime &aDT, const std::string &aTitle,
            const std::string &aPerson1, const std::string &aPerson2);  
    //add copy constructor
    Meeting(const Meeting &aCopy);
    //add assignment operator
    Meeting& operator=(const Meeting &aMeeting);
    //add destructor
    ~Meeting();

    Meeting& setDate(const DateTime &aDate);
    Meeting& setTitle(const std::string &aTitle);
    Meeting& setPerson(const std::string &aName, int aPersonNumber); //a little different than the Task class?

    DateTime& getDate() {return dateTime;};
    virtual const char* getTitle() {return title.c_str();};
    std::string& getPerson(int aPersonNumber);
    virtual char* getType();

  protected:
    //add data members here...
    DateTime dateTime;
    std::string title;
    std::string person1;
    std::string person2;
  };

}

#endif /* Meeting_hpp */
