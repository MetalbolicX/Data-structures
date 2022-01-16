#ifndef _NODE_H_
#define _NODE_H_

class Node {

private:
    // To store data and create the next reference
    int value;
    Node *next;

public:
    // Default constructor
    Node();

    // Constructor
    Node(int data, Node *ptr = 0);

    // Destructor
    ~Node();

    friend class SinglyLinkList;
    friend class CircularSinglyLinkList;
};

#endif // _NODE_H_