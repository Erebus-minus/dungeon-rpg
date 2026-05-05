#pragma once
#include "Item.h"

class Player;

class Consumable : public Item {
    private:
        int healAmount;

    public:
        Consumable(const string& name, const string& description, int value, int healAmount);

        int getHealAmount() const;
        string getType() const override;
        void use(Player& player);
};
