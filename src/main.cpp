#include <iostream>
#include "../include/singlylinklist.h"
//#include "../include/circularsinglylinklist.h"

int main() {

    using std::cout;

    SinglyLinkList ssl;
    //CircularSinglyLinkList ssl;

    // Adds elements
    ssl.append(1);
    ssl.append(2);
    ssl.append(2);
    ssl.append(3);
    ssl.append(3);
    ssl.append(4);
    ssl.append(6);
    ssl.append(10);

    ssl.display();
    cout << "Data: " << ssl.remove(10) << "\n";

    ssl.display();

    return 0;
}