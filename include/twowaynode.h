#ifndef _TWO_WAY_NODE_H_
#define _TWO_WAY_NODE_H_

class TwoWayNode {

private:

    TwoWayNode *prev, *next;
    int value;

public:
    // Default constructor
    TwoWayNode();

    // Constructor
    TwoWayNode(int data, TwoWayNode *before = 0, TwoWayNode *after = 0);

    // Destructor
    ~TwoWayNode();

    friend class DoublyLinkList;
};

#endif // _TWO_WAY_NODE_H_