#ifndef _CIRCULAR_SINGLY_LINK_LIST_
#define _CIRCULAR_SINGLY_LINK_LIST_

#include "./node.h"

class CircularSinglyLinkList {

private:

    Node *head;
    Node *tail;
    int count;

    // Helper methods for index
    void verifyIndex(int index);
    void emptyness();
    void clear();

public:
    // Constructor
    CircularSinglyLinkList();

    // Destructor
    ~CircularSinglyLinkList();

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
    Node *search(int value);

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
    Node *getPtrHead();
    Node *getPtrTail();
    bool isLoop();

    // Methods of updates
    void replace(int oldValue, int value, bool entire = false);
    void update(int index, int value);

};

#endif // _CIRCULAR_SINGLY_LINK_LIST_