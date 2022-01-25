#include <iostream>
#include <cassert>
#include <climits>

#include "../include/circulardoublylinkedlist.h"

// Default constructor
CircularDoublyLinkedList::CircularDoublyLinkedList()
    : head {NULL}, tail {NULL}, count {0} {
}

// Evaluate if the singly link list has any element
bool CircularDoublyLinkedList::isEmpty() const {
    return head == NULL;
}

// Desctructor
CircularDoublyLinkedList::~CircularDoublyLinkedList() {
    clear();
}

// Remove all nodes in the singly link list
void CircularDoublyLinkedList::clear() {

    tail->next = NULL;

    for(TwoWayNode *ptr; !isEmpty();) {
        ptr = head->next;
        delete head;
        head = ptr;
    }
    count = 0;
}

// Get the number of list elements
int CircularDoublyLinkedList::getCount() {
    return count;
}

// Get the value of the head element
int CircularDoublyLinkedList::getHeadData() {
    return head->value;
}

// Get the value of the tail element
int CircularDoublyLinkedList::getTailData() {
    return tail->value;
}

// Get head address
TwoWayNode *CircularDoublyLinkedList::getPtrHead() {
    return head;
}

// Get tail address
TwoWayNode *CircularDoublyLinkedList::getPtrTail() {
    return tail;
}

// Verify if the singly link list has elements
void CircularDoublyLinkedList::emptyness() {
    assert(!isEmpty());
}

// Print all elements the sibgly link list
void CircularDoublyLinkedList::display() {

    using std::cout;

    // If there are not elements
    if (isEmpty()) {
        cout << "The circular doubly linked list is empty.\n";
        return;
    }

    TwoWayNode *ptr {head};
    cout << "Elements in the circular linked list: \n";

    for (int i {0}; i < count; ++i) {
        cout << ptr->value << " ";
        ptr = ptr->next;
    }

    cout << "\n";
}

void CircularDoublyLinkedList::verifyIndex(int index) {
    assert(index >= 0 && index < count);
}

// * Adds new elements

// Adds a new element at beginning of singly link list
void CircularDoublyLinkedList::push(int value) {

    TwoWayNode *newNode = new TwoWayNode(value);

    // When is empty the tail is the new element
    if (head == NULL) {
        head = tail = newNode;
        head->prev = tail;
        head->next = head;
    } else {
        head->prev = newNode;
        newNode->next = head;
        newNode->prev = tail;
        head = newNode;
    }

    ++count;
}

// Adds a new element at end of singly link list
void CircularDoublyLinkedList::append(int value) {

    TwoWayNode *newNode = new TwoWayNode(value);

    // If list is not empty
    if (head == NULL) {
        head = newNode;
        head->prev = tail;
        head->next = head;
    } else {
        tail->next = newNode;
        newNode->prev = head;
        newNode->next = head;
        tail = newNode;
    }

    ++count;
}

// Adds a new element at a given index in the singly link list
void CircularDoublyLinkedList::insert(int index, int value) {

    // Verify if the singly link list has elements
    emptyness();

    // Verification for no more elements in the singly link list
    verifyIndex(index);

    // Add new element
    if (index == 0)
        push(value);
    else if (index == count-1)
        append(value);
    else {

        TwoWayNode *ptr {head};

        for (int i {0}; i < index-1; ++i)
            ptr = ptr->next;

        ptr->next = new TwoWayNode(value, ptr, ptr->next);
        ptr->next->next->prev = ptr->next;
        ++count;
    }
}

// Adds a new element in a sorted singly link list
void CircularDoublyLinkedList::insertSorted(int value) {

    // Existance of elements in the singly link list
    emptyness();

    // Check if the new value is less than head
    if (head->value >= value)
        push(value);
    else if (tail->value <= value)
        append(value);
    else {

        TwoWayNode *ptr {head->next};

        while (ptr != tail && ptr->value <= value && !(ptr->value > value))
            ptr = ptr->next;

        ptr->prev->next = new TwoWayNode(value, ptr->prev, ptr);
        ptr->prev = ptr->prev->next;
        ++count;
    }
}

// Adds a new element before the first apperance of the first ocurrance of a given element
void CircularDoublyLinkedList::beforeValue(int previousValue, int value) {

    emptyness();

    // Check the first element
    if (head->value == previousValue)
        push(value);
    else {

        TwoWayNode *ptr {head};

        while (ptr != tail && ptr->value != previousValue)
            ptr = ptr->next;

        if (ptr->value == previousValue) {
            ptr->prev->next = new TwoWayNode(value, ptr->prev, ptr);
            ptr->prev = ptr->prev->next;
            ++count;
        }
    }
}

// Add a new element after the first apperance of a given value
void CircularDoublyLinkedList::afterValue(int afterValue, int value) {

    emptyness();

    // There is only one element
    if (count == 1 && head->value == afterValue)
        append(value);
    else {

        TwoWayNode *ptr {head};

        while (ptr != tail && ptr->value != afterValue)
            ptr = ptr->next;

        if (ptr == tail && ptr->value == afterValue)
            append(value);
        else if (ptr->value == afterValue) {
            ptr->next = new TwoWayNode(value, ptr, ptr->next);
            ptr->next->next->prev = ptr->next;
            ++count;
        }
    }
}

