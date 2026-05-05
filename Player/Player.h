#pragma once
#include "../Entity/Entity.h"
#include "../Inventory/Inventory.h"
using namespace std;

class Equipment;

class Player : public Entity {
    private:
        int xp;
        int xpToNext;
        int level;
        int statPoints;

        int atkBonus;
        int defBonus;
        string equippedWeapon;
        string equippedArmor;
        Equipment* weapon;
        Equipment* armor;

        int atkBuffTurns;
        int defBuffTurns;
        int spdBuffTurns;
        int atkBuffAmount;
        int defBuffAmount;
        int spdBuffAmount;

        Inventory inventory;
    
    public:
        Player(const string& name);
        ~Player();

        string getAction() override;
        int takeDamage(int damage) override;

        void gainXP(int amount);
        void levelUp();
        void allocateStatPoints();

        void applyAtkBuff(int amount, int turns);
        void applyDefBuff(int amount, int turns);
        void applySpdBuff(int amount, int turns);
        void tickBuffs();

        void equipWeapon(const string& name, int bonus);
        void equipArmor(const string& name, int bonus);
        bool equip(Equipment* equipment);

        Inventory& getInventory() { return inventory; }
        
        int getLevel() const { return level; }
        int getXP() const { return xp; }
        int getXPToNext() const { return xpToNext; }
        int getStatPoints() const { return statPoints; }
        int getTotalAttack() const;
        int getTotalDefense() const;
        int getEffectiveAttack() const { return getTotalAttack(); }
        int getEffectiveDefense() const { return getTotalDefense(); }

        void displayStats() const;
};
