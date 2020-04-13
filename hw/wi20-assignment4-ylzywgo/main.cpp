#include <iostream>
#include <fstream>
#include "Testing.hpp"

std::ostream& getOutput() {return std::cout;}

std::string getJSONPath() {return std::string("test.json");}  //e.g. test.json
std::string getCmdsPath() {return std::string("test.txt");} //e.g. text.txt

int main(int argc, const char * argv[]) {

    std::fstream theJSONFile(getJSONPath());
    std::fstream theCommands(getCmdsPath());

// the Test class will construct a JSONParser and a Model class for you...

    ECE141::Testing::runTests(theJSONFile, theCommands, getOutput());

    return 0;
}