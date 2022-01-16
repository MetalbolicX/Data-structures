#ifndef _DOUBLY_LINK_LIST_H_
#define _DOUBLY_LINK_LIST_H_

#include "./twowaynode.h"

class DoublyLinkList {

private:

    TwoWayNode *head;
    TwoWayNode *tail;
    int count;

    // Helper methods
    void verifyIndex(int index);
    void emptyness();
    void clear();

public:
    // Constructor
    DoublyLinkList();

    // Destructor
    ~DoublyLinkList();

    // Methods
    bool isEmpty() const;
    void display();

    // Methods of addition
    void push(int value);
    void append(int value);

};

#endif // _DOUBLY_LINK_LIST_H_