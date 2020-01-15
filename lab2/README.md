# Lab #2 -- Due Tuesday, January 14, 9:00am

This assignment will help you gain some experience working with objects, and to gain experience with the object lifecycle. Each part requires that you write a small amount of code, and you watch that code execute (preferably in your browser).  This lab should take about an hour to complete.

## Part 1 - Build and annotate simple class (practice with OCF)

#### Part 1A 

In this part, you're going to build a very simple `Date` class. Each `Date` object contains a month, day, and year property. Your class will have a method to set each of these properties, and you will implement operator<< so you can write your `Date` class to `std::cout`.  The template for your class is shown below.  Make sure to complete each of the standard methods too (constructor, copy-constructor, assignment operator, destructor)...

```
class Date {
public:
  Date(int aMonth, int aDay, int aYear) {
    //Student implement your CTOR
  }
  
  Date(const Date &aCopy) {
    //Student implement your COPY-CTOR
  } 
  
  ~Date() {
    //Student implement your DTOR
  }
  
  Date& operator=(const Date &aDate) {
    //Student implement your assignment operator
  }

  //STUDENT -- Add methods here (3) to set the month, day, year properties. 
  //           For example, create a method called "setMonth(int aMonth)" to set the month value...


  friend std::ostream& operator<<(std::ostream &aStream, Date &aDate) {
    //Student implement the stream inserter operator
  }

protected:
   //STUDENT: add the Date class data members here...
};
```

#### Part 1B Annotate each method using `std::cout`

For each of the methods on the `Student` class, add a "logging" statement. Do this by sending output to `std::cout` that indicates that you're executing code in that method (see example below). When your code runs, this logging statement will print output to the terminal that indicates that method is being executed. For example, you can log the `Date` constructor this way:

```
std::cout << "in Student-constructor()\n";  
```

Do this for the constructor, copy-constructor, destructor, assignment operator, and operator<<. Of course, change the text of the output message to indicate which method is being run. 

#### Part 1C 

In your `main()` function, create an object of type date, and initialize it with a reasonable value, like your birthday, or today's date. You'll do this inside a nested block for the purpose of testing -- and this is already setup for you like this:

```
int main() {
  //do part 1 inside this block...
  {
    std::cout << "Part1...\n";
    //Add your code for part 1 here...
  }
  //PUT A BREAKPOINT on the NEXT line of code, and run your program
  std::cout << "Part1 is done.\n";
}
```

#### Part 1D 

Next, in your IDE (or debugger), put a breakpoint on the line of code in `main()` that says, "std::cout << "main() is done".  Now run your program, and look at the output terminal. Your program should have output something like this:

```
In Date-constructor
...other output?...
```

> __Question__: Did you see an output statement related to your destructor?  Can you explain how/why your `Date` destructor was called?


## Part 2 - Clone exercise

If you've already implemented the `Date` methods, this part is very simple.  

#### Part 2A 

In your `main()` function, there is a block of code that reads, "Do part 2 inside this block".   In that block, declare an object of type `Date`, with the variable name, "theDate1".  

#### Part 2B

Next, declare another variable called "theDate2", and copy construct that object from "theDate1". 

```
int main() {
  
  //part 1 here...
  
  //Do part 2 inside this block...
  {
     std::cout << "Part2...\n";
    //Add your code for part2 here...
  }
  //PUT A BREAKPOINT on the NEXT line of code, and run your program
  std::cout << "Part 2 is done.\n";
    
}
```

> __Question__: Can you explain the logging output you're seeing in the terminal?  Why were the methods called in the order you see them?

## Part 3 - Lifespan exercise

This is the easiet part.  In Part1 and Part2 above, you experienced the lifecycle of simple objects. You created an object, and saw both the constructor and destructor for that object get called. Now we're going to try an experiment to see what happens to objects in different contexts. 

#### Part 3A 

Go to the block of code in your `main()` function that is labeled, "part3".  Inside that block, create a new object of type date, and use the new operator put the object on the heap like we discussed in class.  You can use any values you want to initialize this date object.

> __Question__: Did your destructor get called?  Explain why (or why not). 


## Turn in Lab 2 -- Due Tuesday, January 14 at 9a. 

Make sure you fill out the students.json file with your personal information.  Then, check your lab work back into github.



