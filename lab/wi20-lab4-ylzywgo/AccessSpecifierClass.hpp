//
// Created by Savyasachi on 1/26/20.
//

#ifndef ACCESSSPECIFIERCLASS_H
#define ACCESSSPECIFIERCLASS_H


#include <iostream>

class Parent {
public:
    Parent(int arg1, int arg2, int arg3)
            : publicField(arg1), protectedField(arg2), privateField(arg3) {}

    void doPublicMethod() {std::cout<<"I'm public\n";}

    int publicField; //i'm a public variable

protected:
    void doProtectedMethod() {std::cout<<"I'm protected\n";}
    int protectedField; //i'm a protected variable

private:
    void doPrivateMethod() {std::cout<<"I'm private\n";}
    int privateField; //i'm a private variable

};

//play with variations of this subclass to see how different
//class access specifiers behave…


class Child : public Parent {
public:

    Child(int arg1, int arg2, int arg3)
            : Parent(arg1, arg2, arg3) {}

    void doSomething() {
        //what can we do here?
        publicField = 1;
        protectedField = 2;
        doPublicMethod();
        doProtectedMethod();
    }
};

class GrandChild : public Child {
public:

    GrandChild(int arg1, int arg2, int arg3)
            : Child(arg1, arg2, arg3) {}

    void doSomething() {
        //what can we do here?
        publicField = 1;
        protectedField = 2;
        doPublicMethod();
        doProtectedMethod();
    }
};


#endif //ACCESSSPECIFIERCLASS_H
