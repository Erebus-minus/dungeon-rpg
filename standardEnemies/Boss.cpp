#include "Boss.h"
#include "../Player/Player.h"
#include <iostream>

Boss::Boss()
    : StandardEnemy({0, 0}, "Boss", 100, 15, {1, 3}, 'B'), maxHP(100), phase(1)
{}

Boss::Boss(const std::pair<int, int>& pos, const std::string& name, int enemyHealth,
           int attackDamage, const std::pair<int, int>& enemySpeedMinAndMax, char symbolASCII)
    : StandardEnemy(pos, name, enemyHealth, attackDamage, enemySpeedMinAndMax, symbolASCII),
      maxHP(enemyHealth),
      phase(1)
{}

void Boss::updatePhase() {
    if (phase == 1 && hp <= maxHP / 2) {
        phase = 2;
        atkDmg += 5;
        std::cout << name << " enters Phase 2! Its attacks become stronger.\n";
    }
}

void Boss::attack(Player& player) {
    updatePhase();

    int damage = atkDmg;
    if (phase == 2) {
        damage += 3;
        std::cout << name << " uses a special Phase 2 attack!\n";
    }
    else {
        std::cout << name << " attacks!\n";
    }

    int actualDamage = player.takeDamage(damage);
    std::cout << player.getName() << " takes " << actualDamage << " damage.\n";
}

int Boss::getPhase() const {
    return phase;
}
