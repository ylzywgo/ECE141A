# WI20-Assignment2 - 
#### Due Jan 30, 2020 @ 11:15pm (PST)

Let's build our first object-oriented solution for ECE141! 

In this assignment, you'll develop skills around building your first set of classes that interact. You'll work with streams a little bit, and you'll learn to put objects on the heap with `operator new`.  This assignment may be bigger than you're used to -- but the actual tasks aren't really that time-consuming. Don't panic!  We're going to discuss how to approach this challenge more in class, and in the dojo.

## -- Welcome to TimeCo!

Congratuations -- welcome to TimeCo!  We're happy to see all the fresh faces of our newest employees. By now you have had your new-employee orientation, and you've learned where the parking lot, cafeteria, and restrooms are.  Not that that you'll have time to eat, use the restroom, or go home -- but hey, at least your a professional now! :)

![alt text](diagram.jpg "TimeCo!")

## -- Your First Assignment 

At TimeCo, every second counts, and that's why we want you to get started working on our new calendar application. We need to track every minute of every day, to make sure we're all being as productive as possible.  

Your job is to build version 1.0 of our little Calendar program.  This Calendar will track all of the tasks, and all of the meetings of every employee at TimeCo. To do that, your going to build the following classes:

### `Calendar` 

Each `Calendar` object will contain a collection of `Tasks` and `Meetings` for every employee for a given month. Of course, it wouldn't be a good day if we didn't have LOTS of meetings, and it can be difficult to find free time when two people can meet. So the `Calendar` class provides a method to search itself, and suggest a meeting time. Wow -- we ARE productive, aren't we?


### `DateTime` 

The `DateTime` class containss properties that describe one event (day and time). Each `DateTime` class contains a `month`, `day`, `year`, `hour`, and `minutes`. We expect you'll use the `DateTime` class when you're implementing the `Task` and `Meeting` class.  


### `Person` 

At TimeCo, a `Person` class contains information about each employee who has ever worked at TimeCo. We know a __great__ deal about every `Person` at TimeCo, and so this class contains many different properties, like `name, age, height, weight, IQ, shoe-size, favorite food` and MUCH much more.  However, for this assignment, a person will be represented by a `std::string` that contains their name.

### `Meeting` 

A `Meeting` is an event on the calendar when two people are working together at a particular time and place. 

### `Task` 

A `Task` is an event on the calendar where an individual has made a commitment to complete a work deliverable. Each `Task` has a name, a due-date (`DateTime`), and an owner (`string`).  

## Part 1  

In this part, you will get your classes ready for use, by implementing the four required methods:

- constructor
- copy constructor
- assignment operator
- destructor

We have provided starting code for all the your classes in this assignment, but it's up to you to make each of them declare and implement each of the methods listed above. 

## Part 2  -- Adding functionailty to the classes in this assignment

### Part 2A -- Implement the `DateTime` class

#### Data Members

The `DateTime` class needs the following data members.  All of them are integers:

```
  month, day, year, hour, mins
```

#### Methods

In addition to standard methods (OCF), the `DateTime` you need to add and implement the following methods on this class: 

```
bool      operator==(const DateTime &aCopy); //this is the comparison operator

bool      isValid(); //return true if all fields are within the valid range

DateTime& setMonth(int aValue);  //range: 1-12
DateTime& SetDay(int aValue);    //range: 1-31
DateTime& setYear(int aValue);   //range: 0-2050
DateTime& setHour(int aValue);   //range: 0-23 (military time)
DateTime& setMinutes(int aValue); //range: 0-59

int       getMonth() const;
int       getDay() const;
int       getYear() const;
int       getHour() const;
int       getMinutes() const;
```

### Part 2B -- Implement the `Task` class

In addition to standard methods (OCF), you need to add and implement the following methods on the `Task` class. Each of these methods either set or get a property on the current object. 

```
Task&         setDate(const DateTime &aDate);
Task&         setTitle(const std::string &aTitle);
Task&         setPerson(const std::string &aPerson);

DateTime&     getDate()  {return date;};
std::string&  getTitle()  {return title;};
std::string&  getPerson() ;
```    

A non-default constructor for the `Task` class is also required. Here's the definition. This method allows a caller to conveniently set all the properties on a `Task` at once.

