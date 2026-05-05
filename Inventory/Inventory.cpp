#include "Inventory.h"
#include "Item.h"
#include "Consumable.h"
#include "Equipment.h"
#include "../Player/Player.h"
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

bool Inventory::useItem(int index, Player& player) {
    if (index < 0 || index >= items.size()) {
        cout << "Invalid item index.\n";
        return false;
    }

    Item* item = items[index];

    Consumable* consumable = dynamic_cast<Consumable*>(item);
    if (consumable != nullptr) {
        consumable->use(player);
        cout << "Used " << consumable->getName() << ".\n";
        items.erase(items.begin() + index);
        delete consumable;
        return true;
    }

    Equipment* equipment = dynamic_cast<Equipment*>(item);
    if (equipment != nullptr) {
        cout << equipment->getName() << " cannot be used yet. Equip logic will be added later.\n";
        return false;
    }

    cout << item->getName() << " cannot be used.\n";
    return false;
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
             << " [Value: " << items[i]->getValue() << "]";

        Consumable* consumable = dynamic_cast<Consumable*>(items[i]);
        if (consumable != nullptr) {
            cout << " [Heal: " << consumable->getHealAmount() << "]";
        }

        Equipment* equipment = dynamic_cast<Equipment*>(items[i]);
        if (equipment != nullptr) {
            cout << " [Attack: " << equipment->getAttackBonus()
                 << ", Defense: " << equipment->getDefenseBonus()
                 << ", Slot: " << equipment->getSlot() << "]";
        }

        cout << "\n";
    }
}

Item* Inventory::getItem(int index) {
    if (index < 0 || index >= items.size()) {
        return nullptr;
    }

    return items[index];
}
