//
//  main.cpp
//  Lab2
//
//  Created by rick gessner on 1/04/20.
//

#include <iostream>
#include "Date.hpp"

int main(int argc, const char * argv[]) {
    
  //-----------------------------------------------
  //do part 1 inside this block...
  {
    std::cout << "Part1...\n";
    //Add your code for part 1 here...
    Date birthday = Date(5, 24, 1997);
  }
  //PUT A BREAKPOINT on the NEXT line of code, and run your program
  std::cout << "Part1 is done.\n";
  
  //-----------------------------------------------
  //Do part 2 inside this block...
  {
     std::cout << "Part2...\n";
    //Add your code for part2 here...
    Date theDate1 = Date(1, 13, 2020);
    Date theDate2 = Date(theDate1);
  }
  //PUT A BREAKPOINT on the NEXT line of code, and run your program
  std::cout << "Part 2 is done.\n";
      
  //-----------------------------------------------
  //Do part 3 inside this block...
  {
     std::cout << "Part3...\n";
    //Add your code for part2 here...
    Date *date;
    date = new Date(1, 1, 2020);

  }
  //PUT A BREAKPOINT on the NEXT line of code, and run your program
  std::cout << "Part 3 is done.\n";
  std::cout << "main() is done.\n"; 
}
