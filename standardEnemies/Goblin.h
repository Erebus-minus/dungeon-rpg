//
// Created by diego on 4/22/2026.
//

#ifndef DUNGEON_RPG_GOBLIN_H
#define DUNGEON_RPG_GOBLIN_H
#include "StandardEnemy.h"


class Goblin: public StandardEnemy {

private:
    int chanceToRun = 0.1; //Goblins are generally pathetic creatures
                           //Whenever they are hit, they have a chance of simply fleeing.
                           //Rn, the code will just kill them, but if you guys wanna change it feel free to
public:
    void changeHP(int value) override;
};


#endif //DUNGEON_RPG_GOBLIN_H