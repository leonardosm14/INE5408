#include <stdio.h>
#include <iostream>
#include "LinkedList.h"

using namespace std;

int main() {    

    structures::LinkedList<int> lst;
    lst.push_front(10);
    lst.push_front(20);

    cout << lst.find(10) << endl;

    return 0;
}