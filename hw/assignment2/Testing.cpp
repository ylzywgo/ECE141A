//
//  Testing.cpp
//  Assignment2
//
//  Created by rick gessner on 1/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#include "Testing.hpp"
#include "DateTime.hpp"
#include "Task.hpp"
#include "Meeting.hpp"
#include "Calendar.hpp"
#include "DataHelper.hpp"
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <array>

namespace ECE141 {
   
  bool testDateTime(Testing &aTester) {
    bool theResult=true;

    //add tests here for each method you want to validate!
    aTester.getOutput()
      << "\nTesting DateTime class...\n"
      << "-------------------------\n";

    DateTime theDate1(4,1,1961, 14,15); //rick's birthday
    DateTime theDate2(4,1,1961, 14,15); //rick's birthday
        
    //first -- test operator== (comparison)...
    if(!aTester.assertTrue("operator==", theDate1==theDate2)) {
      theResult=false;
    }

    //now test the copy constructor...
    DateTime theDateCopy(theDate1); //copy construct...
    if(!aTester.assertTrue("ctor(copy)", theDate1==theDateCopy)) {
      theResult=false;
    }

    DateTime theDateCopy2 = theDate1; //copy construct...
    if(!aTester.assertTrue("operator=", theDate1==theDateCopy2)) {
      theResult=false;
    }

    DateTime theDate3 = DateTime(1, 13, 1990, 14, 15);
    DateTime theDate4 = DateTime(31, 4, 1990, 14, 15);
    DateTime theDate5 = DateTime(29, 2, 1990, 14, 15);
    DateTime theDate6 = DateTime(29, 2, 2008, 14, 15);
    DateTime theDate7 = DateTime(30, 2, 2008, 14, 15);
    DateTime theDate8 = DateTime(1, 12, 1990, 24, 15);
    DateTime theDate9 = DateTime(1, 12, 1990, 14, 60);
    if (!aTester.assertTrue("isValid1", theDate6.isValid() == true)){
      theResult=false;
    }
    if (!aTester.assertTrue("isValid2",theDate5.isValid() == false)){
      theResult=false;
    }
    if (!aTester.assertTrue("isValid3", theDate9.isValid() == false)){
      theResult=false;
    }
    
    //add other tests here...

    if (!aTester.assertTrue("getDay", theDate1.getDay() == 4)){
      theResult=false;
    }
    if (!aTester.assertTrue("getMonth",theDate1.getMonth() == 1)){
      theResult=false;
    }
    if (!aTester.assertTrue("getYear", theDate1.getYear() == 1961)){
      theResult=false;
    }
    if (!aTester.assertTrue("getHour", theDate1.getHour() == 14)){
      theResult=false;
    }
    if (!aTester.assertTrue("getMinute",theDate1.getMinutes() == 15)){
      theResult=false;
    }

    theDate2.setDay(3);
    theDate2.setMonth(2);
    theDate2.setYear(2020);
    theDate2.setHour(20);
    theDate2.setMinutes(30);

    if (!aTester.assertTrue("setDay", theDate2.getDay() == 3)){
      theResult=false;
    }
    if (!aTester.assertTrue("setMonth",theDate2.getMonth() == 2)){
      theResult=false;
    }
    if (!aTester.assertTrue("setYear", theDate2.getYear() == 2020)){
      theResult=false;
    }
    if (!aTester.assertTrue("setHour", theDate2.getHour() == 20)){
      theResult=false;
    }
    if (!aTester.assertTrue("setMinute",theDate2.getMinutes() == 30)){
      theResult=false;
    }
    
    return theResult;
  }

