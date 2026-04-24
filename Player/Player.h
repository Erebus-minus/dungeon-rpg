#pragma once
#include "../Entity/Entity.h"
#include "../Inventory/Inventory.h"
using namespace std;

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

        int atkBuffTurns;
        int defBuffTurns;
        int spdBuffTurns;
        int atkBuffAmount;
        int defBuffAmount;
        int spdBuffAmount;

        Inventory inventory;
    
    public:
        Player(const string& name);

        string getAction() override;

        void gainXP(int amount);
        void levelUp();
        void allocateStatPoints();

        void applyAtkBuff(int amount, int turns);
        void applyDefBuff(int amount, int turns);
        void applySpdBuff(int amount, int turns);
        void tickBuffs();

        void equipWeapon(const string& name, int bonus);
        void equipArmor(const string& name, int bonus);

        Inventory& getInventory() { return inventory; }
        
        int getLevel() const { return level; }
        int getXP() const { return xp; }
        int getXPToNext() const { return xpToNext; }
        int getStatPoints() const { return statPoints; }
        int getEffectiveAttack() const { return stats.attack + atkBonus; }
        int getEffectiveDefense() const { return stats.defense + defBonus; }

        void displayStats() const;
};