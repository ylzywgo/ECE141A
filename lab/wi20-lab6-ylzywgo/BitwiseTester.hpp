//
// Created by Savyasachi on 2/9/20.
//

#include <string>
#include <iostream>
#include "Bitwise.hpp"

#ifndef BitwiseTester_h
#define BitwiseTester_h

namespace ECE141 {

    template<typename T>
    class BitwiseTester {

    public:
        void runTests() {
            testConstructor();
            testCopyConstructor();
            testAssignmentOperator();
            testEquals();
            testBitManipulation();
            testAnd();
            testOr();
            testXor();
            testNot();
            testShiftLeft();
            testShiftRight();
        }

    private:

        void testConstructor() {
            Bitwise<T> a(2);
            assertEquals("Constructor", a.getValue(), 2);
        }

        void testCopyConstructor() {
            Bitwise<T> a(97);
            Bitwise<T> copy(a);
            assertEquals("Copy Constructor", copy.getValue(), 97);
        }

        void testAssignmentOperator() {
            Bitwise<T> a(97);
            Bitwise<T> copy = a;
            assertEquals("Assignment Operator", copy.getValue(), 97);
        }

        void testEquals() {
            Bitwise<T> a(97);
            Bitwise<T> b(97);
            Bitwise<T> c(99);
            assertEquals("Equals Positive", a == b, true);
            assertEquals("Equals Negative", b == c, false);
        }

        // TODO: Add Your Tests Here. Test all possible cases for Shift Left and Shift Right operators
        void testShiftLeft() {
            Bitwise<T> a(97);
            Bitwise<T> b(194);
            assertEquals("Left Shift", a << 1 == b, true);
            a <<= 3;
            assertEquals("Left Shift Self", a.getValue() == 776, true);
            Bitwise<T> c(1);
            c <<= 32;
            assertEquals("Right Shift Self", c.getValue() == 1, true);
        }

        void testShiftRight() {
            Bitwise<T> a(97);
            Bitwise<T> b(24);
            assertEquals("Right Shift", a >> 2 == b, true);
            a >>= 5;
            assertEquals("Right Shift Self", a.getValue() == 3, true);
            Bitwise<T> c(6);
            c >>= 3;
            assertEquals("Right Shift Self", c.getValue() == 0, true);
        }

        void testAnd() {
            Bitwise<T> a(43);
            Bitwise<T> b(90);
            Bitwise<T> c = a & b;
            assertEquals("And Operator", c.getValue(), 10);
            assertEquals("And Operator Self", a.getValue(), 43);

            Bitwise<T> d(43);
            d &= b;
            assertEquals("And Operator Self", d.getValue(), 10);
        }

        void testOr() {
            Bitwise<T> a(43);
            Bitwise<T> b(90);
            Bitwise<T> c = a | b;
            assertEquals("Or Operator", c.getValue(), 123);
            assertEquals("Or Operator Self", a.getValue(), 43);

            Bitwise<T> d(43);
            d |= b;
            assertEquals("Or Operator Self", d.getValue(), 123);
        }

        void testXor() {
            Bitwise<T> a(43);
            Bitwise<T> b(90);
            Bitwise<T> c = a ^b;
            assertEquals("XOr Operator", c.getValue(), 113);
            assertEquals("XOr Operator Self", a.getValue(), 43);

            Bitwise<T> d(43);
            d ^= b;
            assertEquals("XOr Operator Self", d.getValue(), 113);
        }

        void testNot() {
            Bitwise<T> a(43);
            Bitwise<T> b = ~a;
            assertEquals("Not Operator", b.getValue(), -44);
            assertEquals("Not Operator Self", a.getValue(), 43);
        }

        void testBitManipulation() {
            Bitwise<T> a(43);
            bool bit = a.getBit(0);
            assertTrue("Get Bit", bit);

            bit = a.getBit(2);
            assertFalse("Get Bit", bit);

            a.setBit(2, true);
            bit = a.getBit(2);
            assertTrue("Set Bit", bit);

            a.setBit(0, false);
            bit = a.getBit(0);
            assertFalse("Set Bit", bit);
        }

        void assertTrue(std::string testName, bool returned) {
            assertEquals(testName, returned, true);
        }

        void assertFalse(std::string testName, bool returned) {
            assertEquals(testName, returned, false);
        }

        void assertEquals(std::string testName, T returned, T expected) {
            if (expected == returned) {
                std::cout << "Test: " << testName << " Passed\n";
            } else {
                std::cout << "Test: " << testName << " Failed. Expected value was " << expected << ", But " << returned
                          << " was returned \n";
            }
        }
    };
}


#endif //LAB_6_BITWISETESTER_H
