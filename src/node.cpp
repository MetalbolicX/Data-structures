#include "../include/node.h"

// Default constructor
Node::Node()
    : value {0}, next {0} {
}

// Constructor
Node::Node(int data, Node *ptr)
    : value {data}, next {ptr} { // <- this is useful for initial the next pointer
}

// Destructor
Node::~Node() {}