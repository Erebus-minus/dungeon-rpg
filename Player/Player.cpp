#include "Player.h"
#include "../Inventory/Equipment.h"
#include "../UI/UI.h"
#include <iostream>
#include <algorithm>
using namespace std;

Player::Player(const string& name)
    : Entity(name, 100, 15, 5, 10),
      xp(0), xpToNext(50), level(1), statPoints(0),
      atkBonus(0), defBonus(0), weapon(nullptr), armor(nullptr), atkBuffTurns(0),
      defBuffTurns(0), spdBuffTurns(0), atkBuffAmount(0),
      defBuffAmount(0), spdBuffAmount(0)
{}

Player::~Player() {
    delete weapon;
    delete armor;
}

string Player::getAction(){
    return "player";
}

void Player::gainXP(int amount) {
    xp += amount;
    cout << UI::colorize("+" + to_string(amount) + " XP!", UI::CYAN) << "\n";
    while (xp >= xpToNext) {
        xp -= xpToNext; 
        levelUp();
    }
}

void Player::levelUp() {
    level++;
    xpToNext = static_cast<int>(xpToNext * 1.5);
    statPoints += 3;
    stats.maxHP += 10;
    stats.hp = stats.maxHP;
    cout << UI::colorize("\n*** LEVEL UP! You are now level " + to_string(level) + "! ***",
        UI::BOLD + UI::YELLOW) << "\n";
    cout << "Max HP +10. You have " + to_string(statPoints) + " stat points to spend!\n";
    allocateStatPoints();
}

void Player::allocateStatPoints(){
    while (statPoints > 0) {
        cout << "\nStat points remaining: " << statPoints << "\n";
        cout << "Allocate to:\n";
        cout << UI::colorize("  [1]", UI::YELLOW) << " Attack  (current: " << stats.attack << ")\n";
        cout << UI::colorize("  [3]", UI::YELLOW) << " Speed  (current: " << stats.speed << ")\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if(choice == 1){
            stats.attack++;
            cout << UI::colorize("Attack increased to " + to_string(stats.attack) + "!", UI::GREEN) << "\n";
            statPoints--;
        } else if (choice == 2) {
            stats.defense++;
            cout << UI::colorize("Defense increased to " + to_string(stats.defense) + "!", UI::GREEN) << "\n";
            statPoints--;
        } else if (choice == 3){
            stats.speed++;
            cout << UI::colorize("Speed increase to " + to_string(stats.speed) + "!", UI::GREEN) << "\n";
            statPoints--;
        } else {
            cout << UI::colorize("Invalid choice, try again.", UI::RED) << "\n";
        }
    }
}

void Player::applyAtkBuff(int amount, int turns) {
    atkBuffAmount = amount;
    atkBuffTurns = turns;
    stats.attack += amount;
    cout << UI::colorize("Attack +" + to_string(amount) + " for " + to_string(turns) + " turns!", UI::YELLOW) << "\n";
}

void Player::applyDefBuff(int amount, int turns) {
    defBuffAmount = amount;
    defBuffTurns = turns;
    stats.defense += amount;
    cout << UI::colorize("Defense +" + to_string(amount) + " for " + to_string(turns) + " turns!", UI::YELLOW) << "\n";
}

void Player::tickBuffs(){
    if (atkBuffTurns > 0){
        atkBuffTurns--;
        if (atkBuffTurns == 0) {
            stats.attack -= atkBuffAmount;
            atkBuffAmount = 0;
            cout << UI::colorize("Attack buff wore off.", UI::SLATE) << "\n";
        }
    }

    if (defBuffTurns > 0){
        defBuffTurns--;
        if (defBuffTurns == 0) {
            stats.defense -= defBuffAmount;
            defBuffAmount = 0;
            cout << UI::colorize("Defense buff wore off.", UI::SLATE) << "\n";
        }
    }

    if (spdBuffTurns > 0){
        spdBuffTurns--;
        if (spdBuffTurns == 0) {
            stats.speed -= spdBuffAmount;
            spdBuffAmount = 0;
            cout << UI::colorize("Speed buff wore off.", UI::SLATE) << "\n";
        }
    }
}

void Player::equipWeapon(const string& aname, int bonus){
    equippedWeapon = aname;
    atkBonus = bonus;
    cout << UI::colorize("Equipped " + aname + "! Attack +" + to_string(bonus), UI::YELLOW) << "\n";
}

void Player::equipArmor(const string& bname, int bonus){
    equippedArmor = bname;
    defBonus = bonus;
    cout << UI::colorize("Equipped " + bname + "! Defense +" + to_string(bonus), UI::YELLOW) << "\n";
}

bool Player::equip(Equipment* equipment) {
    if (equipment == nullptr) {
        return false;
    }

    if (equipment->getSlot() == "Weapon") {
        delete weapon;
        weapon = equipment;
        equippedWeapon = equipment->getName();
        cout << UI::colorize("Equipped " + equipment->getName() + "!", UI::YELLOW) << "\n";
        return true;
    }

    if (equipment->getSlot() == "Armor") {
        delete armor;
        armor = equipment;
        equippedArmor = equipment->getName();
        cout << UI::colorize("Equipped " + equipment->getName() + "!", UI::YELLOW) << "\n";
        return true;
    }

    cout << UI::colorize("Cannot equip " + equipment->getName() + ": unknown equipment slot.", UI::RED) << "\n";
    return false;
}

int Player::getTotalAttack() const {
    int total = stats.attack + atkBonus;
    if (weapon != nullptr) {
        total += weapon->getAttackBonus();
    }
    if (armor != nullptr) {
        total += armor->getAttackBonus();
    }
    return total;
}

int Player::getTotalDefense() const {
    int total = stats.defense + defBonus;
    if (weapon != nullptr) {
        total += weapon->getDefenseBonus();
    }
    if (armor != nullptr) {
        total += armor->getDefenseBonus();
    }
    return total;
}

void Player::displayStats() const {
    UI::printSeparator();
    cout << UI::colorize("  PLAYER: " + name, UI::BOLD + UI::CYAN) << "\n";
    cout << "  Level:  " << level << "\n";
    UI::printHPBar("  HP", stats.hp, stats.maxHP);
    UI::printXPBar(xp, xpToNext);
    cout << "  Attack:  " << getTotalAttack() << "\n";
    cout << "  Defense:  " << getTotalDefense() << "\n";
    cout << "  Speed:  " << stats.speed << "\n";
    if (statPoints > 0){
        cout << UI::colorize("  Stat points available: " + to_string(statPoints) , UI::YELLOW) << "\n";
    }
    if(!equippedWeapon.empty()){
        cout << "  Weapon:  " << UI::colorize(equippedWeapon, UI::YELLOW) << "\n";
    }
    if(!equippedArmor.empty()){
        cout << "  Armor:  " << UI::colorize(equippedArmor, UI::YELLOW) << "\n";
    }
    UI::printSeparator();
}