  //-----------------------------------
  //Test all the task methods...
  bool testTask(Testing &aTester) {
    bool theResult=true;

    aTester.getOutput()
      << "\nTesting Task class...\n"
      << "-------------------------\n";
    
    DateTime theDateTime1(29, 1, 2020, 12, 12);
    DateTime theDateTime2(20, 2, 2020, 13, 15);
    std::string title("assignment2");
    std::string person("ywzhao");
    std::string title2("calendar assignment");
    std::string person2("yawen zhao");
    Task task1(theDateTime1, title, person);

    if (!aTester.assertTrue("getDateTime", task1.getDate() == theDateTime1)){
      theResult=false;
    }

    if (!aTester.assertTrue("getTitle", task1.getTitle() == title)){
      theResult=false;
    }

    if (!aTester.assertTrue("getPerson", task1.getPerson() == person)){
      theResult=false;
    }

    const char* c = "task";

    if (!aTester.assertTrue("getType", strcmp(task1.getType(), c) == 0)){
      theResult=false;
    }

    task1.setDate(theDateTime2);
    task1.setTitle(title2);
    task1.setPerson(person2);

    if (!aTester.assertTrue("setDateTime", task1.getDate() == theDateTime2)){
      theResult=false;
    }

    if (!aTester.assertTrue("setTitle", task1.getTitle()  == title2)){
      theResult=false;
    }

    if (!aTester.assertTrue("setPerson", task1.getPerson() == person2)){
      theResult=false;
    }

    return theResult;
  }

  //-----------------------------------
  //Test all the meeting methods...
  bool testMeeting(Testing &aTester) {
    bool theResult=true;

    aTester.getOutput()
      << "\nTesting Meeting class...\n"
      << "-------------------------\n";
    
    DateTime theDateTime3(29, 1, 2020, 12, 12);
    DateTime theDateTime4(20, 2, 2020, 13, 15);
    std::string title("assignment2");
    std::string person1("ywzhao");
    std::string person2("yxzhang");
    std::string title2("calendar assignment");
    std::string person3("yawen zhao");
    std::string person4("yixun zhang");
    Meeting meeting(theDateTime3, title, person1, person2);

    if (!aTester.assertTrue("getDateTime", meeting.getDate() == theDateTime3)){
      theResult=false;
    }

    if (!aTester.assertTrue("getTitle", meeting.getTitle() == title)){
      theResult=false;
    }

    if (!aTester.assertTrue("getPerson1", meeting.getPerson(1) == person1)){
      theResult=false;
    }

    if (!aTester.assertTrue("getPerson2", meeting.getPerson(2) == person2)){
      theResult=false;
    }


    if (!aTester.assertTrue("getType", meeting.getType()== "meeting")){
      theResult=false;
    }

    meeting.setDate(theDateTime4);
    meeting.setTitle(title2);
    meeting.setPerson(person3, 1);
    meeting.setPerson(person4, 2);


    if (!aTester.assertTrue("setDateTime", meeting.getDate() == theDateTime4)){
      theResult=false;
    }

    if (!aTester.assertTrue("setTitle", meeting.getTitle()  == title2)){
      theResult=false;
    }

    if (!aTester.assertTrue("setPerson1", meeting.getPerson(1) == person3)){
      theResult=false;
    }

    if (!aTester.assertTrue("setPerson2", meeting.getPerson(2) == person4)){
      theResult=false;
    }

    return theResult;
  }

