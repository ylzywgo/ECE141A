# WI20-Lab6
## - Due Tuesday, Feb 11, 10am (PST).


## Your Lab Assignment

In this (mid-term) lab, you will build a templatized class that can perform bit-wise operations on an object. Nearly all of the methods you will write are overloaded operators. Some of these operators can be implemented using other operators you have already implemented, so the challenge is smaller than it first appears.


```
template<typename T>
class Bitwise {
public:
  Bitwise(T aValue=0);

  Bitwise(const Bitwise &aCopy);   //copy ctor
  Bitwise&  operator=(const Bitwise &aCopy); 
  
  bool      operator==(const Bitwise& aCopy);  //compare two bitwise objects
  
  Bitwise&  setBit(size_t aBitNum, bool aValue); //set an individual bit at bitnum as on/off
  bool      getBit(size_t aBitNum);    //retrieve the value of a given bit (t/f)
  T         getValue(); //return current value
  
  //bitwise AND (&)
  Bitwise   operator&(const Bitwise& another);
  Bitwise&  operator&=(const Bitwise &another);
  
  //bitwise OR (|)
  Bitwise   operator|(const Bitwise& another);
  Bitwise&  operator|=(const Bitwise &another);
  
  //bitwise XOR
  Bitwise   operator^(const Bitwise& another);
  Bitwise&  operator^=(const Bitwise &another);
    
    //bitwise NOT (~)
  Bitwise   operator~();
  
  //left shift -- this is NOT used for streams!
  Bitwise   operator<<(size_t aCount);
  Bitwise&  operator<<=(size_t aCount);
  
  //right shift -- this is NOT use for streams!
  Bitwise   operator>>(size_t aCount);
  Bitwise&  operator>>=(size_t aCount);
  
protected:
   T bits;
};
```

> If there are any unexpected differences between the listing above and the Bitwise.hpp file in your project, assume the sourcecode is correct. 


### A Note about `operator<<` and `operator>>`

We introduced operator overloading in our first week, and we've been using it ever since. You learned to use `operator<<` and `operator>>` with `std::stream` classes.  As we've said before, a class is free to overload (nearly) any operator it wants, and decide for itself what that operator is supposed to do.

In the case of your `Bitwise` class for this lab, `operator<<` and `operator>>` and not used for streaming. Instead, the represent the bitwise operators "shift left" and "shift right". Please refer to the discussion (below), or your favorite online tutorial about bitwise operators. 

### Testing Your Code

Because your TA's like you very much, they have included a file called `BitwiseTester.hpp` in your project folder. This class helps with testing of your `Bitwise` class, and is called from your `main.cpp` file.  Yay!  

However -- they did leave two methods for you to implement:

```
template <typename T>
class BitwiseTester {

  //you have to implement these:

  void testShiftLeft() {
     //Student - implement this test!
  }

  void testShiftRight() {
     //STudent - implement this test!
  }

}
```

### What you can (and can't) do to finish this lab

Academic integrity matters. So as always, your work must be your own -- and you cannot copy code from anyone or any source. 

On the other hand, you're not alone. You're free to talk to your classmates about this assignment, to discuss issues you face writing this code. You can use the google machine for ideas, or get questions answered. (We provided some good links already).  You can also reference topics in your book(s).  Just remember that every line of code you write needs to be your own. Expect that at some point in the future, you might get asked to make changes to this code.  :)

### Submitting Your Assignment
#### - Due Tuesday, Feb 11, 10am (PST).

Post your updates to github, and link them to gradescope as usual.  Make sure your fill out your `student.json` file. 

---

## Review of Bitwise operators

Bitwise operators work on data by comparing or mutating individual bits, using logical notation (more on that in a moment). People often confuse bitwise operators with logical operators, because the language is similar. 

<blockquote>
  <div>Speaking of tutorials -- here are some really good ones:</div>
  <div>
    <ul> 
      <li>
        <a href='https://www.learncpp.com/cpp-tutorial/bitwise-operators/'> Bitwise operator tutorial </a>
      </li>
      <li>
        <a href='https://pmihaylov.com/bitwise-operations/'> Another bitwise operator tutorial </a>
      </li>
      <li>
        <a href='https://riptutorial.com/cplusplus/topic/2572/bit-operators'>
          Another Tutorial on Bitwise Ops           
        </a>
      </li>
    </ul>
  </div>
</blockquote>


### A sidebar about logical operators

For example, consider the logical `AND` operator.  Given two `boolean` values, we can use conditional logic to say:
```
if(this AND that) {
  //do this code of both conditions are true
}
```

### Bitwise AND example

Most bitwise operators use logic to derive bits in a compute data field from two other operands. The exception is the ~ operator (NOT), which is a unary operator (no arguments). Let's look at the bitwise `AND` operator.  Let's consider what happens when we apply bit-wise `AND` to two 8-bit integers:

```
Apply logical AND to each pair of bits:

A.      0000 0011 &
B.      0000 0010
------------------
Result  0000 0010
```

* R[0] = A[0] & B[0]=> (1 AND 0) = 0  (rightmost bit)
* R[1] = A[1] & B[1]=> (1 AND 1) = 1
* R[2] = A[2] & B[2]=> (0 AND 0) = 0
* R[3] = A[3] & B[3]=> (0 AND 0) = 0
* R[4] = A[4] & B[4]=> (0 AND 0) = 0
* R[5] = A[5] & B[5]=> (0 AND 0) = 0
* R[6] = A[6] & B[6]=> (0 AND 0) = 0
* R[7] = A[7] & B[7]=> (0 AND 0) = 0

### Bitwise OR example

Similarly for the bitwise `OR` operator, we compare bit by bit. If _either_ bit is set, the result is true (1):

```
Apply logical OR to each pair of bits:

A.      0000 0011 |
B.      0000 0010
------------------
Result  0000 0011
```

### Bitwise XOR example

For bitwise `XOR` operator, the result evaluates to 1 iif one of the operands is 1.

```
Apply logical XOR to each pair of bits:

A.      0000 0011 ^
B.      0000 0110
------------------
Result  0000 0101
```

* R[0] = A[0] ^ B[0]=> (1 XOR 0) = 1
* R[1] = A[1] ^ B[1]=> (1 XOR 1) = 0
* R[2] = A[2] ^ B[2]=> (0 XOR 1) = 1

### Bitwise ~ (not) example

The bitwise `NOT` operator is simple. It flips each bit from 0 to 1 or from 1 to 0. 
This is a unary operator (complement)

```
Apply logical ~ to each pair of bits:

        1111 1100 ~
------------------
Result  0000 0011
```

### Bitwise << (shift left) example

Don't confuse this bitwise shift left operator with the ostream operator `<<`. 
What this bitwise shift left operator does is shifting the bits to the left by x places.

```
Shift left 

        0011 << 1
-----------------
Result  0110

        0011 << 3
-----------------
Result  1000
```

Note that in the `0011 << 3` example, the 1 on the left side is shifted off the number.
This is information is lost forever.

### Bitwise >> (shift right) example

Similarly, we have bitwise shift right operator, which is different from the istream operator `>>`.
It shifts the bits to the right by x places.

```
Shift right 

        0110 >> 1
-----------------
Result  0011

        0110 >> 3
-----------------
Result  0000
```

When a bit is moved off the end, the information is lost forever.

