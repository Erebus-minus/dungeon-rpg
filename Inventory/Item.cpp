#include "Item.h"

Item::Item(const string& name, const string& description, int value)
    : name(name), description(description), value(value)
{}

string Item::getName() const {
    return name;
}

string Item::getDescription() const {
    return description;
}

int Item::getValue() const {
    return value;
}

string Item::getType() const {
    return "Item";
}
