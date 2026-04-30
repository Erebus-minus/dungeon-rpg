//
// Created by diego on 4/22/2026.
//

#include "Goblin.h"

void Goblin::changeHP(int value) {
    static std::random_device rd3;
    static std::mt19937 gen(rd3());
    std::uniform_int_distribution<> distrib(0,1);
    if (distrib(gen) < chanceToRun)
    {
        hp = 0;
        return;
    }
    hp -= value;
}