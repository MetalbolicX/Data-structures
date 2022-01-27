#include <iostream>
#include <cassert>
#include <climits>

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

// Get the number of elements
int DoublyLinkList::getCount() {
    return count;
}

// Get the the value of the head
int DoublyLinkList::getHeadData() {
    return head->value;
}

// Get the value of the tail
int DoublyLinkList::getTailData() {
    return tail->value;
}

// Get head address
TwoWayNode *DoublyLinkList::getPtrHead() {
    return head;
}

// Get tail address
TwoWayNode *DoublyLinkList::getPtrTail() {
    return tail;
}

// Verify if the list has elements
void DoublyLinkList::emptyness() {
    assert(!isEmpty());
}

// Print the elements in the list
void DoublyLinkList::display() {

    using std::cout;

    // In case there are not elements
    if (isEmpty()) {
        cout << "Doubly linked list is empty.\n";
        return;
    }

    cout << "Doubly linked list elements: \n";

    for(TwoWayNode *ptr {head}; ptr != NULL; ptr = ptr->next)
        cout << ptr->value << " ";

    cout << "\n";
}

// Verify the range of the index
void DoublyLinkList::verifyIndex(int index) {
    assert(index >= 0 && index < count);
}

// * Methods of addition

// Add a new element at beginning of the list
void DoublyLinkList::push(int value) {

    //head = new TwoWayNode(value, 0, head);
    TwoWayNode *ptr = new TwoWayNode(value, NULL, head);

    if (!isEmpty()) {
        head = ptr;
        tail = head;
    } else {
        head->prev = ptr;
        head = ptr;
    }

    ++count;
}

// Add a new element at end of the list
void DoublyLinkList::append(int value) {

    // The list is not empty
    if (tail != NULL) {
        tail->next = new TwoWayNode(value, tail);
        tail = tail->next;
    } else
        head = tail = new TwoWayNode(value);

    ++count;
}

// Add a new node at a given index
void DoublyLinkList::insert(int index, int value) {

    emptyness();
    verifyIndex(index);

    if (index == 0)
        push(value);
    else if (index == count-1)
        append(value);
    else {

        TwoWayNode *ptr {head};

        while (index > 1) {
            ptr = ptr->next;
            --index;
        }

        ptr->next = new TwoWayNode(value, ptr, ptr->next);
        ptr->next->next->prev = ptr->next;
        ++count;
    }
}

// Add a new node in a sorted list
void DoublyLinkList::insertSorted(int value) {

    emptyness();

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

// Add a new before the first apperance of a given element
void DoublyLinkList::beforeValue(int previousValue, int value) {

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

// Adds a new element after the first apperance of the given value
void DoublyLinkList::afterValue(int afterValue, int value) {

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

// * Methods of deletion

// Remove the first element in the list
int DoublyLinkList::shift() {

    emptyness();

    TwoWayNode *ptr {head};
    int x {ptr->value};

    if (count == 1) {
        clear();
        return x;
    }

    head = head->next;

    delete ptr;
    --count;

    if (head)
        head->prev = NULL;

    return x;
}

// Remove the last element in the list
int DoublyLinkList::pop() {

    emptyness();

    TwoWayNode *ptr {tail};
    int x {ptr->value};

    if (count == 1) {
        clear();
        return x;
    }

    tail = tail->prev;
    tail->next = NULL;
    delete ptr;
    --count;

    return x;
}

int DoublyLinkList::Delete(int index) {

    emptyness();
    verifyIndex(index);

    if (index == 0 || count == 1)
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

// Remove all duplicates values in the list
void DoublyLinkList::removeDuplicatesSorted() {

    emptyness();

    TwoWayNode *ptr {head->next}, *temp {nullptr};

    while (ptr != tail) {

        if (ptr->prev->value != ptr->value)
            ptr = ptr->next;
        else {

            temp = ptr->next;
            ptr->prev->next = temp;
            temp->prev = ptr->prev;
            --count;
            delete ptr;
            ptr = temp;
        }
    }

    if (ptr == tail && ptr->prev->value == ptr->value)
        pop();
}

// Remove the first apperance of the given element in the list
int DoublyLinkList::remove(int value) {
    
    emptyness();

    if (head->value == value)
        return shift();

    TwoWayNode *ptr {head};
    int x {INT_MIN};

    while (ptr != tail && ptr->value != value)
        ptr = ptr->next;

    // If it is the last element to remove
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

// Check if list is sorted
bool DoublyLinkList::checkSort() {

    emptyness();

    int x {INT_MIN};

    for (TwoWayNode *ptr {head}; ptr != NULL; ptr = ptr->next) {
        if (ptr->value < x)
            return false;
        
        x = ptr->value;
    }

    return true;
}

// * Methods miscellaneus

// Reverse ths list
void DoublyLinkList::reverse() {

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
}

// Verify if the list is looped
bool DoublyLinkList::isLoop() {

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

// Replace the first occurrence of a given value with the new one or all occurrences
void DoublyLinkList::replace(int oldValue, int value, bool entire) {

    emptyness();

    for (TwoWayNode *ptr {head}; ptr != NULL; ptr = ptr->next) {
        if (ptr->value == oldValue)
            ptr->value = value;

            // Stop in case the entire value is false
        if (!entire)
            break;
    }
}

// Replace a value by a given index
void DoublyLinkList::update(int index, int value) {

    emptyness();
    verifyIndex(index);

    TwoWayNode *ptr {head};

    for (int i {0}; i < index; ++i)
        ptr = ptr->next;

    ptr->value = value;
}

// Search a given value in the list
TwoWayNode *DoublyLinkList::search(int value) {

    if (head->value == value)
        return head;
    else if (tail->value == value)
        return tail;
    else {

        TwoWayNode *ptr {head};

        for (int i {0}; i < count; ++i) {

            if (ptr->value == value) {
                ptr->prev->next = ptr->next;
                ptr->next->prev = ptr->prev;

                ptr->next = head;
                ptr->prev = NULL;
                head = ptr;

                return ptr;
            }

            ptr = ptr->next;
        }
    }

    return NULL;
}