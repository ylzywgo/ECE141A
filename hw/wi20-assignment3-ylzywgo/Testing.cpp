//
//  Testing.cpp
//  Assignment2
//
//  Created by rick gessner on 1/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#include "Testing.hpp"
#include "String.hpp"
#include <string>
#include "Timer.hpp"
#include <string>
#include <iostream>


namespace ECE141 {
  
  //test your ctor(), dtor(), operator=, etc...
  bool testBasicMethods(Testing &aTester) {
      bool testResult = true;
      const char* c = "abc";
      String s="abc";
      String s1("abc", 2);
      String s22(c);
      String s11(s22, 2);

      aTester.getOutput() << "Basic Method Testing...\n"
                          << "-------------------------\n";

      std::string ss = "abc";
      std::string ss1 = "ab";

      if (!aTester.assertTrue("getBuffer method test", s.getBuffer() == ss)){
          testResult = false;
      }

      if (!aTester.assertTrue("getBuffer method test 2", s22.getBuffer() == ss)){
          testResult = false;
      }

      if (!aTester.assertTrue("getBuffer method test with ctr of char and presize", s1.getBuffer() == ss1)){
          testResult = false;
      }

      if (!aTester.assertTrue("getBuffer method test with ctr of string and presize", s11.getBuffer() == ss1)){
          testResult = false;
      }

      if (!aTester.assertTrue("[] method test", s[0] == 'a')){
          testResult = false;
      }

      if (!aTester.assertTrue("getLength method test", s.getLength() == 4)){
          testResult = false;
      }

      String s2 = s;
      if (!aTester.assertTrue("getLength method test with operator =", s2.getLength() == 4)){
          testResult = false;
      }

      String insert = "insert";
      s.insert(1, insert);
      std::string new_insert = "ainsertbc";
      if (!aTester.assertTrue("insert method test 1", s.getBuffer() == new_insert)){
          testResult = false;
      }

      s.insert(8, insert, 3);
      std::string new_insert2 = "ainsertbinsc";
      if (!aTester.assertTrue("insert method test 2", s.getBuffer() == new_insert2)){
          testResult = false;
      }

      const char* ch = "test";
      s.insert(12, ch);
      std::string new_insert3 = "ainsertbinsctest";
      if (!aTester.assertTrue("insert method test 3", s.getBuffer() == new_insert3)){
          testResult = false;
      }

      s.insert(12, ch, 2);
      std::string new_insert4 = "ainsertbinsctetest";
      if (!aTester.assertTrue("insert method test 4", s.getBuffer() == new_insert4)){
          testResult = false;
      }

      s.insert(12, 't');
      std::string new_insert5 = "ainsertbinscttetest";
      if (!aTester.assertTrue("insert method test 5", s.getBuffer() == new_insert5)){
          testResult = false;
      }

      s.replace(1, "replace");
      std::string new_replace1 = "areplaceinscttetest";
      if (!aTester.assertTrue("replace method test 1", s.getBuffer() == new_replace1)){
          testResult = false;
      }

      s.replace(8, "replace", 2);
      std::string new_replace2 = "areplacerescttetest";
      if (!aTester.assertTrue("replace method test 2", s.getBuffer() == new_replace2)){
          testResult = false;
      }

      s.replace(1, insert);
      std::string new_replace3 = "ainserterescttetest";
      if (!aTester.assertTrue("replace method test 1", s.getBuffer() == new_replace3)){
          testResult = false;
      }

      s.replace(8, insert, 2);
      std::string new_replace4 = "ainserteinscttetest";
      if (!aTester.assertTrue("replace method test 2", s.getBuffer() == new_replace4)){
          testResult = false;
      }

      s.erase(1, 12);
      std::string new_erase = "atetest";
      if (!aTester.assertTrue("erase method test", s.getBuffer() == new_erase)){
          testResult = false;
      }

      s += insert;
      std::string new_add1 = "atetestinsert";
      if (!aTester.assertTrue("+= method test 1", s.getBuffer() == new_add1)){
          testResult = false;
      }

      s += "ins";
      std::string new_add2 = "atetestinsertins";
      if (!aTester.assertTrue("+= method test 2", s.getBuffer() == new_add2)){
          testResult = false;
      }

      std::cout << "test << output: " << s  << " = " << new_add2 << std::endl;

      return testResult;
  }

