#include <iostream>
#include <cassert>
#include <climits>

#include "../include/circularsinglylinklist.h"

// Default constructor
CircularSinglyLinkList::CircularSinglyLinkList()
    : head {NULL}, tail {NULL}, count {0} {
}

// Evaluate if the singly link list has any element
bool CircularSinglyLinkList::isEmpty() const {
    return head == NULL;
}

// Desctructor
CircularSinglyLinkList::~CircularSinglyLinkList() {
    clear();
}

// Remove all nodes in the singly link list
void CircularSinglyLinkList::clear() {

    tail->next = NULL;

    for(Node *ptr; !isEmpty();) {
        ptr = head->next;
        delete head;
        head = ptr;
    }
    count = 0;
}

// Get the number of list elements
int CircularSinglyLinkList::getCount() {
    return count;
}

// Get the value of the head element
int CircularSinglyLinkList::getHeadData() {
    return head->value;
}

// Get the value of the tail element
int CircularSinglyLinkList::getTailData() {
    return tail->value;
}

// Get head address
Node *CircularSinglyLinkList::getPtrHead() {
    return head;
}

// Get tail address
Node *CircularSinglyLinkList::getPtrTail() {
    return tail;
}

// Verify if the singly link list has elements
void CircularSinglyLinkList::emptyness() {
    assert(!isEmpty());
}

// Print all elements the sibgly link list
void CircularSinglyLinkList::display() {

    using std::cout;

    // If there are not elements
    if (isEmpty()) {
        cout << "The circular singly linked list is empty.\n";
        return;
    }

    Node *ptr {head};
    cout << "Elements in the circular singly linked list: \n";

    for (int i {0}; i < count; ++i) {
        cout << ptr->value << " ";
        ptr = ptr->next;
    }

    cout << "\n";
}

void CircularSinglyLinkList::verifyIndex(int index) {
    assert(index >= 0 && index < count);
}

// * Adds new elements

// Adds a new element at beginning of singly link list
void CircularSinglyLinkList::push(int value) {

    // Create a new node and references to its the head as next element
    head = new Node(value, head);

    // When is empty the tail is the new element
    if (tail == NULL)
        tail = head;
    else
        tail->next = head;

    ++count;
}

// Adds a new element at end of singly link list
void CircularSinglyLinkList::append(int value) {

    // If list is not empty
    if (tail != NULL) {
        tail->next = new Node(value);
        tail = tail->next;
        tail->next = head;
    } else
        head = tail = new Node(value);

    ++count;
}

// Adds a new element at a given index in the singly link list
void CircularSinglyLinkList::insert(int index, int value) {

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

        // Iterate through the desired index
        Node *ptr {head}, *temp {nullptr};

        while (index > 0) {
            temp = ptr;
            ptr = ptr->next;
            --index;
        }
        // Add a new element
        temp->next = new Node(value, ptr);
        ++count;
    }
}

// Adds a new element in a sorted singly link list
void CircularSinglyLinkList::insertSorted(int value) {

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
void CircularSinglyLinkList::beforeValue(int previousValue, int value) {

    emptyness();

    // Check the first element
    if (head->value == previousValue)
        push(value);
    else {

        Node *ptr {head}, *temp {nullptr};

        while (temp != tail && ptr->value != previousValue) {
            temp = ptr;
            ptr = ptr->next;
        }

        if (ptr != head) {
            temp->next = new Node(value, ptr);
            ++count;
        }
    }
}

// Add a new element after the first apperance of a given value
void CircularSinglyLinkList::afterValue(int afterValue, int value) {

    emptyness();

    // There is only one element
    if (count == 1 && head->value == afterValue)
        append(value);
    else {

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
}

// * Search methods

// Apply the linear search to the singly link list
Node *CircularSinglyLinkList::search(int value) {

    emptyness();

    // Check the extremes
    if (head->value == value)
        return head;
    else if (tail->value == value)
        return tail;

    Node *ptr {head}, *temp {nullptr};

    for (int i {0}; i < count; ++i) {

        if (ptr->value == value) {
            temp->next = ptr->next;
            ptr->next = head;
            head = ptr;
            tail->next = head;

            return ptr;
        }

        temp = ptr;
        ptr = ptr->next;
    }

    // In case its not found
    return NULL;
}

// * Methods of deletion

int CircularSinglyLinkList::shift() {

    // Check if the singly link list has elements
    emptyness();

    Node *ptr {head};
    int x {ptr->value};

    if (count == 1) {
        clear();
        return x;
    }

    head = head->next;
    tail->next = head;
    delete ptr;
    --count;

    return x;
}

// Removes the last element in the list
int CircularSinglyLinkList::pop() {

    emptyness();

    // If there is just one element
    if (count == 1)
        return shift();

    Node *ptr {head}, *temp {head->next};

    while (temp != tail) {
        ptr = temp;
        temp = temp->next;
    }

    int x {temp->value};
    ptr->next = head;
    tail = ptr;
    delete temp;
    --count;

    return x;
}

// Delete an element by a given index
int CircularSinglyLinkList::Delete(int index) {

    emptyness();
    verifyIndex(index);

    // Verify the extremes
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

        int x {ptr->value};
        temp->next = ptr->next;
        delete ptr;
        --count;

        return x;
    }
}

// Remove duplicates
void CircularSinglyLinkList::removeDuplicatesSorted() {

    emptyness();

    Node *ptr {head}, *temp {head->next};

    while (temp !=tail) {

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

    if (temp == tail && ptr->value == temp->value) {
        tail = ptr;
        ptr->next = head;
        delete temp;
        --count;
    }
}

// Delete the first apperance of the given value
int CircularSinglyLinkList::remove(int value) {

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

    // Verify the last pair of elements
    if (ptr == tail && ptr->value == value) {
        x = ptr->value;
        tail = temp;
        temp->next = head;
        delete ptr;
        --count;
        return x;
    // In case it is found before the last two elements
    } else if (ptr->value == value && ptr != tail) {
        x = ptr->value;
        temp->next = ptr->next;
        delete ptr;
        --count;
        return x;
    }

    return x;
}

// * Methods of sorting

// Check if the singly link list is sorted
bool CircularSinglyLinkList::checkSort() {

    emptyness();

    Node *ptr {head};
    int x {INT_MIN};

    for (int i {0}; i < count; ++i) {
        if (ptr->value < x)
            return false;

        x = ptr->value;
        ptr = ptr->next;
    }

    return true;
}

void CircularSinglyLinkList::reverse() {

    emptyness();

    Node *ptr {head}, *prevNode {nullptr}, *nextNode {nullptr};
    tail = head;

    for (int i {0}; i < count; ++i) {
        nextNode = ptr->next;
        ptr->next = prevNode;
        prevNode = ptr;
        ptr = nextNode;
    }

    head = prevNode;
    tail = ptr;
    ptr->next = head;
}

// Check if the singly link list is looped otherwise is linear
bool CircularSinglyLinkList::isLoop() {

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
void CircularSinglyLinkList::replace(int oldValue, int value, bool entire) {

    emptyness();

    Node *ptr {head};

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
void CircularSinglyLinkList::update(int index, int value) {

    // Existance of the elements in the list
    emptyness();
    // Check the range of the index
    verifyIndex(index);

    Node *ptr {head};

    for (int i {0}; i < index; ++i)
        ptr = ptr->next;

    ptr->value = value;
}