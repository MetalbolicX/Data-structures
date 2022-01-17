#include "../include/twowaynode.h"

// Default constructor
TwoWayNode::TwoWayNode()
    : prev {0}, next {0}, value {0} {
}

// Overload constructor
TwoWayNode::TwoWayNode(int data, TwoWayNode *before, TwoWayNode *after)
    : prev {before}, next {after}, value {data} {
}

// Destructor
TwoWayNode::~TwoWayNode() {}