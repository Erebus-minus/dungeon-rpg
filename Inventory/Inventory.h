#pragma once
#include <vector>
#include <string>
using namespace std;

class Item;
class Player;

class Inventory {
    private:
        vector<Item*> items;
        static const int MAX_SIZE = 10;

    public:
        bool addItem(Item* item);
        bool useItem(int index, Player& player);
        void removeItem(int index);
        void display() const;
        bool isEmpty() const { return items.empty();}
        int size() const { return items.size();}
        Item* getItem(int index);
};