```
  Task(const DateTime &aDT, const std::string &aTitle, const std::string &aPerson);
```

### Part 2C -- Implement the `Meeting` class

In addition to standard methods (OCF), this class needs the following methods: 

```
Meeting&     setDate(const DateTime &aDate);
Meeting&     setTitle(const std::string &aTitle);
Meeting&     setPerson(const std::string &aName, int aPersonNumber); //a little different than the Task class?

DateTime&    getDate() ;
std::string& getTitle() ;
std::string& getPerson(int aPersonNumber) ;
```

All of these methods either set or get a property on the current object. 

A non-default constructor for the `Meeting` class is also required. Here's the definition:

```
    Meeting(const DateTime &aDT, const std::string &aTitle,
            const std::string &aPerson1, const std::string &aPerson2);
```

### Part 2D -- Implement the `Calendar` class

In addition to standard methods (OCF), this class needs the following methods: 

```
    Calendar(int aMonth=1, int aYear=2020); //default ctor with default values...

    Calendar& addItem(DateTime *anItem);
    
    bool load(std::istream &anInputStream); //load tasks/meetings from a file
    
    int getMonth() const; //ask the calendar the month it represents
    int getYear() const; //ask the calendar what year it represents 
    int countItemsForDate(const DateTime &aDateTime) const; //how many items on a given date?
    int countTasks() const; //how many added items are tasks?
    int countMeetings() const; //how many added items are meetings?
      
    const Calendar& show(std::ostream &anOutput) const; //show a text-based version of full-month calendar (see below)
    const Calendar& showSummary(std::ostream &anOutput) const; //show a text-based version of items (see below)
     
     //find the first day/time that both calendar objects have a free hour (within the given time range)
    DateTime  firstAvailableHour(const Calendar &anOther, int startHour=0, int stopHour=0, const char *dow=nullptr) const;

    friend std::ostream & operator << (std::ostream &output, const Calendar &aCalendar);
```

#### firstAvailableHour() 

This method is special, and requires some explanation. Let's assume we have a shared calendar for January 2020, and both Rickg and Chandhini have Tasks and Meetings on that calendar. TimeCo thinks these two aren't having enough meetings, and so they insist on adding a new meeting to the shared calendar. The question is: when is the best time for their next meeting?

In order to find a best time, you have to search the calendar, and find a slot where both Rickg and Chandhini aren't already busy. Once yo you locate a slot, you can create the new meeting, and attach that to the calendar.  Of course, this gets more difficult (and time-consuming) when the Calendar gets more full. 

#### Show() 

When the show method is called, the calendar should show a grid (for the month). Each cell should contain the number of active items for that day:

```
|------------------------------------------------|
|  January 2020                                  |
|------------------------------------------------|
|  Su  |  Mo  |  Tu  |  We  |  Th  |  Fr  |  Sa  |
|------------------------------------------------|
|   2  |      |      |      |      |      |      |
|------------------------------------------------|
|      |  3   |      |      |      |      |      |
|------------------------------------------------|
|      |      |  4   |      |      |      |      |
|------------------------------------------------|
|      |      |      |      |      |      |      |
|------------------------------------------------|
|      |      |      |  1   |      |      |      |
|------------------------------------------------|
```

#### Summary() 

When the `summary()` method is called, the calendar should show a list of tasks and meetings, with related information:

```
|------------------------------------------------|
|  January 2020 Summary                          |
|------------------------------------------------|
|  Jan 4, 4p  | Task: homework1                  |
|------------------------------------------------|
|  Jan 5, 1p  | Mtg: Lunch                       |
|             | rickg, chandhini                 |
|------------------------------------------------|
```

#### load() 

This method has been partially written for you. It uses a `ifstream` and a `stringstream` to read each line of your input file, and parse the items into a local array. Your task is to turn that data into either a `Task` or a `Meeting`, and put on the calendar. 

Note: A given calendar will represent a only single month at a time. Therefore, you only add items from the file if the date of the given item matches the month reprsented by the calendar. Ignore the other items.

## Part 3 -- Testing 

This assignment include a simple testing framework to help you ensure that your code is working correctly. However, you are required to implement some of tests.  Open your `Testing.hpp` file, and you'll see this interface:

