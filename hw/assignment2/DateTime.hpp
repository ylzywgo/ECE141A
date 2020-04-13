//
//  Date.hpp
//  Assignment2
//
//  Created by rick gessner on 1/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#ifndef DateTime_hpp
#define DateTime_hpp

#include <stdio.h>
#include <iostream>

namespace ECE141 {

  class DateTime {
  public:
    DateTime(int aDay=0, int aMon=0, int aYear=0, int anHour=0, int aMins=0);
    //add copy constructor...
    DateTime(const DateTime &aCopy);
    //add assignment operator
    DateTime& operator=(const DateTime &aDateTime);
    //add destructor
    ~DateTime();
    //add specified methods here...
    bool operator==(const DateTime &aCopy);
    bool isValid(); //return true if all fields are within the valid range
    DateTime& setMonth(int aValue);  //range: 1-12
    DateTime& setDay(int aValue);    //range: 1-31
    DateTime& setYear(int aValue);   //range: 0-2050
    DateTime& setHour(int aValue);   //range: 0-23 (military time)
    DateTime& setMinutes(int aValue); //range: 0-59
    virtual const char* getTitle() {
      return "title";
    };

    int getMonth() const;
    int getDay() const;
    int getYear() const;
    int getHour() const;
    int getMinutes() const;
    virtual const char* getType();

    bool sameHour(const DateTime & aDateTime) const;

    friend std::ostream& operator<<(std::ostream &output, const DateTime &aDateTime);
        
  protected:
    //add specified data members here..
    int month, day, year, hour, minutes;
  };

}

#endif /* DateTime_hpp */
