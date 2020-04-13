// ECE 141B Lab 5
//
#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>

using namespace std;

// Part 1 (templatize this function)
template <typename T>
T sum(T &a, T &b) {
    return a+b;
}

// Part 2
template <typename ValueType>

class ListNode {

public:
    ListNode(ValueType v) : value(v), next(nullptr) {}
    ValueType getValue() { return value; }
    ListNode* getNext() { return next; }
    void setValue(ValueType v) { value = v; }
    void setNext(ListNode<ValueType>* node) { next = node; }
private:
    ValueType value;
    ListNode* next;

};

// Part 3
template <typename ValueType>

class LinkedList {

public:

    LinkedList() : size(1) {
        head = new ListNode<int>(0);
        tail = head;
    }

    LinkedList(ValueType val) : size(1) {
        head = new ListNode<ValueType>(val);
        tail = head;
    }

    LinkedList(const LinkedList<ValueType>& aLL) {
        *this = & aLL;
    }

    LinkedList& operator=(const LinkedList<ValueType>& aLL) {
        head = new ListNode<ValueType>(aLL.head->getValue());
        ListNode<ValueType>* curr = head;
        ListNode<ValueType>* aLLc = aLL.head;
        while (aLLc) {
            curr->setNext(new ListNode<ValueType>(aLLc->getNext()->getValue()));
            curr = curr->getNext();
            aLLc = aLLc->getNext();
        }
        tail = curr;
        size = aLL.size;

        return *this;
    }

    ~LinkedList() {
        // please implement the destructor
        ListNode<ValueType>* cur = head;
        ListNode<ValueType>* next = head->getNext();
        
        while (cur) {
            delete cur;
            cur = next;
            next = cur->getNext();
        }
    }

    // Make modifications to this class as you templatize the ListNode class

    // add useful methods to make this class useful
    void addNode(ListNode<ValueType> *node){
        tail->setNext(node);
        tail = tail->getNext();
        size++;
    }

    void show(){
        ListNode<ValueType>* aLLc = this->head;
        std::cout << "size : " << this->size << std::endl;
        while (aLLc) {
            std::cout << aLLc->getValue() << "->";
            aLLc = aLLc->getNext();
        }
        std::cout << "\n";
    } 

    size_t getSize(){
        return size;
    }

private:
    ListNode<ValueType>* head;
    ListNode<ValueType>* tail;
    size_t      size;
};


#endif // LINKEDLIST_HPP