//
//  Date.hpp
//  Lab2
//
//  Created by rick gessner on 1/04/20.
//

#include <iostream>
#ifndef Date_h
#define Date_h

class Date {
public:
  Date(int aMonth, int aDay, int aYear) {
    //Student implement your CTOR
    month = aMonth;
    day = aDay;
    year = aYear;
    std::cout << "in Date-constructor()\n";  
  }
  
  Date(const Date &aCopy) {
    //Student implement your COPY-CTOR
    month = aCopy.month;
    day = aCopy.day;
    year = aCopy.year;
    std::cout << "in Date-copy-constructor()\n"; 
  }
  
  ~Date() {
    //Student implement your DTOR
    std::cout << "in Date-deconstructor()\n"; 
  }
  
  Date& operator=(const Date &aDate) {
    //Student implement your assignment operator
    month = aDate.month;
    day = aDate.day;
    year = aDate.year;
    std::cout << "in Date-assignment-operator()\n"; 
    return *this;
  }

  //STUDENT -- Add methods here (3) to set the month, day, year properties.
  //           For example, create a method called "setMonth(int aMonth)" to set the month value...

  void setMonth(int aMonth){
    month = aMonth;
    std::cout << "in Date-set-month-operator()\n"; 
  }

  void setDay(int aDay){
    day = aDay;
    std::cout << "in Date-set-day-operator()\n"; 
  }

  void setYear(int aYear){
    year = aYear;
    std::cout << "in Date-set-year-operator()\n"; 
  }

  friend std::ostream& operator<<(std::ostream &aStream, Date &aDate) {
    //Student implement the stream inserter operator
    aStream << aDate.month << aDate.day << aDate.year << std::endl;
    std::cout << "in Date-stream-inserter-operator()\n"; 
    return aStream;
  }

protected:
   //STUDENT: add the Date class data members here...
   int month;
   int day;
   int year;
};

#endif /* Date_h */
