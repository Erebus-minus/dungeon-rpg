#include "Equipment.h"

Equipment::Equipment(const string& name, const string& description, int value,
                     int attackBonus, int defenseBonus, const string& slot)
    : Item(name, description, value),
      attackBonus(attackBonus),
      defenseBonus(defenseBonus),
      slot(slot)
{}

int Equipment::getAttackBonus() const {
    return attackBonus;
}

int Equipment::getDefenseBonus() const {
    return defenseBonus;
}

string Equipment::getSlot() const {
    return slot;
}

string Equipment::getType() const {
    return "Equipment";
}
