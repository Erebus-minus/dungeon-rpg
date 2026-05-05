#pragma once
#include <string>
using namespace std;

class Item {
    protected:
        string name;
        string description;
        int value;

    public:
        Item(const string& name, const string& description, int value);
        virtual ~Item() = default;

        string getName() const;
        string getDescription() const;
        int getValue() const;
        virtual string getType() const;
};
