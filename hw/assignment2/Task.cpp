//
//  Task.cpp
//  Assignment2
//
//  Created by rick gessner on 1/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#include "Task.hpp"

namespace ECE141 {
    Task::Task(const DateTime &aDT, const std::string &aTitle, const std::string &aPerson): dateTime(aDT), title(aTitle), person(aPerson) {}

    Task::Task(const Task &aCopy){
        // dateTime = aCopy.dateTime;
        // title = aCopy.title;
        // person = aCopy.person;
        *this = aCopy;
    }
    Task& Task::operator=(const Task &aTask){
        dateTime = aTask.dateTime;
        title = aTask.title;
        person = aTask.person;
        
        return *this;
    }
    Task::~Task(){}

    Task& Task::setDate(const DateTime & aDate){
        dateTime = aDate;
        return *this;
    }

    Task& Task::setTitle(const std::string aTitle){
        title = aTitle;
        return *this;
    }
    
    Task& Task::setPerson(const std::string aPerson)
    {
        person = aPerson;
        return *this;
    }

    char* Task::getType() {
        return "task";
    }

}
