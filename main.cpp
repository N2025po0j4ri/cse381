// Copyright 2023 Nirupama Poojari
#include <iostream>
#include <vector>
#include "Inventory.h"

using std::cout, std::cin, std::endl, std::ostream;

// Create some initial inventory items
void initializeInventory(std::vector<Inventory>& inv) {
    // Create two instances specifying all instance variables
    inv.push_back(Inventory(1, "Item A", 10, 15.99));
    inv.push_back(Inventory(2, "Item B", 5, 24.99));
    // Create an empty instance and use setters to initialize
    inv.push_back(Inventory());
    size_t invSize = inv.size();
    inv[invSize - 1].setItemID(3);
    inv[invSize - 1].setItemName("Item C");
    inv[invSize - 1].setQuantity(8);
    inv[invSize - 1].setPrice(19.99);
}

void menu() {
    cout << "Enter 1 to display the inventory" << endl;
    cout << "Enter 2 to search for an item" << endl;
    cout << "Enter 3 to update the quantity of an item" << endl;
    cout << "Enter 4 to update the price of an item" << endl;
    cout << "Enter 0 to exit the program" << endl;
    cout << "Enter your choice: ";
}

void displayInventory(std::vector<Inventory>& inv) {
    size_t invSize = inv.size();
    for (size_t i = 0; i < invSize; i++) {
       inv[i].displayItemDetails();
       cout << "---------------------------" << endl;
    }
}

void ItemSearch(std::vector<Inventory>& inv) {
    int key;
    cout << "Enter the item ID to search for: ";
    cin >> key;
    size_t invSize = inv.size();
    bool found = false;
    for (size_t i = 0; i < invSize; ++i) {
        if (inv[i].getItemID() == key) {
            found = true;
            cout << "\nItem found! Details:" << endl;
            inv[i].displayItemDetails();
            cout << endl;
        }
    }
    if (!found) {
        cout << "\nItem " << key << " not found in the inventory." << endl;
        cout << endl;
    }
}
void changeQuantity(std::vector<Inventory>& inv, int key) {
    size_t invSize = inv.size();
    bool found = false;
    for (size_t i = 0; i < invSize; i++) {
        if (inv[i].getItemID() == key) {
            found = true;
            int qty;
            cout << "Current quantity is " << inv[i].getQuantity() << "\n";
            cout << "Enter new quantity: ";
            cin >> qty;
            inv[i].setQuantity(qty);
            inv[i].getQuantity();
            cout << "Quantity is now " <<  qty << "\n";
            cout << endl;
        }
    }
    if (!found) {
        cout << "\nInvalid item ID.  Exiting program." << endl;
        cout << endl;
        exit(0);
    }
}
void updateQuantity(std::vector<Inventory>& inv) {
    int key;
    cout << "Enter item ID to update quantity: ";
    cin >> key;
    changeQuantity(inv, key);
}

void changePrice(std::vector<Inventory>& inv, int key) {
    size_t invSize = inv.size();
    bool found = false;
    for (size_t i = 0; i < invSize; i++) {
        if (inv[i].getItemID() == key) {
            found = true;
            double newPrice;
            cout << "Current price is " << inv[i].getPrice() << "\n";
            cout << "Enter new price: ";
            cin >> newPrice;
            inv[i].setPrice(newPrice);
            inv[i].getPrice();
            cout << "price is now " << inv[i].getPrice() << "\n";
            cout << endl;
        }
    }
    if (!found) {
        cout << "\nInvalid item ID.  Exiting program." << endl;
        cout << endl;
        exit(0);
    }
}

void idUpdatePrice(std::vector<Inventory>& inv) {
    int key;
    cout << "Enter item ID to update price: ";
    cin >> key;
    changePrice(inv, key);
}


int main() {
    std::vector<Inventory> inventory;  // Create a vector to store items
    initializeInventory(inventory);  // Add some items to the inventory
    // Add main function
    // add helper functions above
    int choice = 0;
    do {
        menu();
        cin >> choice;
        if (choice == 1) {
            displayInventory(inventory);
        } else if (choice == 2) {
            ItemSearch(inventory);
        } else if (choice == 3) {
            updateQuantity(inventory);
        } else if (choice == 4) {
            idUpdatePrice(inventory);
        }
        if (choice < 0 || choice > 4) {
            cout << endl;
            cout << "Invalid choice:  Try again." << endl;
            cout << endl;
        }
    } while (choice != 0);
    return 0;
}
