//
//  main.cpp
//  Assignment1
//
//  Created by rick gessner on 1/2/20.
//

#include <iostream>
#include "TextStreamWriter.hpp"
#include "TextStreamTokenizer.hpp"
#include "TextStreamLineReader.hpp"
#include "JSONStreamWriter.hpp"
#include "BinaryStreamWriter.hpp"


  //STUDENT: intialize this to point to root of your project folder...
const char* kWorkingFolderPath = "/Users/yawen_zhao/UCSD/SPR20/ECE141A/wi20-assignment1-ylzywgo/";
const int   kDefaultCount = 20;


void doTerminalIO() {
  //STUDENT: as user to enter name and age, then print a summary of both the terminal
}

int main(int argc, const char * argv[]) {
  std::cout << "Running tests..." << std::endl;
    
    //PART 1 -- simple user I/O...
    char name[100];
    int age;

    std::cout << "Enter your name:" << std::endl;
    std::cin >> name;

    std::cout << "Enter your age:" << std::endl;
    std::cin >> age;

    std::cout << "Thanks " << name << ", you did a good job for someone who is " << age << "!" << std::endl;

  
  doTerminalIO();
  
    //PART 2 --
  
  ECE141::TextStreamWriter theTextWriter(kWorkingFolderPath, "numbers.txt");
  theTextWriter.run(23);
  theTextWriter.run(85);
  theTextWriter.run(6);
  theTextWriter.run(709);
  
   //PART 3 --
  ECE141::TextStreamTokenizer theTokenReader(kWorkingFolderPath, "numbers.txt");
  std::ofstream output2;
  char thePath2[512];
  sprintf(thePath2, "%s/%s", kWorkingFolderPath, "part3_res.txt");
  output2.open(thePath2, std::ofstream::out | std::ofstream::app);
  
  theTokenReader.run(output2);
  
   //PART 4 --
  ECE141::TextStreamLineReader theLineReader(kWorkingFolderPath, "numbers.txt");
  std::ofstream output3;
  char thePath3[512];
  sprintf(thePath3, "%s/%s", kWorkingFolderPath, "part4_res.txt");
  output3.open(thePath3, std::ofstream::out | std::ofstream::app);

  theLineReader.run(output3);
   
   //PART 5 --
  ECE141::JSONStreamWriter theJSONWriter(kWorkingFolderPath, "aboutme.json");
  theJSONWriter.run();
   
   //PART 6 --
  ECE141::BinaryStreamWriter theBinaryWriter(kWorkingFolderPath, "blocks.bin");
  theBinaryWriter.run(kDefaultCount);
  
  return 0;
}
