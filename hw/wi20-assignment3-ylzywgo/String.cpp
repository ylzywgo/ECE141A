//
//  String.cpp
//  Assignment3
//
//  Created by rick gessner on 1/29/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#include "String.hpp"

namespace ECE141 {

  String::String(const String &aString, size_t aPresize)
    : BufferManager<char>(aString), Sortable(*this),Searchable(*this)  {
      if (aPresize!=0){
//          std::cout << "ss" << std::endl;
          deletion(length - 1 - aPresize, aPresize);
      }
  }

  String::String(const char* aBuffer, size_t aPresize)
    : BufferManager<char>(aBuffer), Sortable(*this), Searchable(*this) {
      if (aPresize!=0){
//          std::cout << "sss" << std::endl;
          deletion(length - 1 - aPresize, aPresize);
      }
  }

  String& String::operator=(const String &aString){
//      std::cout << "abc" << std::endl;
      deletion(length-1, 0);
      insert(0, aString);

      return *this;
  }

  char& String::operator[](int pos){
      return buffer[pos];
  }

  String& String::insert(size_t aPos, const String &aString, size_t aMaxCopyLen){
      // -1 because the length of string counted '\0', but we don't need that
      size_t len = aString.length - 1;
      if (aMaxCopyLen == 0) aMaxCopyLen = len;
      if (aMaxCopyLen > len) throw("too large maxCopyLen");
      else{
          BufferManager::insert(aString.buffer, aMaxCopyLen, aPos);
      }

      return *this;
  }

  String& String::insert(size_t aPos, const char *aBuffer, size_t aMaxCopyLen){
      size_t len = 0;
      while (aBuffer[len]) len++;
      if (aMaxCopyLen == 0) aMaxCopyLen = len;
      if (aMaxCopyLen > len) throw("too large maxCopyLen");
      else{
          BufferManager::insert(aBuffer, aMaxCopyLen, aPos);
      }

      return *this;
  }

  String& String::insert(size_t aPos, const char aChar){
      char* buf = new char [1];
      buf[0] = aChar;
      BufferManager::insert(buf, 1, aPos);

      return *this;
  }

  String& String::replace(size_t aPos, const String &aString, size_t aMaxCopyLen){
      size_t len = aString.length - 1;
      if (aMaxCopyLen == 0) aMaxCopyLen = len;
      if (aPos + aMaxCopyLen >= length || aMaxCopyLen > len){
          throw ("too large maxCopyLen");
      }
      else{
          BufferManager::deletion(aMaxCopyLen, aPos);
          BufferManager::insert(aString.buffer, aMaxCopyLen, aPos);
      }

      return *this;
  }

  String& String::replace(size_t aPos, const char *aBuffer, size_t aMaxCopyLen){
      size_t len = 0;
      while (aBuffer[len]) len++;
      if (aMaxCopyLen == 0) aMaxCopyLen = len;
      if (aPos + aMaxCopyLen >= length || aMaxCopyLen > len){
          throw ("too large maxCopyLen");
      }
      else{
          BufferManager::deletion(aMaxCopyLen, aPos);
          BufferManager::insert(aBuffer, aMaxCopyLen, aPos);
      }

      return *this;
  }

  String& String::operator+=(const String &aString){
      size_t len = aString.length - 1;
      BufferManager::insert(aString.buffer, len, length - 1);

      return *this;
  }

  String& String::operator+=(const char *aBuffer){
      size_t len = 0;
      while (aBuffer[len]) len++;
      BufferManager::insert(aBuffer, len, length - 1);

      return *this;
  }

  String& String::erase(size_t aPos, size_t aLength){
      if (aPos + aLength >= length) throw ("too large length");
      BufferManager::deletion(aLength, aPos);

      return *this;
  }

  std::ostream& operator<<(std::ostream &out, const String &aStr){
      for (int i = 0; i < aStr.length - 1; i++)
          out << aStr.buffer[i];

      return out;
  }
  std::istream& operator>>(std::istream &in,  String &aString){
      for (int i = 0; i < aString.length - 1; i++)
          in >> aString.buffer[i];

      return in;
  }
}
