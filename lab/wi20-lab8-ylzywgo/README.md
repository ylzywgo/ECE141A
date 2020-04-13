# WI20-Lab8
## - Due Tuesday, Feb 25, 10am (PST).


## Objectives 
The C++ STL (Standard Template Library) is a powerful set of C++ template classes to provide general-purpose classes and functions with templates that implement many data structures like vectors, lists, queues, and stacks. By the end of this lab, You will understand that iterators must be tied to a specific container class. Algorithms are implemented as a function that operates using iterators. That is, algorithms operate through iterators directly on values not affecting the structure of the container. 

In this lab, you will practice building containers using STL and apply algorithms on it. Specifically you will be working with two containers - Vector and List. You will implement the functions in each of the class using iterators and Algorithms provided by STL.

### Finishing the Vector and List Class
We have initialized your vector and list container with the user's input. Before we can proceed, you are required to implement the _incomplete_ methods in the both the classes:

`is_equal` :  Return True if the containers are equal to each other.  
`Print_elements` : print the elements of the container to std::cout by traversing them using iterators.  
`multiple_of_five` : Find if the elements of the container are multiples of 5. Your function should return 1 if all the elements are multiple of 5, return 0 if any of the elements are a multiple of 5 or return -1 if none of the elements are a multiple of 5.  
`element_n(int n)`: Return the nth element from the begining of the container. if 'n' is beyond the size of the container, you should return -1.  
`min_max()` : Return the minimum element in the container.  
`sortedcontainer()`: Sort the container and return it.  
`match_count(int n)`: Return the number of elements in the container that are equal to n.  

### Submitting Your Assignment
#### - Due Tuesday, Feb 25, 10am (PST).

Post your updates to github, and link them to gradescope as usual.  Make sure your fill out your `student.json` file. 

### Review of STL
- http://www.cplusplus.com/reference/stl/
