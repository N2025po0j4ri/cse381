// Copyright 2024 Alan Ferrenberg
#ifndef INVENTORY_H_
#include <string>
#define INVENTORY_H_
#endif  // INVENTORY_H_

class Inventory {
 private:
    int itemID;
    std::string itemName;
    int quantity;
    double price;

 public:
    // Constructors
    Inventory();
    Inventory(int id, const std::string& name, int qty, double itemPrice);

    // Getter and setter functions
    int getItemID() const;
    void setItemID(int id);

    const std::string& getItemName() const;
    void setItemName(const std::string& name);

    int getQuantity() const;
    void setQuantity(int qty);

    double getPrice() const;
    void setPrice(double itemPrice);

    // Display item details
    void displayItemDetails() const;
};