  //Add tests to deal with Searchable<> interface...
  bool testSearchMethods(Testing &aTester) {
      bool testResult = true;

      aTester.getOutput() << "Searchable Method Testing...\n"
                          << "-------------------------\n";

      String s("super junior is super best");
      String ss("super");

      if (!aTester.assertTrue("index method test 1", s[0] == 's')){
          testResult = false;
      }


      if (!aTester.assertTrue("index method test 2", s[30] == '\0')){
          testResult = false;
      }

      if (!aTester.assertTrue("find method String test 1", s.find(ss, 0) == 0)){
          testResult = false;
      }
      if (!aTester.assertTrue("find method String test 2", s.find(ss, 6) == 16)){
          testResult = false;
      }
      if (!aTester.assertTrue("find method String test 3", s.find(ss, 16) == 16)){
          testResult = false;
      }
      if (!aTester.assertTrue("find method String test 4", s.find(ss, 17) == -1)){
          testResult = false;
      }
      if (!aTester.assertTrue("find method String test 5", s.find(ss, -1) == -1)){
          testResult = false;
      }
      if (!aTester.assertTrue("find method String test 6", s.find(ss, 25) == -1)){
          testResult = false;
      }

      if (!aTester.assertTrue("find method char test 1", s.find("super", 0) == 0)){
          testResult = false;
      }
      if (!aTester.assertTrue("find method char test 2", s.find("super", 6) == 16)){
          testResult = false;
      }
      if (!aTester.assertTrue("find method char test 3", s.find("super", 16) == 16)){
          testResult = false;
      }
      if (!aTester.assertTrue("find method char test 4", s.find("super", 17) == -1)){
          testResult = false;
      }
      if (!aTester.assertTrue("find method char test 5", s.find("super", -1) == -1)){
          testResult = false;
      }
      if (!aTester.assertTrue("find method char test 6", s.find("super", 25) == -1)){
          testResult = false;
      }


    return testResult;
  }

  /*
   *  This won't compile at first, because your String class is incomplete!
   *  Once your string class is sortable, you can test relational operators.
   */
  bool testRelationalMethods(Testing &aTester) {
      bool testResult = true;

      aTester.getOutput() << "Relationship Methods Testing...\n"
                          << "-------------------------\n";

      String a11 = "abc";
      String b11 = "acb";
      String c11 = "abc";
      String d11 = "aac";
      if (!aTester.assertTrue("< method test with String", a11 < b11)){
          testResult = false;
      }
      if (!aTester.assertFalse("< method test with String 2", a11 < c11)){
          testResult = false;
      }
      if (!aTester.assertFalse("< method test with String 3", a11 < d11)){
          testResult = false;
      }

      char* b12 = "acb";
      char* c12 = "abc";
      char* d12 = "aac";

      if (!aTester.assertTrue("< method test with char", a11 < b12)){
          testResult = false;
      }
      if (!aTester.assertFalse("< method test with char 2", a11 < c12)){
          testResult = false;
      }
      if (!aTester.assertFalse("< method test with char 3", a11 < d12)){
          testResult = false;
      }

      String a21 = "abc";
      String b21 = "acb";
      String c21 = "abc";
      String d21 = "aac";
      if (!aTester.assertTrue("<= method test with String", a21 <= b21)){
          testResult = false;
      }
      if (!aTester.assertTrue("<= method test with String 2", a21 <= c21)){
          testResult = false;
      }
      if (!aTester.assertFalse("<= method test with String 3", a21 <= d21)){
          testResult = false;
      }

      char* b22 = "acb";
      char* c22 = "abc";
      char* d22 = "aac";

      if (!aTester.assertTrue("<= method test with char", a21 <= b22)){
          testResult = false;
      }
      if (!aTester.assertTrue("<= method test with char 2", a21 <= c22)){
          testResult = false;
      }
      if (!aTester.assertFalse("<= method test with char 3", a21 <= d22)){
          testResult = false;
      }

      String a31 = "abc";
      String b31 = "acb";
      String c31 = "abc";
      String d31 = "aac";
      if (!aTester.assertFalse("> method test with String", a31 > b31)){
          testResult = false;
      }
      if (!aTester.assertFalse("> method test with String 2", a31 > c31)){
          testResult = false;
      }
      if (!aTester.assertTrue("> method test with String 3", a31 > d31)){
          testResult = false;
      }

      char* b32 = "acb";
      char* c32 = "abc";
      char* d32 = "aac";

      if (!aTester.assertFalse("> method test with char", a31 > b32)){
          testResult = false;
      }
      if (!aTester.assertFalse("> method test with char 2", a31 > c32)){
          testResult = false;
      }
      if (!aTester.assertTrue("> method test with char 3", a31 > d32)){
          testResult = false;
      }

      String a41 = "abc";
      String b41 = "acb";
      String c41 = "abc";
      String d41 = "aac";
      if (!aTester.assertFalse(">= method test with String", a41 >= b41)){
          testResult = false;
      }
      if (!aTester.assertTrue(">= method test with String 2", a41 >= c41)){
          testResult = false;
      }
      if (!aTester.assertTrue(">= method test with String 3", a41 >= d41)){
          testResult = false;
      }

      char* b42 = "acb";
      char* c42 = "abc";
      char* d42 = "aac";

      if (!aTester.assertFalse(">= method test with char", a41 >= b42)){
          testResult = false;
      }
      if (!aTester.assertTrue(">= method test with char 2", a41 >= c42)){
          testResult = false;
      }
      if (!aTester.assertTrue(">= method test with char 3", a41 >= d42)) {
          testResult = false;
      }

      String a51 = "abc";
      String b51 = "acb";
      String c51 = "abc";
      if (!aTester.assertFalse("== method test with String", a51 == b51)){
          testResult = false;
      }
      if (!aTester.assertTrue("== method test with String 2", a51 == c51)){
          testResult = false;
      }

      char* b52 = "acb";
      char* c52 = "abc";

      if (!aTester.assertFalse("== method test with char", a51 == b52)){
          testResult = false;
      }
      if (!aTester.assertTrue("== method test with char 2", a51 == c52)){
          testResult = false;
      }

      String a61 = "abc";
      String b61 = "acb";
      String c61 = "abc";
      if (!aTester.assertTrue("!= method test with String", a61 != b61)){
          testResult = false;
      }
      if (!aTester.assertFalse("!= method test with String 2", a61 != c61)){
          testResult = false;
      }

      char* b62 = "acb";
      char* c62 = "abc";

      if (!aTester.assertTrue("!= method test with char", a61 != b62)){
          testResult = false;
      }
      if (!aTester.assertFalse("!= method test with char 2", a61 != c62)){
          testResult = false;
      }

      return testResult;
  }

