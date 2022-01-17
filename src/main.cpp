#include <iostream>
//#include "../include/singlylinklist.h"
//#include "../include/circularsinglylinklist.h"
#include "../include/doublylinklist.h"

int main() {

    using std::cout;

    //SinglyLinkList ssl;
    //CircularSinglyLinkList ssl;
    DoublyLinkList ssl;

    // Adds elements
    ssl.append(1);
    ssl.append(2);
    ssl.append(2);
    ssl.append(3);
    ssl.append(3);
    ssl.append(4);
    ssl.append(6);
    ssl.append(10);
    //ssl.append(10);

    ssl.display();
    ssl.replace(3, 23, true);
    cout << "Data erased: " << ssl.isLoop() << "\n";

    ssl.display();

    return 0;
}