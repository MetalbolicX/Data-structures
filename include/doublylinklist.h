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

    // Methods of descrption of the list
    bool isEmpty() const;
    void display();
    int getCount();
    int getHeadData();
    int getTailData();
    TwoWayNode *getPtrHead();
    TwoWayNode *getPtrTail();

    // Methods of addition
    void push(int value);
    void append(int value);
    void insert(int index, int value);
    void insertSorted(int value);
    void beforeValue(int previousValue, int value);
    void afterValue(int afterValue, int value);

    // Methods of deletion
    int shift();
    int pop();
    int Delete(int index);
    void removeDuplicatesSorted();
    int remove(int value);

    // Methods of sorting
    bool checkSort();

    // Methods miscellaneus
    void reverse();
    bool isLoop();

    // Methods of update
    void replace(int oldValue, int value, bool entire = false);
    void update(int index, int value);

};

#endif // _DOUBLY_LINK_LIST_H_