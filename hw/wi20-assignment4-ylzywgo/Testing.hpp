//
//  Testing.hpp
//  Assignment4
//
//  Created by rick gessner on 2/16/20.
//

#ifndef Testing_h
#define Testing_h

#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include "CommandProcessor.hpp"
#include "JSONParser.hpp"
#include "Model.hpp"

namespace ECE141 {

  class Testing {
  public:
    
    static bool runTests (std::istream &aJSONFile, std::istream &aCmdFile, std::ostream &anOutput) {
      
      Testing theTests(anOutput);
      return theTests.run(aJSONFile, aCmdFile);
    }
          
  protected:
      
    //let's wire up the testing mechansim here.
    //testing involves reading commands from file, and running through command processor...
    bool run(std::istream &aJSONFile, std::istream &aCmdFile) {

      ECE141::JSONParser theParser(aJSONFile);
      ECE141::Model theModel;
      theParser.parse(&theModel);
      std::cout << theModel << std::endl;

      auto theQuery = theModel.query();
//      int count = theQuery.within("root").before("list").first("*").count();
      ModelCollection* res = theQuery.within("root.sammy").after("online").get();
      ModelCollection r = (*res);
      std::cout << r << std::endl;
//      std::string theCount = theQuery.first("sammy").first("followers").get("count");

//      ModelQuery& m2 = m.first("follower");
//      size_t theCount=theQuery.first("sammy").after("list").count();
//      std::cout << std::stod("123.0") << std::endl;
//      double theSum=theQuery.first("sammy").after("list").sum("foo");
//      auto   *theSet =  theQuery.first("sammy").after("list").get();
       
      std::string theLine;
      CommandProcessor theProcessor;
//      theModel.print();
      
      bool isValid=true;
      while (std::getline(aCmdFile, theLine) && isValid) {
          if(theLine.size()) {
              isValid=theProcessor.run(theLine, theModel, output);
          }
      }

      return isValid;
    }
    
    Testing(std::ostream &anOutput) : output(anOutput){}
    
    std::ostream &output;

  };

}

#endif /* Testing_h */