  // -----------------------------------
  // Test all the calendar methods...
  bool testCalendar(Testing &aTester) {
    bool theResult = true;
    
    aTester.getOutput()
      << "\nTesting Calendar class...\n"
      << "-------------------------\n";
    
    const int theMonth = 1;
    const int theYear = 2020;
    ECE141::Calendar theCalendar(theMonth,theYear);
      
    //---------------------------------------------------
    //Add a test for loading of items from file...
    const char * thePath="items.txt"; //items.txt file?
    std::ifstream theStream(thePath);
    theCalendar.load(theStream);
    
    // std::cout << theCalendar.countTasks() << std::endl;
    if(!aTester.assertTrue("addItem(task)", theCalendar.countTasks())) {  //SHOULD  be valid!
      theResult = false;
    }

    if(!aTester.assertTrue("addItem(meeting)", theCalendar.countMeetings())) {  //SHOULD  be valid!
      theResult = false;
    }

    ECE141::Calendar theCalendar2(theMonth,theYear);

    //---------------------------------------------------
    //test adding fake tasks...
    for(int i=0;i<10;i++) {
      //make a fake (but reasonabale) datetime...
      DateTime theDT(
        DataHelper::getRandomValue(1, 31), theMonth, theYear,
        DataHelper::getRandomValue(0, 23), DataHelper::getRandomValue(0, 59));

      Task *theTask = new Task( theDT, DataHelper::getFakeTitle(), DataHelper::getFakeUser1());
      theCalendar2.addItem(theTask);
    }

    // //---------------------------------------------------
    // //test adding fake meetings...
    for(int i=0;i<10;i++) {
      //make a fake (but reasonabale) datetime...
      DateTime theDT(
        DataHelper::getRandomValue(1, 31), theMonth, theYear,
        DataHelper::getRandomValue(0, 23), DataHelper::getRandomValue(0, 59));

      ECE141::Meeting *theMtg = new ECE141::Meeting( theDT, DataHelper::getFakeTitle(), DataHelper::getFakeUser1(), DataHelper::getFakeUser2());
      theCalendar2.addItem(theMtg);
    }
    
    // std::cout << theCalendar2.countTasks() << std::endl;

    // //---------------------------------------------------
    
    // //now output your calendar show() and summary() methods...
    // aTester.getOutput() << theCalendar << "\n";
    theCalendar.show(aTester.getOutput());
    aTester.getOutput() << "\n";
    theCalendar.showSummary(aTester.getOutput());
    aTester.getOutput() << "\n";
    theCalendar2.show(aTester.getOutput());
    aTester.getOutput() << "\n";
    theCalendar2.showSummary(aTester.getOutput());
    aTester.getOutput() << "\n";
    DateTime dateTime11(8, 1, 2020, 0, 0);
    std::cout << "countItemsForDate for Jan 8 is " << theCalendar2.countItemsForDate(dateTime11) << std::endl;

    DateTime res = theCalendar.firstAvailableHour(theCalendar2, 21, 22, "sun");
    aTester.getOutput() << res << "\n";
    aTester.getOutput() << "\n";

    aTester.getOutput() << theCalendar << "\n";
    aTester.getOutput() << "\n";
    theCalendar.showSummary(aTester.getOutput());
    aTester.getOutput() << "\n";
    aTester.getOutput() << theCalendar2 << "\n";
    aTester.getOutput() << "\n";
    theCalendar2.showSummary(aTester.getOutput());
    
    return theResult;
  }

  //----------- this is the test controller ---------------
  
  bool Testing::assertTrue(const char *aMessage, bool aValue) {
    static const char* theMsgs[]={"OK\n","FAIL\n"};
    output << "\t" << aMessage << " " << theMsgs[!aValue];
    return aValue;
  }

  bool Testing::assertFalse(const char *aMessage, bool aValue) {
    static const char* theMsgs[]={"OK\n","FAIL\n"};
    output << "\t" << aMessage << " " << theMsgs[aValue];
    return false==aValue;
  }

  bool Testing::fail(const char* aMessage) {
    output << "Failure: " << aMessage << "\n";
    return false;
  }

  bool Testing::succeed(const char* aMessage) {
    output << "Success: " << aMessage << "\n";
    return true;
  }
  
  //This is the main test function...
  bool Testing::runTests() {
    
    if(!testDateTime(*this)) {
      output << "DateTime tests failed\n";
      return false;
    }

    if(!testTask(*this)) {
      output << "Task tests failed (stopping)\n";
      return false;
    }

    if(!testMeeting(*this)) {
      output << "Meeting tests failed  (stopping)\n";
      return false;
    }

    if(!testCalendar(*this)) {
      output << "Calendar tests failed  (stopping)\n";
      return false;
    }

    return true;
  }

}
