//
//  Searchable.hpp
//  Assignment3
//
//  Created by rick gessner on 1/29/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#ifndef Searchable_h
#define Searchable_h

  //This class is incomplete; students need to finish it...
  template <typename T>
  class Searchable {
  public:

    Searchable(T &aSelf) : self(aSelf) {
//        std::cout << "3333" << std::endl;
    }
    
    //add other OCF methods...
    Searchable& operator=(T &aSearch){
        self = aSearch;
        return *this;
    }

      //get a character from your string at a given index... 
    
    char& operator[](size_t aPos) const {
      static char temp = '\0';
      if (aPos < self.getLength() - 1)
          temp = self.getBuffer()[aPos];
      return temp;
    }
       
      //Find index of target (substring) in your string; return offset, or -1 if not found.    
     
    int find(const T &aTarget, size_t anOffset=0) const {
        const char* s = aTarget.getBuffer();
        return find(s, anOffset);
    }
    
    int find(const char *aBuffer, size_t anOffset=0) const {
      int aLen = 0;
      int selfLen = self.getLength() - 1;
      while (aBuffer[aLen]) aLen++;
      const char* selfBuffer = self.getBuffer();

//      std::cout << "aLen = " << aLen << std::endl;
//      std::cout << "selfLen = " << selfLen << std::endl;
//      std::cout << "anOffset = " << anOffset << std::endl;

      if (anOffset > selfLen - aLen) return -1;
      for (int i = anOffset; i <= selfLen - aLen; i++){
          char* s = new char[aLen];
          for (int j = 0; j < aLen; j++)
              s[j] = selfBuffer[j + i];
//          std::cout << "cur substring = " << s << std::endl;
//          std::cout << "aBuffer " << aBuffer << std::endl;
//          std::cout << strcmp(s, aBuffer) << std::endl;
//          std::cout << i << std::endl;
          if (strcmp(s, aBuffer) == 0) return i;
      }

      return -1;
    }
  protected:
    T& self;
  };

#endif /* Searchable_h */
