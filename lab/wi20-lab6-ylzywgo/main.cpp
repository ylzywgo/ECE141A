//
//  main.cpp
//  Bitwise
//
//  Created by rick gessner on 2/9/20.
//

#include <iostream>
#include "BitwiseTester.hpp"

int main(int argc, const char *argv[]) {

    ECE141::BitwiseTester<uint32_t> tests;
    tests.runTests();

    return 0;
}