```
 class Testing  {
  public:
    
    Testing(std::ostream &anOutput) : output(anOutput) {}
    
    bool runTests();
    
  protected:
    std::ostream &output;
  };
```

The class is responsible for running a series of tests for the rest of your classes. It does that when you call the `runTests()` method. If you look inside the `Testing.cpp` file, you'll see that the `runTests()` method calls a series of local functions that perform individual tests:

```
bool Testing::runTests() {
    
    if(!testDateTime()) {
      output << "DateTime tests failed\n";
      return false;
    }

    if(!testTask()) {
      output << "Task tests failed\n";
      return false;
    }

    if(!testMeeting()) {
      output << "Meeting tests failed\n";
      return false;
    }

    if(!testCalendar()) {
      output << "Calendar tests failed\n";
      return false;
    }

    return true;
  }
```

When you first try to run this project, all of the tests will fail, because the code being tested hasn't been implemented yet.  As you finish working on your classes, the tests will being to pass, and eventually, they will all work.  Yay!

Note, however, that you are responsbile for writing some of your own tests, as described below.

#### --How to test a Method

The key to writing a test for a method, is to think about how an object will change after the method is executed. For example, if I call `Task::setTitle()`, the title property of that object will mutate when the call completes. So a valid test is to determine the current value of the object, call a method to change a value, then call a method to retreive the new value. You can then verify the object state has changed for that property in a meaningful and correct way.  

> Think about how you might test a "getter method" that retrieves a value from an object. (Ex: DateTime::getYear()). How do we know if this is working? Well, if you first call a method to set that property to a specific value, and _then_ get that same value from the object, you know the setter worked.

Another common technique (that we used in testing `DateTime`) is to compare two objects of the same type, after you make specific changes to one of them.  

Finally, recognize when you're testing, it's sometimes easier to verify whether an object does NOT match an expected state, than to try to prove that it does match that state.  In other words, a test for invalid state is a common practice.

### 3A - Testing DateTime

Your `DateTime` class tests are contained with the function, `testDateTime()` in the `Testing.cpp` file. We've written the first tests for you as an example.  Take a look at that code now to see how simple it is to write tests. Take a look at the `assertTrue` and `assertFalse` methods in particular. This is how you tell the testing tool whether you're testing something to be true or false, and how to report an error if you don't get the result you expect. 

### 3B -- Testing Task 

It's essential that you write a test for each method in each class, as defined above in Part 2B. Don't forget to write tests for your OCF methods too.

For example, `setDate` is expected to change the date for your `Task` to be equal to the given `DateTime` object. To test this method, you can call `getDate` on the `Task` object (it's current value), and _then_ call `setDate` to mutate the date property. Next, compare the original `DateTime` value of your `Task` against its current `DateTime` property. They should no longer match.  This is one of many ways to verify that your code is working as expected. 


### 3C -- Testing Meeting 

It's essential that you write a test for each method in each class, as defined above in Part 2C. Don't forget to write tests for your OCF methods too.

### 3D -- Testing Calendar

You want to write tests for each of the methods listed for this class in Part 2D.  

Testing the `addItem` method is tricky, because it needs to generate many records (Tasks and Meetings), and insert them all into the Calendar.  We've provided some starter code for you in the CalendarTest in the Testing.cpp file.  We've also provided you a "helper class" that can generate fake data you can use to make fake Task and Meeting objects to insert into your calendar for testing.  See `DataHelper.hpp`. 

Testing the `load()` method is fairly easy. The `load()` method is supposed to read items from a file, create associated `Task` and `Meeting` objects, and insert them into the calendar if the item month matches the calendar month. After the `load()` method finishes, you can ask the calendar how many objects it contains (it should not be zero).


## Turning in your work -- 
#### Due Jan 30, 2020 @ 11:15pm (PST)

Submitting your homework is a two-step process: one on github, and one on GradeScope.

First, when youre code is ready, check it all into github as usual. 

Second, go to Gradescope, and choose the assignment you are submitting from the UI. On the pop up window, choose github and link your github account if you haven't. Two drop down menus will appear and select your github repository for this assignment and your desired branch respectively. Finally, press submit to submit the assignment.

Good luck everyone!
