//
//  Date.cpp
//  Assignment2
//
//  Created by rick gessner on 1/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#include "DateTime.hpp"

namespace ECE141 {
  DateTime::DateTime(int aDay, int aMon, int aYear, int anHour, int aMins) {
    //STUDENT: implement
    day = aDay;
    month = aMon;
    year = aYear;
    hour = anHour;
    minutes = aMins;
  }

  // :day(aCopy.day), month(aCopy.month), year(aCopy.year), hour(aCopy.hour), minutes(aCopy.minutes)
  DateTime::DateTime(const DateTime &aCopy){
    *this = aCopy;
  }
  
  DateTime& DateTime::operator=(const DateTime &aDateTime){
    day = aDateTime.day;
    month = aDateTime.month;
    year = aDateTime.year;
    hour = aDateTime.hour;
    minutes = aDateTime.minutes;

    return *this;
  }

  DateTime::~DateTime(){}

  //add other methods here...
  bool DateTime::operator==(const DateTime &aCopy){
    if (day != aCopy.day) return false;
    else if (month != aCopy.month) return false;
    else if (year != aCopy.year) return false;
//    else if (hour != aCopy.hour) return false;
//    else if (minutes != aCopy.minutes) return false;
    else return true;
  }

  bool DateTime::isValid(){
    if (minutes < 0 || minutes > 59) return false;
    if (hour < 0 || hour > 23) return false;
    if (year < 0 || year > 2050) return false;
    if (month < 1 || month > 12) return false;
    if (day <= 0) return false;
    if ((month == 1 || month == 3 || month == 5 || month == 7 ||
         month == 8 || month == 10 || month == 12) && day > 31)
         return false;
    if ((month == 4 || month == 6 || month == 9 || month ==11 ) && day > 30)
         return false;
    if (month == 2){
      if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)){
        if (day > 29){ return false;}
      }
      else{
        if (day > 28){ return false;}
      }
    }
    return true;
  }

  DateTime& DateTime::setMonth(int aValue){ //range: 1-12
    month = aValue;
    return *this;
  }  
  DateTime& DateTime::setDay(int aValue){ //range: 1-31
    day = aValue;
    return *this;
  }    
  DateTime& DateTime::setYear(int aValue){ //range: 0-2050
    year = aValue;
    return *this;
  }   
  DateTime& DateTime::setHour(int aValue){ //range: 0-23 (military time)
    hour = aValue;
    return *this;
  }   
  DateTime& DateTime::setMinutes(int aValue){ //range: 0-59
    minutes = aValue;
    return *this;
  }

  int DateTime::getMonth() const {return month;}
  int DateTime::getDay() const {return day;}
  int DateTime::getYear() const {return year;}
  int DateTime::getHour() const {return hour;}
  int DateTime::getMinutes() const {return minutes;}
  const char* DateTime::getType(){
      return "type";
  };

  bool DateTime::sameHour(const DateTime &aDateTime) const{
    // std::cout << *this << std::endl;
    // std::cout << aDateTime << std::endl;
    // std::cout << std::endl;
    if (day != aDateTime.day) return false;
    else if (month != aDateTime.month) return false;
    else if (year != aDateTime.year) return false;
    else if (hour != aDateTime.hour) return false;
    else return true;
  }

  std::ostream& operator<<(std::ostream &output, const DateTime &aCalendar){
    output << aCalendar.year << "-";
    if (aCalendar.month < 10) output << "0";
    output << aCalendar.month << "-";
    if (aCalendar.day < 10) output << "0";
    output << aCalendar.day << " ";
    if (aCalendar.hour < 10) output << "0";
    output << aCalendar.hour << ":";
    if (aCalendar.minutes < 10) output << "0";
    output << aCalendar.minutes;
    return output;
  }
}
