//
// Created by yawen zhao on 2/26/20.
//

#include <iostream>
#include <fstream>
#include "DateTime.hpp"
#include "Calendar.hpp"
#include "Testing.hpp"

std::ostream& getOutputStream() {return std::cout;}

int main(){
    ECE141::Testing theTester(getOutputStream());
    theTester.runTests();
    return 0;
};