  //-----------------------------------
  //Test all the datetime methods...
  bool testString(Testing &aTester) {

    if(testBasicMethods(aTester)) {
      if(testRelationalMethods(aTester)) {
        if(testSearchMethods(aTester)) {
          return true;
        }
      }
    }
    
    return false;
  }


  void runSpeedTest(std::ostream &anOutput) {
    ECE141::Timer theTimer;
    theTimer.start();

//      UNCOMMENT THIS WHEN YOUR STRING CLASS WORKS!

      String temp("this is a block that gets reused");
      anOutput << "\nTesting String class performance...\n";
      for(int i=0;i<90000;i++) {
        {
          String theString("hello world");
//          std::cout << "1 " << theString << std::endl;
          theString+=temp;
//          std::cout << "2 " << theString << std::endl;
          theString+=temp;
//          std::cout << "3 " << theString << std::endl;
          for(int j=0;j<3;j++) {
            theString.insert(10,temp);
//            std::cout << "4 " << theString << std::endl;
            theString+=(temp);
//            std::cout << "5 " << theString << std::endl;
            theString.erase(30,10);
//            std::cout << "6 " << theString << std::endl;
          }
//          std::cout << "6" << theString << std::endl;
          String theOther(theString);
        }
      }
      theTimer.stop();
      anOutput << "elapsed time " << theTimer.elapsed() << "\n";

      std::string temp2("this is a block that gets reused");
      anOutput << "\nTesting std::string class performance...\n";
      for(int i=0;i<90000;i++) {
          {
              std::string theString("hello world");
              theString += temp2;
              theString+=temp2;
              for(int j=0;j<3;j++) {
                  theString.insert(10,temp2);
                  theString += (temp2);
                  theString.erase(30,10);
              }
              std::string theOther(theString);
          }
      }
      theTimer.stop();
      anOutput << "elapsed time of std string " << theTimer.elapsed() << "\n";
  }

  //----------- this is the test controller ---------------
  
  bool Testing::assertTrue(const char *aMessage, bool aValue) {
    static const char* theMsgs[]={"OK\n","FAIL\n"};
    output << "\t" << aMessage << " " << theMsgs[!aValue];
    return aValue;
  }

  bool Testing::assertFalse(const char *aMessage, bool aValue) {
    static const char* theMsgs[]={"OK\n","FAIL\n"};
    output << "\t" << aMessage << " " << theMsgs[aValue];
    return false==aValue;
  }

  //This is the main test function...
  bool Testing::runTests() {
    
    output << "\nTesting String class...\n";
    output << "-------------------------\n";
    if(!testString(*this)) {
      output << "String tests failed\n";
      return false;
    }

    runSpeedTest(output);

    return true;
  }

}
