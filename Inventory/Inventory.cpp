#include "Inventory.h"
#include "Item.h"
#include <iostream>
using namespace std;

Inventory::~Inventory() {
    for (Item* item : items) {
        delete item;
    }
    items.clear();
}

bool Inventory::addItem(Item* item) {
    if (item == nullptr) {
        return false;
    }

    if (items.size() >= MAX_SIZE) {
        cout << "Inventory is full.\n";
        return false;
    }

    items.push_back(item);
    return true;
}

void Inventory::removeItem(int index) {
    if (index < 0 || index >= items.size()) {
        cout << "Invalid item index.\n";
        return;
    }

    delete items[index];
    items.erase(items.begin() + index);
}

void Inventory::displayInventory() const {
    if (items.empty()) {
        cout << "Inventory is empty.\n";
        return;
    }

    cout << "Inventory:\n";
    for (int i = 0; i < items.size(); i++) {
        cout << i + 1 << ". "
             << items[i]->getName()
             << " (" << items[i]->getType() << ") - "
             << items[i]->getDescription()
             << " [Value: " << items[i]->getValue() << "]\n";
    }
}

Item* Inventory::getItem(int index) {
    if (index < 0 || index >= items.size()) {
        return nullptr;
    }

    return items[index];
}