// * Search methods

// Apply the linear search to the singly link list
TwoWayNode *CircularDoublyLinkedList::search(int value) {

    emptyness();

    // Check the extremes
    if (head->value == value)
        return head;
    else if (tail->value == value)
        return tail;

    TwoWayNode *ptr {head}, *temp {nullptr};

    for (int i {0}; i < count; ++i) {

        if (ptr->value == value) {

            temp = ptr;
            ptr->prev->next = ptr->next;
            ptr->next->prev = ptr->prev;

            ptr->next = head;
            ptr->prev = tail;
            head = ptr;

            return temp;
        }

        ptr = ptr->next;
    }

    // In case its not found
    return NULL;
}

// * Methods of deletion

int CircularDoublyLinkedList::shift() {

    // Check if the singly link list has elements
    emptyness();

    TwoWayNode *ptr {head};
    int x {ptr->value};

    if (count == 1) {
        clear();
        return x;
    }

    head = head->next;
    head->prev = tail;
    tail->next = head;
    delete ptr;
    --count;

    return x;
}

// Removes the last element in the list
int CircularDoublyLinkedList::pop() {

    emptyness();

    TwoWayNode *ptr {tail};
    int x {ptr->value};

    // If there is just one element
    if (count == 1) {
        clear();
        return x;
    }

    tail = tail->prev;
    tail->next = head;
    delete ptr;
    --count;

    return x;
}

// Delete an element by a given index
int CircularDoublyLinkedList::Delete(int index) {

    emptyness();
    verifyIndex(index);

    if (count == 1) {
        int x {head->value};
        clear();
        return x;
    }

    // Verify the extremes
    if (index == 0)
        return shift();
    else if (index == count-1)
        return pop();
    else {

        TwoWayNode *ptr {head};

        for (int i {0}; i < index; ++i)
            ptr = ptr->next;

        int x {ptr->value};
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        delete ptr;
        --count;

        return x;
    }
}

// Remove duplicates
void CircularDoublyLinkedList::removeDuplicatesSorted() {

    emptyness();

    TwoWayNode *ptr {head->next}, *temp {nullptr};

    while (ptr !=tail) {

        if (ptr->prev->value != ptr->value)
            ptr = ptr->next;
        else {
            temp = ptr->next;
            ptr->prev->next = temp;
            temp->prev = ptr->prev;
            delete temp;
            --count;
            ptr = temp;
        }
    }

    if (ptr == tail && ptr->prev->value == ptr->value)
        pop();
}

// Delete the first apperance of the given value
int CircularDoublyLinkedList::remove(int value) {

    emptyness();

    // In case its the first element
    if (head->value == value)
        return shift();

    TwoWayNode *ptr {head};
    int x {INT_MIN};

    while (ptr != tail && ptr->value != value)
        ptr = ptr->next;

    if (ptr == tail && ptr->value == value)
        return pop();
    else if (ptr != tail && ptr->value == value) {
        x = ptr->value;
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        delete ptr;
        --count;

        return x;
    }

    return x;
}

// * Methods of sorting

// Check if the singly link list is sorted
bool CircularDoublyLinkedList::checkSort() {

    emptyness();

    TwoWayNode *ptr {head};
    int x {INT_MIN};

    for (int i {0}; i < count; ++i) {
        if (ptr->value < x)
            return false;

        x = ptr->value;
        ptr = ptr->next;
    }

    return true;
}

void CircularDoublyLinkedList::reverse() {

    emptyness();

    TwoWayNode *ptr {head}, *prevNode {nullptr}, *nextNode {nullptr};
    tail = ptr;

    for (int i {0}; i < count; ++i) {
        nextNode = ptr->next;
        ptr->next = prevNode;
        ptr->prev = nextNode;
        prevNode = ptr;
        ptr = nextNode;
    }

    head = prevNode;
    head->prev = tail;
    tail->next = head;
}

// Check if the singly link list is looped otherwise is linear
bool CircularDoublyLinkedList::isLoop() {

    emptyness();

    TwoWayNode *ptr {head}, *temp {head};

    do {
        ptr = ptr->next;
        temp = temp->next;
        temp = (temp) ? temp->next : NULL;
    } while (ptr && temp && ptr != temp);

    return (ptr == temp) ? true : false;
}

// * Methods of update

// Replace all values or the first apperance of a given value with a new one
void CircularDoublyLinkedList::replace(int oldValue, int value, bool entire) {

    emptyness();

    TwoWayNode *ptr {head};

    for (int i {0}; i < count; ++i) {
        // Replace the value
        if (ptr->value == oldValue) {
            ptr->value = value;

            // Stop in case the entire value is false
            if (!entire)
                break;
        }

        ptr = ptr->next;
    }
}

// Replace an value with a new value by a given index
void CircularDoublyLinkedList::update(int index, int value) {

    // Existance of the elements in the list
    emptyness();
    // Check the range of the index
    verifyIndex(index);

    TwoWayNode *ptr {head};

    for (int i {0}; i < index; ++i)
        ptr = ptr->next;

    ptr->value = value;
}