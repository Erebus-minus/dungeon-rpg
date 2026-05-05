#pragma once
#include "Item.h"

class Equipment : public Item {
    private:
        int attackBonus;
        int defenseBonus;
        string slot;

    public:
        Equipment(const string& name, const string& description, int value,
                  int attackBonus, int defenseBonus, const string& slot);

        int getAttackBonus() const;
        int getDefenseBonus() const;
        string getSlot() const;
        string getType() const override;
};
