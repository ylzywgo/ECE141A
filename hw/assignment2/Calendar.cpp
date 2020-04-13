//
//  Calendar.cpp
//  Assignment2
//
//  Created by rick gessner on 1/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#include "Calendar.hpp"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <cstring>
#include <map>

namespace ECE141 {
  enum class DOW {sunday, monday, tuesday, 
                  wednesday, thursday, friday, saturday};

  std::map<std::string, int> weekdayToNum = {{"mon",0},{"tue",1},{"wed",2},{"thu",3},{"fri",4},{"sat",5},{"sun",6}};
  std::map<int, std::string> numToMonth = {{1,"January"},{2, "February"}, {3, "March"}, {4, "April"}, {5, "May"}, {6, "June"},
                                           {7, "July"}, {8, "August"}, {9, "September"}, {10, "October"}, {11, "November"}, {12, "December"}};

  Calendar::Calendar(int aMonth, int aYear) : mon(aMonth), year(aYear), fdwd(calculateWeekDay(aYear, aMonth, 1)){}
  Calendar::Calendar(const Calendar &aCopy){
    *this = aCopy;
  }

  Calendar& Calendar::operator=(const Calendar &aCalendar){
    mon = aCalendar.mon;
    year = aCalendar.year;
    fdwd = aCalendar.fdwd;
    items = aCalendar.items;
    eventNum = aCalendar.eventNum;

    return *this;
  }

  Calendar::~Calendar(){
//      for (auto item : items)
//          delete item;
  }
      
  bool Calendar::load(std::istream &anInputStream) {
    //STUDENT: implement
    const int kMaxParts = 5;
    std::array<std::string, kMaxParts> theParts;
    std::string theLine;
    while (std::getline(anInputStream, theLine)) {
      std::istringstream theStringStream(theLine);
      int theCount=0;
      std::string token;
      while (std::getline(theStringStream, token, ',')){
        token.erase(0,token.find_first_not_of(" "));  
        token.erase(token.find_last_not_of(" ") + 1);
        theParts.at(theCount++) = token.substr(1, token.length() - 2);
        // std::cout << theParts.at(theCount -1) << " " << theCount << " ";
      }
      // std::cout << std::endl;
      //ok, the parts array has our data.
      //create either a task or a meeting on the heap, then call addItem...
      std::string time = theParts.at(1);
      int space = time.find_first_of(" ");
      std::string date = time.substr(0, space);
      std::string clock = time.substr(space + 1);

      std::array<int, 5> dateArray;
      int count = 0;
      int i;

      while ((i = date.find_first_of("-")) != -1){
        // std::cout << date.substr(0, i) << std::endl;
        int cur = std::stoi(date.substr(0, i));
        date = date.substr(i + 1);
        // std::cout << date << std::endl;
        dateArray.at(count++) = cur;
      }
      // std::cout << date << std::endl;
      int cur = std::stoi(date);
      dateArray.at(count++) = cur;

      while ((i = clock.find_first_of(":")) != -1){
        // std::cout << clock.substr(0, i) << std::endl;
        int cur = std::stoi(clock.substr(0, i));
        clock = clock.substr(i + 1);
        dateArray.at(count++) = cur;
      }

      // std::cout << clock << std::endl;
      cur = std::stoi(clock);
      dateArray.at(count++) = cur;

      DateTime dateTime(dateArray.at(2), dateArray.at(1), dateArray.at(0), dateArray.at(3), dateArray.at(4));
      // std::cout << dateTime.getDay() << " " << dateTime.getMonth() << " " << dateTime.getYear() << " " << dateTime.getHour() << " " << dateTime.getMinutes() << " " << std::endl;
      std::string title = theParts.at(0);
      std::string person1 = theParts.at(2);
      
      if (theCount == 3){
        Task* task = new Task(dateTime, title, person1);
        addItem(task);
      }
      else{
        std::string person2 = theParts.at(3);
        Meeting* meeting = new Meeting(dateTime, title, person1, person2);
        addItem(meeting);
      }
    }
    return true;

  }
    
