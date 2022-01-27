#include <iostream>
#include "../include/circulardoublylinkedlist.h"
//#include "../include/doublylinklist.h"


int main() {

    using std::cout;

    CircularDoublyLinkedList cdll;
    //DoublyLinkList cdll;

    // Adds elements
    cdll.append(1);
    cdll.append(2);
    cdll.append(2);
    cdll.append(3);
    cdll.append(3);
    cdll.append(4);
    cdll.append(6);
    cdll.append(10);
    cdll.append(10);

    cdll.display();
    //cdll.replace(3, 23, true);
    //cout << "Data looped: " << cdll.isLoop() << "\n";

    return 0;
}