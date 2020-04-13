//
//  VectorClass.hpp
//  Lab8
//
//


#ifndef vector_h
#define vector_h

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std; 


class VectorClass{
    public:
    VectorClass(vector<int> v1, vector<int> v2) : vec1(v1), vec2(v2){}

    //STUDENT -- Return true if the vec1 and vec2 are equal to each other.
    bool is_equal(){
        if (vec1.size() != vec2.size()) return false;
        for (size_t i = 0; i < vec1.size(); i++){
            if (vec1.at(i) != vec2.at(i)) return false;
        }
        return true;
    }

    //STUDENT -- print elements of the vec1 using iterators separated by space 
    void print_elemets(){
        for (size_t i = 0; i < vec1.size(); i++){
            std::cout << vec1.at(i);
            if (i < vec1.size() - 1)  std::cout << " ";
        }
        std::cout << std::endl;
    }

    //STUDENT -- return 1 if all the elements of vec1 are multiple of 5, return 0 if any of the elements of vec1 
    // are a multiple of 5 or return -1 if none of the elements of vec 1 are a multiple of 5.
    int multiple_of_five(){
        int count = 0;
        for (size_t i = 0; i < vec1.size(); i++){
            if (vec1.at(i) % 5 == 0) count++;
        }

        if (count == vec1.size()) return 1;
        else if (count == 0) return -1;
        else return 0;
    }

    //rSTUDENT -- return nth element from vector1 - return -1 if out of range
    int element_n(int n){
        int size = vec1.size();
        if (n >= size) return -1;
        return vec1.at(n);
    }

    //STUDENT --return the minimum element in the vector
    int min_max(){
        int min = vec1.at(0);
        for (size_t i = 1; i < vec1.size(); i++){
            if (min > vec1.at(i)) min = vec1.at(i);
        }
        return min;
    }

    //STUDENT -- return sorted vector of vec1
    vector<int> sortedcontainer(){
        std::vector<int> sorted(vec1);
        for (size_t i = 0; i < sorted.size(); i++){
            size_t k = i;
            for (size_t j = k + 1; j < sorted.size(); j++){
                if (sorted[j] < sorted[k]){
                    k = j;
                }
            }
            int temp = sorted[i];
            sorted[i] = sorted[k];
            sorted[k] = temp;
        }

        return sorted;
	}

    //STUDENT -- return the number of elements in the vec1 which are equal to n
    int match_count(int n){
        int count = 0;
        for (size_t i = 0; i < vec1.size(); i++){
            if (vec1.at(i) == n) count++;
        }
        return count;
    }

    protected:
        vector<int> vec1;
        vector<int> vec2;
};


#endif //vector_h
