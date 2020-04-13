#### Part1D
> __Question__: Did you see an output statement related to your destructor?  Can you explain how/why your `Date` destructor was called?

Yes. Because Date birthday is a local variable in the curly bracket. So it will be destroyed when it goes out of the scope.

#### Part2B
> __Question__: Can you explain the logging output you're seeing in the terminal?  Why were the methods called in the order you see them?

Yes. Because we first create theDate1 and the create theDate2 by copy constructor. When it goes out of the scope, these two objects will be destoryed in the reverse order of they have being created.

#### Part3A
> __Question__: Did your destructor get called?  Explain why (or why not).

No. Because the object is allocated in heap, and will be in memory until program terminates(or called delete method). 