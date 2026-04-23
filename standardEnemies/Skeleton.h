//
// Created by diego on 4/22/2026.
//

#ifndef DUNGEON_RPG_SKELETON_H
#define DUNGEON_RPG_SKELETON_H
#include "StandardEnemy.h"
#include <random>


class Skeleton:public StandardEnemy {
private:
    double chanceToRespawn = .50; //All skeletons have a small chance to reassemble after being destroyed.

public:
    [[nodiscard]] bool isDead();

};


#endif //DUNGEON_RPG_SKELETON_H