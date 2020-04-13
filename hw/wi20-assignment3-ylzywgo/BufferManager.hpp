//
//  BufferManager.hpp
//  Assignment3
//
//  Created by rick gessner on 1/29/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#ifndef BufferManager_h
#define BufferManager_h

#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

namespace ECE141 {
  
  template <typename T>
  class BufferManager {
  public:
    BufferManager() : buffer(nullptr), length(0), capacity(0) {
    }

    BufferManager(const BufferManager &aCopy) {
        length = aCopy.length;
        capacity = aCopy.capacity;
        buffer = new char[capacity];
//        buffer = (char*)malloc(capacity);
        strcpy(buffer, aCopy.buffer);
    }

    BufferManager(const char* aBuffer) {
        length = 0;
        while (aBuffer[length]) length++;
        length += 1;
        capacity = length * 1.5;
        buffer = new char[capacity];
//        buffer = (char*)malloc(capacity);
        strcpy(buffer, aBuffer);
        buffer[length - 1] = '\0';
//        std::cout << (buffer == aBuffer) << std::endl;
    }

    BufferManager& operator=(const BufferManager &aCopy) {
        length = aCopy.length;
        capacity = aCopy.capacity;
        resize(aCopy.buffer, length);
//        buffer = new char[capacity];
//        buffer = (char*)malloc(capacity);
//        strcpy(buffer, aCopy.buffer);
        return *this;
    }

    BufferManager& operator=(const char* aBuffer) {
        length = 0;
        while (aBuffer[length]) length++;
        length += 1;
        capacity = length * 1.5;
        resize(aBuffer, length);
//        buffer = new char[capacity];
//        buffer = (char*)malloc(capacity);
//        strcpy(buffer, aBuffer);

        return *this;
    }

    //Add methods here to manage your buffer
    //YOU decide what methods to make...

    BufferManager& insert(const char* aBuffer, size_t len, size_t pos) {
        int newLength = length + len;
//        std::cout << "1111" << std::endl;
//        std::cout << newLength << std::endl;

        resize(buffer, newLength);

//        char* newBuffer = new char[newLength];
//        int i = 0;
//        for (; i < pos; i++) newBuffer[i] = buffer[i];
        for (int i = length - 1; i >= pos; i--) {buffer[i + len] = buffer[i];}
        for (int i = pos; i < len + pos; i++) buffer[i] = aBuffer[i - pos];

        buffer[newLength - 1] = '\0';

        return *this;
    }

      BufferManager& deletion(size_t len, size_t pos) {
//          std::cout << "delete" << std::endl;
          int newLength = length - len;
          if (newLength < 0) throw ("too more deletion");

//          char* newBuffer = new char[newLength];
          int i = pos;
//          for (; i < pos; i++) {newBuffer[i] = buffer[i];}
          for (; i < newLength - 1; i++) {buffer[i] = buffer[i + len];}
          for (; i < length - 1; i++) buffer[i] = '\0';
//          newBuffer[newLength - 1] = '\0';

          length = newLength;
//          strcpy(buffer, newBuffer);


          return *this;
      }
      ~BufferManager() {
//        delete buffer;
      }


    size_t getLength() {return length;}

  protected:
    size_t  length;
    T*      buffer;
    size_t capacity;

    BufferManager& resize(const char* aBuffer, size_t aNewLength, bool aRelease=false) {
        length = aNewLength;
        capacity = length * 1.5;

        char* temp = new char[capacity];
        strcpy(temp, aBuffer);

        delete[](buffer);
        buffer = new char[capacity];
        strcpy(buffer, temp);

        if (aRelease) delete[] aBuffer;

        return *this;
    }
               
  };

}

#endif /* BufferManager_h */
