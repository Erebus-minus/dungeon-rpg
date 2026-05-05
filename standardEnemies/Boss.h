#ifndef DUNGEON_RPG_BOSS_H
#define DUNGEON_RPG_BOSS_H

#include "StandardEnemy.h"

class Player;

class Boss : public StandardEnemy {
private:
    int maxHP = 180;
    int phase = 1;

public:
    Boss();
    Boss(const std::pair<int, int>& pos, const std::string& name, int enemyHealth,
         int attackDamage, const std::pair<int, int>& enemySpeedMinAndMax, char symbolASCII);

    void updatePhase();
    void attack(Player& player);
    [[nodiscard]] int getPhase() const;
};

#endif //DUNGEON_RPG_BOSS_H
