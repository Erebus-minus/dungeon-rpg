//
// Created by diego on 4/22/2026.
//

#include "Skeleton.h"

bool Skeleton::isDead() {
    static std::random_device rd1;
    static std::mt19937 gen(rd1());
    std::uniform_int_distribution<> distrib(0,1);
    if (hp <= 0 && distrib(gen)<chanceToRespawn){
        hp += 5;
        chanceToRespawn /= 2;
        return false;
    }
    return true;
}
