#include <iostream>
#include <cassert>
#include <climits>

#include "../include/singlylinklist.h"

// Default constructor
SinglyLinkList::SinglyLinkList()
    : head {NULL}, tail {NULL}, count {0} {
}

// Evaluate if the singly link list has any element
bool SinglyLinkList::isEmpty() const {
    return head == NULL;
}

// Desctructor
SinglyLinkList::~SinglyLinkList() {
    clear();
}

// Remove all nodes in the singly link list
void SinglyLinkList::clear() {

    for(Node *ptr; !isEmpty();) {
        ptr = head->next;
        delete head;
        head = ptr;
    }
    count = 0;
}

// Get the number of list elements
int SinglyLinkList::getCount() {
    return count;
}

// Get the value of the head element
int SinglyLinkList::getHeadData() {
    return head->value;
}

// Get the value of the tail element
int SinglyLinkList::getTailData() {
    return tail->value;
}

// Get head address
Node *SinglyLinkList::getPtrHead() {
    return head;
}

// Get tail address
Node *SinglyLinkList::getPtrTail() {
    return tail;
}

// Verify if the singly link list has elements
void SinglyLinkList::emptyness() {
    assert(!isEmpty());
}

// Print all elements the sibgly link list
void SinglyLinkList::display() {

    using std::cout;

    // If there are not elements
    if (isEmpty()) {
        cout << "The circular singly linked list is empty.\n";
        return;
    }

    Node *ptr {head};
    cout << "Elements in the singly linked list: \n";

    for (int i {0}; i < count; ++i) {
        cout << ptr->value << " ";
        ptr = ptr->next;
    }

    cout << "\n";
}

void SinglyLinkList::verifyIndex(int index) {
    assert(index >= 0 && index < count);
}

// * Adds new elements

// Adds a new element at beginning of singly link list
void SinglyLinkList::push(int value) {

    // Create a new node and references to its the head as next element
    head = new Node(value, head);

    // When is empty the tail is the new element
    if (tail == NULL)
        tail = head;
    // Increase the count
    ++count;
}

// Adds a new element at end of singly link list
void SinglyLinkList::append(int value) {

    // If list is not empty
    if (tail != NULL) {
        tail->next = new Node(value);
        tail = tail->next;
    } else
        head = tail = new Node(value);

    ++count;
}

// Adds a new element at a given index in the singly link list
void SinglyLinkList::insert(int index, int value) {

    // Verify if the singly link list has elements
    emptyness();

    // Verification for no more elements in the singly link list
    verifyIndex(index);

    // Add new element
    if (index == 0)
        push(value);
    else if (index == count - 1)
        append(value);
    else {

        // Iterate through the desired index
        Node *ptr {head};

        while (index > 1) {
            ptr = ptr->next;
            --index;
        }

        // Add a new element
        ptr->next = new Node(value, ptr->next);
        ++count;
    }
}

// Adds a new element in a sorted singly link list
void SinglyLinkList::insertSorted(int value) {

    // Existance of elements in the singly link list
    emptyness();

    // Check if the new value is less than head
    if (head->value >= value)
        push(value);
    else if (tail->value <= value)
        append(value);
    else {

        Node *ptr {head}, *temp {head->next};

        while (temp != tail && ptr->value <= value && !(temp->value > value)) {
            ptr = temp;
            temp = temp->next;
        }

        ptr->next = new Node(value, temp);
        ++count;
    }
}

// Adds a new element before the first apperance of the first ocurrance of a given element
void SinglyLinkList::beforeValue(int previousValue, int value) {

    emptyness();

    // Check the first element
    if (head->value == previousValue) {
        push(value);
        return;
    }

    Node *ptr {head}, *temp {nullptr};

    while (ptr != tail && ptr->value != previousValue) {
        temp = ptr;
        ptr = ptr->next;
    }

    if (ptr->value == previousValue) {
        temp->next = new Node(value, ptr);
        ++count;
    }
}

// Add a new element after the first apperance of a given value
void SinglyLinkList::afterValue(int afterValue, int value) {

    emptyness();

    // There is only one element
    if (count == 1 && head->value == afterValue) {
        append(value);
        return;
    }

    Node *ptr {head}, *temp {head->next};

    while (temp != tail && ptr->value != afterValue) {
        ptr = temp;
        temp = temp->next;
    }

    if (temp == tail && temp->value <= afterValue)
        append(value);
    else if (ptr->value <= afterValue) {
        ptr->next = new Node(value, temp);
        ++count;
    }
}

