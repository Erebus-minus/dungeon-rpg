#pragma once
#include <vector>
using namespace std;

class Item;

class Inventory {
    private:
        vector<Item*> items;
        static const int MAX_SIZE = 10;

    public:
        ~Inventory();
        Inventory() = default;
        Inventory(const Inventory& other) = delete;
        Inventory& operator=(const Inventory& other) = delete;

        bool addItem(Item* item);
        void removeItem(int index);
        void displayInventory() const;
        bool isEmpty() const { return items.empty();}
        Item* getItem(int index);
        int getSize() const { return items.size();}
};
