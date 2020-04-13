//
//  main.cpp
//  Lab8
//
//

#include <iostream>
#include <vector>
#include <list>
#include <sstream> 
#include <string> 
#include "VectorClass.hpp"
#include "ListClass.hpp"

int main(){
    vector<int> vec1, vec2;
    string line;
    std::cout<<"Enter the elements for vector 1"<<endl;
    if (getline(cin, line)) {
        istringstream is(line);
        int i;
        while (is >> i) {
            vec1.push_back(i);
        }
    }

    std::cout<<"Enter the elements for vector 2"<<endl;
    if (getline(cin, line)) {
        istringstream is(line);
        int i;
        while (is >> i) {
            vec2.push_back(i);
        }
    }

    VectorClass vec_object(vec1, vec2);
    vec_object.print_elemets();
    std::cout << vec_object.element_n(1) << std::endl;
    std::cout << vec_object.is_equal() << std::endl;
    std::cout << vec_object.min_max() << std::endl;
    std::cout << vec_object.multiple_of_five() << std::endl;

    vector<int> sorted = vec_object.sortedcontainer();
    for (int i = 0; i < sorted.size(); i++){
            std::cout << sorted.at(i) << " ";
    }
    std::cout << std::endl;
    vec_object.print_elemets();
    

    //Linkedlist
    list<int> l1, l2;
    int n;
    std::cout<<"Enter the elements for List 1"<<endl;
    if (getline(cin, line)) {
        istringstream is(line);
        int i;
        while (is >> i) {
            l1.push_back(i);
        }
    }

    std::cout<<"Enter the elements for List 2"<<endl;
    if (getline(cin, line)) {
        istringstream is(line);
        int i;
        while (is >> i) {
            l2.push_back(i);
        }
    }

    ListClass list_object(l1,l2);

    list_object.print_elemets();
    std::cout << list_object.element_n(4) << std::endl;
    std::cout << list_object.element_n(5) << std::endl;
    std::cout << list_object.is_equal() << std::endl;
    std::cout << list_object.min() << std::endl;
    std::cout << list_object.multiple_of_five() << std::endl;

    list<int> sorted2 = list_object.sortedcontainer();

    std::list<int>::iterator it1 = sorted2.begin();
    while (it1 != sorted2.end()){
        std::cout << *it1 << " ";
        it1++;
    }
    std::cout << std::endl;

    return 0;
}