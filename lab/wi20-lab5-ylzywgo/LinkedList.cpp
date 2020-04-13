// ECE 141B Lab 5
//

#include <iostream>
#include "LinkedList.hpp"

int main() {

    // write your test functions here...
    ListNode<int>* n = new ListNode<int>(1);
    std::cout << n->getValue() << std::endl;
    ListNode<int>* m = new ListNode<int>(2);
    LinkedList<int>* l = new LinkedList<int>();
    l->addNode(n);
    l->addNode(m);
    l->show();
    LinkedList<int> *copy_l = l;
    copy_l->show();
}

