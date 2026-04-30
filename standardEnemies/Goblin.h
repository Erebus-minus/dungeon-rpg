//
// Created by diego on 4/22/2026.
//

#ifndef DUNGEON_RPG_GOBLIN_H
#define DUNGEON_RPG_GOBLIN_H
#include "StandardEnemy.h"


class Goblin: public StandardEnemy {

private:
    double chanceToRun = 0.1; //Goblins are generally pathetic creatures
                           //Whenever they are hit, they have a chance of simply fleeing.
                           //Rn, the code will just kills them
public:
    void changeHP(int value) override;
    //I did want to implement a system to allow them to call for backup
    //However I didn't want to force anyone to have to implement that
};


#endif //DUNGEON_RPG_GOBLIN_H