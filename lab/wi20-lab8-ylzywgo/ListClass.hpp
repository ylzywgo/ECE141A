//
//  ListClass.hpp
//  Lab8
//
//

#include <stdio.h>
#include <iostream>
#include <list>
#include "VectorClass.hpp"

using namespace std;


class ListClass{
    public:
        ListClass(list<int> v1, list<int> v2) : l1(v1), l2(v2){}

        //STUDENT -- Return true if the list1 and list2 are equal to each other.
        bool is_equal(){
            if (l1.size() != l2.size()) return false;
            std::list<int>::iterator it1 = l1.begin();
            std::list<int>::iterator it2 = l2.begin();
            while (it1 != l1.end() && it2 != l2.end()){
                if (*it1 != *it2) return false;
                it1++;
                it2++;
            }

            return true;
        }

        //STUDENT -- print elements of the list1 using iterators separated by space 
        void print_elemets(){
            std::list<int>::iterator it1 = l1.begin();
            while (it1 != l1.end()){
                std::cout << *it1 << " ";
                it1++;
            }
            std::cout << std::endl;
        }

        int multiple_of_five(){
            std::list<int>::iterator it1 = l1.begin();
            int count = 0;
            while (it1 != l1.end()){
                int cur = *it1;
                if (cur % 5 == 0) count++;
                it1++;
            }
            if (count == l1.size()) return 1;
            else if (count == 0) return -1;
            else return 0;
        }

        //STUDENT --  return nth element from Lis1 - return -1 if out of range
        int element_n(int n){
            std::list<int>::iterator it1 = l1.begin();
            while (it1 != l1.end()){
                int cur = *it1;
                if (n-- == 0) return cur;
                it1++;
            }
            return -1;
        }

        //STUDENT --  return the minimum element in List 1
        int min(){
            std::list<int>::iterator it1 = l1.begin();
            int min = *it1;
            while (it1 != l1.end()){
                int cur = *it1;
                if (cur < min) min = cur;
                it1++;
            }

            return min;
        }

        //return sorted list1 
        list<int> sortedcontainer(){
            list<int> sorted(l1);
            sorted.sort();
            return sorted;
        }

        //return the number of elements in the lis1 which are equal to n
        int match_count(int n){
            std::list<int>::iterator it1 = l1.begin();
            int count = 0;
            while (it1 != l1.end()){
                int cur = *it1;
                if (cur == n) count++;
                it1++;
            }

            return count;
        }


    protected:
        list<int> l1;
        list<int> l2;

};
