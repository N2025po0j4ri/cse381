// Copyright 2024 NPoojari
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Inventory.h"
using std::cout, std::cin, std::endl;

// Constructors
Inventory::Inventory() {}
Inventory::Inventory(int id, const std::string& name,
int qty, double itemPrice) {
    itemID = id;
    itemName = name;
    quantity = qty;
    price = itemPrice;
}

// Getter and setter functions

int Inventory::getItemID() const {
    return itemID;
}
void Inventory::setItemID(int id) {
    itemID = id;
}

const std::string& Inventory::getItemName() const {
    return itemName;
}

void Inventory::setItemName(const std::string& name) {
    itemName = name;
}

int Inventory::getQuantity() const {
    return quantity;
}

void Inventory::setQuantity(int qty) {
    // quantity = qty;
    quantity = qty;
}

double Inventory::getPrice() const {
    return price;
}
void Inventory::setPrice(double itemPrice) {
    price = itemPrice;
}

// Display item details
void Inventory::displayItemDetails() const {
    cout << "Item ID: " << itemID << endl;
    cout << "Item Name: " <<itemName << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Price: $" << price << endl;
}















































































































