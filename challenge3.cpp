// Copyright 2023 POOJARN
#include <iostream>
using std::cout, std::endl, std::cin;

void swap(int& first, int& second) {
    int temp = first;
    first = second;
    second = temp;
}

int main() {
    int a, b;
    /*int a = 1;
    int b = 2;*/
    cin >> a >> b;

    // swap(&a, &b); <- will print error
    swap(a, b);
    cout << a << " " << b << endl;
    return 0;
}
