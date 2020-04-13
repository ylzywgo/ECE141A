//
//  String.hpp
//  Assignment3
//
//  Created by rick gessner on 1/29/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#ifndef String_hpp
#define String_hpp

#include <stdio.h>
#include <iostream>
#include "BufferManager.hpp"
#include "Searchable.hpp"
#include "Sortable.hpp"

namespace ECE141 {

  class String : public BufferManager<char>,  public Sortable<String>, public Searchable<String>  {   //CRTP?
  public:

    String(const String &aString, size_t aPresize=0);
    String(const char* aBuffer, size_t aPresize=0);
            
    //add other OCF methods...
    String& operator=(const String &aString);
    
    //mutation methods...
    char&      operator[](int pos);
    
      //Insert methods let you insert a sub-string into another string ... 
    
    String&    insert(size_t aPos, const String &aString, size_t aMaxCopyLen=0);
    String&    insert(size_t aPos, const char *aBuffer, size_t aMaxCopyLen=0);
    String&    insert(size_t aPos, const char aChar);

      //Replace methods let you overwrite portions of a string with a given sub-string...

    String&    replace(size_t aPos, const String &aString, size_t aMaxCopyLen=0);
    String&    replace(size_t aPos, const char *aBuffer, size_t aMaxCopyLen=0);
              
      //operator+= is the "append" action, attaching the given string to end of your string...
    
    String&    operator+=(const String &aString);
    String&    operator+=(const char *aBuffer);

      //Erase "cuts" N characters from the middle of a string, starting a aPos
    String&    erase(size_t aPos, size_t aLength);
    
    const char* getBuffer() const {return buffer;}
      
      //read/write your string to an iostream
    
    friend std::ostream& operator << (std::ostream &out, const String &aStr);
    friend std::istream& operator >> (std::istream &in,  String &aString);
  };
  
}

#endif /* String_hpp */
