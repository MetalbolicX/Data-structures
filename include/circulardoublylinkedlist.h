#ifndef _CIRCULAR_DOUBLY_LINKED_LIST_H_
#define _CIRCULAR_DOUBLY_LINKED_LIST_H_

#include "./twowaynode.h"

class CircularDoublyLinkedList {

private:

    TwoWayNode *head;
    TwoWayNode *tail;
    int count;

    // Helper methods for index
    void verifyIndex(int index);
    void emptyness();
    void clear();

public:
    // Constructor
    CircularDoublyLinkedList();

    // Destructor
    ~CircularDoublyLinkedList();

    // Methods
    bool isEmpty() const;
    void display();

    // Methods of addition
    void push(int value);
    void append(int value);
    void insert(int index, int value);
    void insertSorted(int value);
    void beforeValue(int previousValue, int value);
    void afterValue(int afterValue, int value);

    // Methods of search
    TwoWayNode *search(int value);

    // Methods of deletion
    int shift();
    int Delete(int index);
    int pop();
    void removeDuplicatesSorted();
    int remove(int value);

    // Methods of sorting
    bool checkSort();

    // Methods of positioning
    void reverse();

    // For properties
    int getCount();
    int getHeadData();
    int getTailData();
    TwoWayNode *getPtrHead();
    TwoWayNode *getPtrTail();
    bool isLoop();

    // Methods of updates
    void replace(int oldValue, int value, bool entire = false);
    void update(int index, int value);

};

#endif // _CIRCULAR_DOUBLY_LINKED_LIST_H_