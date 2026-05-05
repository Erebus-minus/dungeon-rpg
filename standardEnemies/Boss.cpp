#include "Boss.h"
#include "../Player/Player.h"
#include <iostream>

Boss::Boss()
    : StandardEnemy({0, 0}, "Boss", 220, 10, {1, 3}, 'B'), maxHP(220), phase(1), attackCount(0)
{}

Boss::Boss(const std::pair<int, int>& pos, const std::string& name, int enemyHealth,
           int attackDamage, const std::pair<int, int>& enemySpeedMinAndMax, char symbolASCII)
    : StandardEnemy(pos, name, enemyHealth, attackDamage, enemySpeedMinAndMax, symbolASCII),
      maxHP(enemyHealth),
      phase(1),
      attackCount(0)
{}

void Boss::updatePhase() {
    if (phase == 1 && hp <= maxHP / 2) {
        phase = 2;
        atkDmg += 4;
        std::cout << "\n*** The boss enters Phase 2! ***\n";
        std::cout << name << " becomes enraged and hits harder.\n";
    }
}

void Boss::attack(Player& player) {
    updatePhase();

    int damage = atkDmg;
    if (phase == 2) {
        attackCount++;
        if (attackCount % 2 == 0) {
            damage += 4;
            std::cout << name << " uses a heavy Phase 2 attack!\n";
        }
        else {
            std::cout << name << " attacks with Phase 2 strength!\n";
        }
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
