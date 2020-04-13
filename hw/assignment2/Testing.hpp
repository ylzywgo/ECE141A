//
//  Testing.hpp
//  Assignment2
//
//  Created by rick gessner on 1/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#ifndef Testing_hpp
#define Testing_hpp

#include <stdio.h>
#include <iostream>

namespace ECE141 {

  class Testing  {
  public:
    
    Testing(std::ostream &anOutput) : output(anOutput) {}
    bool runTests();
    
    bool assertTrue(const char* aMessage, bool aValue);
    bool assertFalse(const char* aMessage, bool aValue);

    std::ostream& getOutput() {return output;}

    bool fail(const char* aMessage);
    bool succeed(const char* aMessage);

  protected:
    std::ostream &output;
  };

}

#endif /* Testing_hpp */
