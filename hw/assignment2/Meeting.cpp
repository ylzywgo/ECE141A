//
//  Meeting.cpp
//  Assignment2
//
//  Created by rick gessner on 1/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#include "Meeting.hpp"

namespace ECE141 {
    Meeting::Meeting(const DateTime &aDT, const std::string &aTitle,const std::string &aPerson1, const std::string &aPerson2): dateTime(aDT), title(aTitle), person1(aPerson1), person2(aPerson2){} 
    Meeting::Meeting(const Meeting &aCopy){
        *this = aCopy;
    }
    Meeting& Meeting::operator=(const Meeting &aMeeting){
        dateTime = aMeeting.dateTime;
        title = aMeeting.title;
        person1 = aMeeting.person1;
        person2 = aMeeting.person2;

        return *this;
    }
    Meeting::~Meeting(){}
    //STUDENT: implement all your methods...
    Meeting& Meeting::setDate(const DateTime &aDate){
        dateTime = aDate;
        return *this;
    }
    Meeting& Meeting::setTitle(const std::string &aTitle){
        title = aTitle;
        return *this;
    }
    Meeting& Meeting::setPerson(const std::string &aName, int aPersonNumber){ //a little different than the Task class?
        if (aPersonNumber == 1){
            person1 = aName;
        }
        if (aPersonNumber == 2){
          person2 = aName;
        }
        return *this;
    } 

    std::string& Meeting::getPerson(int aPersonNumber){
        if (aPersonNumber == 1){
            return person1;
        }
        else{
            return person2;
        }
    }

    char* Meeting::getType(){ 
        return "meeting";
    }
}
