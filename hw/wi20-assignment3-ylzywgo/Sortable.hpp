//
//  Sortable.hpp
//  Assignment3
//
//  Created by rick gessner on 1/29/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#ifndef Sortable_h
#define Sortable_h

namespace ECE141 {
    
  //This class is incomplete; students need to finish it...
    
  template <typename T>
  class Sortable {
  public:

    Sortable(T &aSelf) : self(aSelf) {
//        std::cout << "4444" << std::endl;
    }  //CRTP?

    //add other OCF methods....
    Sortable& operator=(T &aSort){
        self = aSort;
        return *this;
    }
    
    bool operator<(const T &aComp) const {
        const char* s = aComp.getBuffer();
        return operator<(s);
    }
    bool operator<(const char *aBuffer) const {
        const char* s = self.getBuffer();
        return (strcmp(s, aBuffer) < 0);
    }
        
    bool operator<=(const T &aComp) const {
        const char* s = aComp.getBuffer();
        return operator<=(s);
    }
    bool operator<=(const char *aBuffer) const {
        const char* s = self.getBuffer();
        return (strcmp(s, aBuffer) <= 0);
    }
    
    bool operator>(const T &aComp) const {
        const char* s = aComp.getBuffer();
        return operator>(s);
    }
    bool operator>(const char *aBuffer) const {
        const char* s = self.getBuffer();
        return (strcmp(s, aBuffer) > 0);
    }
    
    bool operator>=(const T &aComp) const {
        const char* s = aComp.getBuffer();
        return operator>=(s);
    }
    bool operator>=(const char *aBuffer) const {
        const char* s = self.getBuffer();
        return (strcmp(s, aBuffer) >= 0);
    }
    
    bool operator==(const T &aComp) const {
        const char* s = aComp.getBuffer();
        return operator==(s);
    }
    bool operator==(const char *aBuffer) const {
        const char* s = self.getBuffer();
        return (strcmp(s, aBuffer) == 0);
    }
    
    bool operator!=(const T &aComp) const {
        const char* s = aComp.getBuffer();
        return operator!=(s);
    }
    bool operator!=(const char *aBuffer) const {
        const char* s = self.getBuffer();
        return (strcmp(s, aBuffer) != 0);
    }
    
  protected:
    T& self;  //The CRTP?    
  };

}

#endif /* Sortable_h */
