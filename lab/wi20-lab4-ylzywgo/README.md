# Lab #4 -- Due Tuesday, January 28, 9:00am

This assignment will help you gain some experience working with Conversion Constructors, Conversion Operators, Friend Functions and Access Specifiers. Each part requires that you write a small amount of code, and you watch that code execute (preferably in your browser). This lab should take roughly an hour or two to complete.

Let's say you are writing a service which returns some data which you query from a database. You are able to successfully fetch the data from the database and you store it in a object called `QueryResponse`. However, your service's expected response `ServiceResponse` is a bit different(Different in structure, field names etc.). The data is the same but the field names are different(`size` in `QueryResponse` & `length` in `ServiceResponse`) So you need some mechanism to convert `QueryResponse` tp `ServiceResponse` and vice-versa. You also have a `ResponsePrinter` class which is just a utility class that you use for logging. We'll use these classes to get a better understanding of the mentioned concepts.

## Part 1 - Conversion Constructors

Write Conversion Constructors for both `QueryResponse` and `ServiceResponse` in `Response.cpp`. Verify the following things in `main` class - 

1. Create an object of `QueryResponse` and use the conversion constructor to create an object `ServiceResponse` from it.
2. Create an object of `ServiceResponse` and use the conversion constructor to create an object `QueryResponse` from it.

## Part 2 - Conversion Operators

We can also use Conversion Operators instead of Conversion Constructors to achieve the same goal. Write Conversion Operators for both `QueryResponse` and `ServiceResponse` in `Response.cpp`. Verify the following things in `main` class - 

1. Create an object of `QueryResponse` and use the conversion operator to create an object `ServiceResponse` from it.
2. Create an object of `ServiceResponse` and use the conversion operator to create an object `QueryResponse` from it.

## Part 3 - Friend Functions and Classes

In order to get the `ResponsePrinter` class working, `ResponsePrinter` needs access to the private method `getResponse` of both  `QueryResponse` & `ServiceResponse` classes.

1. Make `ResponsePrinter` a friend of `QueryResponse` to get the `printQueryResponse` method working.
2. Use the concept of Friend Function to get the `printServiceResponse` working.
3. Verify that you are able to print both in your `main` class.

## Part 4 - Access Specifiers

In this part we'll use the provided `Parent`, `Child` & `GrandChild` classes to get a better understanding of access control. Try changing the Class Inheritance Specifier for the `Child` and report what all fields and methods you can access from the `Parent` class in both `Child` & `GrandChild`. You need not change the Class Inheritance Specifier for the `GrandChild` class. 

Report your experiment results in a text file which you should check in as part of your submission. It should contain the following details - 

* Class inheritance specifier of the `Child` class.
* Methods and fields accessible by the `Child` class.
* Methods and fields accessible by the `GrandChild` class.
 
 For example - one submission will have three such entries for `public`, `protected` & `private` 

```
Inheritance Specifier: public
Methods Accessible in Child Class: foo
Fields Accessible in Child Class: v1
Methods Accessible in GrandChild Class: foo, bar
Fields Accessible in GrandChild Class: v1, v3
```

## Turn in Lab 4 -- Due Tuesday, January 28, 9:00am

Make sure you fill out the students.json file with your personal information.  Then, check your lab work back into github.



