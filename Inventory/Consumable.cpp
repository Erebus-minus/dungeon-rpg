#include "Consumable.h"
#include "../Player/Player.h"

Consumable::Consumable(const string& name, const string& description, int value, int healAmount)
    : Item(name, description, value), healAmount(healAmount)
{}

int Consumable::getHealAmount() const {
    return healAmount;
}

string Consumable::getType() const {
    return "Consumable";
}

void Consumable::use(Player& player) {
    player.heal(healAmount);
}