  Calendar& Calendar::addItem(DateTime *anItem){
    items.push_back(anItem);
    int year, month, day;
    if (anItem->getType() == "meeting"){
      Meeting* meeting = dynamic_cast<Meeting*>(anItem);
      DateTime date = meeting->getDate();
      year = date.getYear();
      month = date.getMonth();
      day = date.getDay();
    }
    else{
      Task* task = dynamic_cast<Task*>(anItem);
      DateTime date = task->getDate();
      year = date.getYear();
      month = date.getMonth();
      day = date.getDay();
    }

    // std::cout << year << month << day << std::endl;
    int wd = calculateWeekDay(year, month, day);
    int week = (day + fdwd) / 7;
    std::string weekAndDay = std::to_string(week) + " " + std::to_string(wd);
    // std::cout << weekAndDay<< std::endl;
    if (eventNum.find(weekAndDay) == eventNum.end()){
      eventNum[weekAndDay] = 0;
    }
    eventNum[weekAndDay] += 1;
    return *this;
  }
  
  int Calendar::countItemsForDate(const DateTime &aDateTime) const{
    int count = 0;
    std::cout << aDateTime.getYear() << std::endl;
    DateTime date;
    for (int i = 0; i < items.size(); i++){
      DateTime* cur = items.at(i);
        if (cur->getType() == "meeting"){
            Meeting* meeting = dynamic_cast<Meeting*>(cur);
            date = meeting->getDate();
        }
        else{
            Task* task = dynamic_cast<Task*>(cur);
            date = task->getDate();
        }
      if (date == aDateTime){ count++;}
    }
    return count;
  }

  bool Calendar::findItemsForHour(const DateTime &aDateTime){
    for (auto item : items){
      std::string t = item->getType();
      DateTime date;
      if (t == "task"){
        Task* task = dynamic_cast<Task*>(item);
        date = task->getDate();
      }
      else{
        Meeting* meeting = dynamic_cast<Meeting*>(item);
        date = meeting->getDate();
      }
      if (date.sameHour(aDateTime)){
        return true;
      }
    }
    return false;
  }

  int Calendar::countTasks() const{
    int count = 0;
    for (auto item : items){
      // std::cout<<item->getType()<<std::endl;
      if (item->getType() == "task"){ count++;}
    }
    return count;
  }
  int Calendar::countMeetings() const{
    int count = 0;
    for (auto item : items){
      // DateTime *cur = items.at(i);
      if (item->getType() == "meeting"){ count++;}
    }
    return count;
  }

  const Calendar& Calendar::show(std::ostream &anOutput) const{
    anOutput << "|------------------------------------------------|\n";

    anOutput << "|   ";
    anOutput << numToMonth[mon] << " ";
    anOutput << year;
    int space = 45 - numToMonth[mon].length() - std::to_string(year).length();
    for (int i = 0; i < space - 1; i++) anOutput << " ";
    anOutput << "|\n";

    // anOutput << "|   January  2020                                |\n";
    anOutput << "|------------------------------------------------|\n";
    anOutput << "|  Su  |  Mo  |  Tu  |  We  |  Th  |  Fr  |  Sa  |\n";
    for (int i = 0; i < 5; i++){
      anOutput << "|------------------------------------------------|\n";
      for (int j = 0; j < 7; j++){
        anOutput << "|  ";
        std::string str = std::to_string(i)+ " " + std::to_string((j + 6) % 7);
        if (eventNum.find(str) != eventNum.end()){
          int num = eventNum.at(str);
          anOutput << num;
          if (num < 10){ anOutput << " ";}
        }
        else{
          anOutput << "  ";
        }
        anOutput << "  ";
      }
      anOutput << "|\n";
    }

    return *this;
  } 

  int Calendar::calculateWeekDay(int y, int m, int d){
    if (m == 1 || m == 2) {
      m += 12;
      y--;
    }
    int iWeek = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
    return iWeek;
  }
  
