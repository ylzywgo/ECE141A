//
//  Header.hpp
//  Assignment2
//
//  Created by rick gessner on 1/16/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#ifndef Datahelper_h
#define Datahelper_h

#include <string>

namespace ECE141 {

  struct DataHelper {
    
    static int getRandomValue(int aMin, int aMax) {
      return aMin + rand() % (aMax - aMin) ;
    }

    //create a fake title for task or meeting
    static std::string getFakeTitle() {
      static const char* words[] = {"discuss ","team ","dynamics ","culture ","size "};
      const int theWordCount=sizeof(words)/sizeof(char*);
      std::string theResult;
      int i = rand();
      for(int i=0;i<3;i++) {
        int theWordIndex=rand() % theWordCount;
        const char* c = words[theWordIndex];
        // std::cout << c << std::endl;
        std::string temp(c);
        theResult.append(temp);
      }
      return theResult;
    }
    
      //get a fake person name (from list1)
    static const char* getFakeUser1() {
      static const char* thePeople[] = {"bob ","joe ","tom ","steve ","rick "};
      const int theCount=sizeof(thePeople)/sizeof(char*);
      int theIndex=rand() % theCount;
      return thePeople[theIndex];
    }
    
      //get a fake person name (from list2)
    static const char* getFakeUser2() {
      static const char* thePeople[] = {"alice ","beyonce ","megan ","haisley ","yara "};
      const int theCount=sizeof(thePeople)/sizeof(char*);
      int theIndex=rand() % theCount;
      return thePeople[theIndex];
    }

  };

}

#endif /* Datahelper_h */
