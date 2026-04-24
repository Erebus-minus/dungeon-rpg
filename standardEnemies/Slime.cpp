//
// Created by diego on 4/22/2026.
//

#include "Slime.h"

void Slime::changeHP(int value) {
    static std::random_device rd2;
    static std::mt19937 gen(rd2());
    std::uniform_int_distribution<> distrib(0,1);

    if (distrib(gen)<= chanceToAvoidDmg) {
        return;
    }
    hp -= value;
}