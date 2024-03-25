// Copyright 2024 Alan Ferrenberg
#include <iostream>

using std::cin, std::cout, std::endl;

// Function to swap two integers using pointers
void swapWithPointers(int* a, int* b) {
    // Using a temporary variable to swap values
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to swap two integers using references
void swapWithReferences(int& a, int& b) {
    // Swapping values directly using references
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int num1, num2;

    // Read two ints from the user
    cout << "Enter the first integer: ";
    cin >> num1;

    cout << "Enter the second integer: ";
    cin >> num2;

    // Call the swap function with pointers
    swapWithPointers(&num1, &num2);

    // Print the swapped values
    cout << "Swapped using pointers: " << num1 << " " << num2 << std::endl;

    // Call the swap function with references
    swapWithReferences(num1, num2);

    // Print the swapped values
    cout << "Swapped using references: " << num1 << " " << num2 << std::endl;

    return 0;
}