  const Calendar& Calendar::showSummary(std::ostream &anOutput) const{
    anOutput << "|------------------------------------------------|\n";
    anOutput << "|   ";
    anOutput << numToMonth[mon] << " ";
    anOutput << year;
    std::string sum = " Summary";
    anOutput << sum;
    int space = 45 - numToMonth[mon].length() - std::to_string(year).length() - sum.length();
    for (int i = 0; i < space - 1; i++) anOutput << " ";
    anOutput << "|\n";
    anOutput << "|------------------------------------------------|\n";
    for (auto item : items){
      int year, day, hour;
      std::string title, person1, person2;
      // std::cout <<  "hgah" << std::endl;
      std::string s = item->getType();
      if (s == "meeting"){
        Meeting* meeting = dynamic_cast<Meeting*>(item);
        DateTime date = meeting->getDate();
        day = date.getDay();
        hour = date.getHour();
        title = meeting->getTitle();
        person1 = meeting->getPerson(1);
        person2 = meeting->getPerson(2);
      }
      else{
        Task* task = dynamic_cast<Task*>(item);
        DateTime date = task->getDate();
        day = date.getDay();
        hour = date.getHour();
        title = task->getTitle();
      }
        // day = item->getDay();
        // hour = item->getHour();
        // title = item->getTitle();

      anOutput << "|  Jan " << day << ",";
      if (hour < 12){
        if (hour == 0) anOutput << "12a";
        else anOutput << hour << "a";
      }
      else{
        if (hour == 12) anOutput << "12p";
        else anOutput << hour - 12 << "p"; 
      }
      int space = 2;
      if (day / 10 > 0) space--;
      if (hour == 0 || hour == 10 || hour == 11 || hour == 12 || hour == 23 || hour == 22) space--;
      for (int i = 0; i < space; i++) anOutput << " ";

      if (s == "task"){
        anOutput << "| Task: ";
        space = 28 - title.length();
        anOutput << title;
        for (int i = 0; i < space; i++) anOutput << " ";
      }
      else{
        anOutput << "| Mtg: ";
        int space = 29 - title.length();
        anOutput << title;
        for (int i = 0; i < space; i++) anOutput << " ";
        anOutput << "|\n";

        anOutput << "|            | " << person1 << ", " << person2;
        space = 32 - person1.length() - person2.length();
        for (int i = 0; i < space; i++) anOutput << " ";
      }
      anOutput << "|\n";
      anOutput << "|------------------------------------------------|\n";
    }
    return *this;
  }
  
  DateTime Calendar::firstAvailableHour(Calendar &anOther, int startHour, int stopHour, char *dow){
    int endDate = getDaysInMonth(mon, year);
    DateTime date(1, mon, year, 0, 0);
    // std::cout << "hhhhhhhh" << std::endl;
    bool find = false;
    if (dow == nullptr){
      for (int day = 1; day <= endDate; day++){
        for (int h = startHour; h <= stopHour; h++){
          DateTime newdate(day, mon, year, h, 0);
          if (!findItemsForHour(newdate) && !anOther.findItemsForHour(newdate)){
            date = newdate;
            find = true;
            break;
          }
        }
        if (find == true) break;
      }
    }
    else{
      std::vector<int> allWeekDayDate = {};
      std::string dows = dow;
      int needFindWeekDay = weekdayToNum[dows];
      int startDate;
      if (needFindWeekDay > fdwd){
        startDate = 1 + (needFindWeekDay - fdwd);
      }
      else{
        startDate = 1 + (7 - (fdwd - needFindWeekDay));
      }

      for (int day = startDate; day <= endDate; day += 7){
        for (int h = startHour; h <= stopHour; h++){
          DateTime newdate(day, mon, year, h, 0);
          if (!findItemsForHour(newdate) && !anOther.findItemsForHour(newdate)){
            date = newdate;
            find = true;
            break;
          }
        }
        if (find == true) break;
      }
    }

    // std::cout << "hhhhhhhh" << std::endl;

    std::string person1, person2;
    if (items[0]->getType() == "task") {
      Task* task = dynamic_cast<Task*>(items[0]);
      person1 = task->getPerson();
    }
    else{
      Meeting* meeting = dynamic_cast<Meeting*>(items[0]);
      person1 = meeting->getPerson(1);
    }

    if (anOther.getItems()[0]->getType() == "task") {
      Task* task = dynamic_cast<Task*>(items[0]);
      person2 = task->getPerson();
    }
    else{
      Meeting* meeting = dynamic_cast<Meeting*>(items[0]);
      person2 = meeting->getPerson(1);
    }

    std::string title = "";
    title.append(person1).append(" meeting ").append(person2);

    Meeting* meeting = new Meeting(date, title, person1, person2);
    addItem(meeting);
    anOther.addItem(meeting);

    return date;
  }

  std::ostream & operator << (std::ostream &anOutput, const Calendar &aCalendar) {
    //STUDENT: implement
    aCalendar.show(anOutput);
    return anOutput;
  }

//add other methods here...
  int Calendar::getDaysInMonth(int aMonth, int aYear){
    static int kDaysInMonth[]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(2==aMonth) {
      bool isLeapYear = 
        (aYear % 4 == 0 && aYear % 100 != 0) || (aYear % 400 == 0);
      return kDaysInMonth[1] + isLeapYear;
    }
    return kDaysInMonth[aMonth-1];
  }
}
