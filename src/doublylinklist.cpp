#include <iostream>
#include <cassert>

#include "../include/doublylinklist.h"

// Default constructor
DoublyLinkList::DoublyLinkList()
    : head {NULL}, tail {NULL}, count {0} {
}

// Evaluate if the list has any element
bool DoublyLinkList::isEmpty() const {
    return head == NULL;
}

// Destructor
DoublyLinkList::~DoublyLinkList() {
    clear();
}

// Remove all elements from the list
void DoublyLinkList::clear() {

    for (TwoWayNode *ptr; !isEmpty();) {
        ptr = head->next;
        delete head;
        head = ptr;
    }
    count = 0;
}