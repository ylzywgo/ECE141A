//
//  main.cpp
//  Assignment3
//
//  Created by rick gessner on 1/29/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#include <iostream>
#include "Testing.hpp"

int main(int argc, const char * argv[]) {
    ECE141::Testing theTests(std::cout);
    theTests.runTests();

  return 0;
}
