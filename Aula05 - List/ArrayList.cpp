#include <stdio.h>
#include <iostream>
#include "ArrayList.h"

using namespace std;

int main() {

    structures::ArrayList<int> arr(5);

    arr.push_front(50);
    arr.push_back(80);
    // 50, 80
    cout << arr.size() << endl;
    cout << arr.at(0) << endl;

    // 100, 50, 80
    arr.insert(100, 0);
    cout << arr.at(0) << endl;
    cout << arr.at(1) << endl;

    arr.insert_sorted(70);
    cout << arr.at(0) << endl;
    // 70, 100, 50, 80

    cout << arr.pop(1) << endl;
    cout << arr.at(1) << endl;

}