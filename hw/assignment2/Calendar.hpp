//
//  Calendar.hpp
//  Assignment2
//
//  Created by rick gessner on 1/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#ifndef Calendar_hpp
#define Calendar_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Task.hpp"
#include "Meeting.hpp"
#include <array>
#include <map>

namespace ECE141 {

  class Calendar {
  public:
    Calendar(int aMonth=1, int aYear=2020);
    //add copy constructor
    Calendar(const Calendar &aCopy);
    //add assignment operator
    Calendar& operator=(const Calendar &aCalendar);
    //add destructor
    ~Calendar();

    //add other methods described in assignment here...
    bool load(std::istream &anInputStream);
    
    Calendar& addItem(DateTime *anItem);
    
    int getMonth() const {return mon;}; //ask the calendar the month it represents
    int getYear() const {return year;}; //ask the calendar what year it represents 
    std::vector<DateTime*> getItems() const{return items;};
    int countItemsForDate(const DateTime &aDateTime) const; //how many items on a given date?
    bool findItemsForHour(const DateTime &aDateTime);
    int countTasks() const; //how many added items are tasks?
    int countMeetings() const; //how many added items are meetings?

    int calculateWeekDay(int y, int m, int d);
     
      
    const Calendar& show(std::ostream &anOutput) const; //show a text-based version of full-month calendar (see below)
    const Calendar& showSummary(std::ostream &anOutput) const; //show a text-based version of items (see below)
     
     //find the first day/time that both calendar objects have a free hour (within the given time range)
    DateTime  firstAvailableHour(Calendar &anOther, int startHour=0, int stopHour=0, char *dow=nullptr);

    friend std::ostream& operator<<(std::ostream &output, const Calendar &aCalendar);

    int getDaysInMonth(int aMonth, int aYear);
    
  protected:
    int mon, year;
    int fdwd;
    std::vector<DateTime*> items;
    std::map<std::string,int> eventNum;
  };

}

#endif /* Calendar_hpp */