// * Search methods

// Apply the linear search to the singly link list
Node *SinglyLinkList::search(int value) {

    emptyness();

    // Check the extremes
    if (head->value == value)
        return head;
    else if (tail->value == value)
        return tail;

    Node *ptr {head}, *temp {nullptr};

    while (ptr != NULL) {

        temp = ptr;

        if (ptr->value == value) {
            temp->next = ptr->next;
            ptr->next = head;
            head = ptr;
            return ptr;
        }

        temp = ptr;
        ptr = ptr->next;
    }

    // In case its not found
    return NULL;
}

// * Methods of deletion

int SinglyLinkList::shift() {

    // Check if the singly link list has elements
    emptyness();

    int x {head->value};

    if (count == 1) {
        clear();
        return x;
    }

    Node *ptr {head};
    head = head->next;

    // Deletion
    delete ptr;
    --count;

    return x;
}

// Delete an element by a given index
int SinglyLinkList::Delete(int index) {

    emptyness();

    // In case it just one element or the first element to remove
    if (index == 0)
        return shift();
    else if (index == count-1)
        return pop();
    else {

        Node *ptr {head}, *temp {nullptr};

        for (int i {0}; i < index; ++i) {
            temp = ptr;
            ptr = ptr->next;
        }

        temp->next = ptr->next;
        int x {ptr->value};
        delete ptr;
        --count;

        return x;
    }
}

int SinglyLinkList::pop() {

    emptyness();

    int x {tail->value};

    if (count == 1) {
        clear();
        return x;
    }

    Node *ptr {nullptr};

    // Iterate to the previous node to the last
    for (ptr = head; ptr->next != tail; ptr = ptr->next);

    delete tail;
    tail = ptr; // Previous become the tail
    tail->next = NULL;
    --count;
    return x;

}

// Remove duplicates
void SinglyLinkList::removeDuplicatesSorted() {

    emptyness();

    Node *ptr {head}, *temp {head->next};

    while (temp != NULL) {

        if (ptr->value != temp->value) {
            ptr = temp;
            temp = temp->next;
        } else {
            ptr->next = temp->next;
            delete temp;
            --count;
            temp = ptr->next;
        }
    }
}

int SinglyLinkList::remove(int value) {

    emptyness();

    // In case its the first element
    if (head->value == value)
        return shift();

    Node *ptr {head}, *temp {nullptr};
    int x {INT_MIN};

    while (ptr != tail && ptr->value != value) {
        temp = ptr;
        ptr = ptr->next;
    }

    if (ptr == tail && ptr->value == value) {
        x = ptr->value;
        tail = temp;
        temp->next = NULL;
        delete ptr;
        --count;
        return x;
    } else if (ptr != tail && ptr->value == value) {
        x = ptr->value;
        temp->next = ptr->next;
        --count;
        delete ptr;
        return x;
    }

    return x;
}

// * Methods of sorting

// Check if the singly link list is sorted
bool SinglyLinkList::checkSort() {

    emptyness();

    Node *ptr {head};
    int x {INT_MIN};

    while (ptr != NULL) {
        if (ptr->value < x)
            return false;

        x = ptr->value;
        ptr = ptr->next;
    }

    return true;
}

void SinglyLinkList::reverse() {

    emptyness();

    Node *ptr {head}, *prevNode {nullptr}, *nextNode {nullptr};
    tail = head;

    while (ptr != NULL) {
        nextNode = ptr->next;
        ptr->next = prevNode;
        prevNode = ptr;
        ptr = nextNode;
    }

    head = prevNode;
}

// Check if the singly link list is looped otherwise is linear
bool SinglyLinkList::isLoop() {

    emptyness();

    Node *ptr {head}, *temp {head};

    do {
        ptr = ptr->next;
        temp = temp->next;
        temp = (temp) ? temp->next : NULL;
    } while (ptr && temp && ptr != temp);

    return (ptr == temp) ? true : false;
}

// * Methods of update

// Replace all values or the first apperance of a given value with a new one
void SinglyLinkList::replace(int oldValue, int value, bool entire) {

    emptyness();

    Node *ptr {head};

    while (ptr != NULL) {
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
void SinglyLinkList::update(int index, int value) {

    // Existance of the elements in the list
    emptyness();
    // Check the range of the index
    verifyIndex(index);

    Node *ptr {head};

    for (int i {0}; i < index; ++i)
        ptr = ptr->next;

    ptr->value = value;
}