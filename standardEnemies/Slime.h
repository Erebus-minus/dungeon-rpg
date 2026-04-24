//
// Created by diego on 4/22/2026.
//

#ifndef DUNGEON_RPG_SLIME_H
#define DUNGEON_RPG_SLIME_H
#include "StandardEnemy.h"


class Slime:public StandardEnemy {
private:
    double chanceToAvoidDmg = 0.2; //All slimes have a chacne to avoid damage
    //Thematically, it could just be attacks passing through them.
    //Feel free to adjust chacnce if it feels necessar
public:
    void changeHP(int value) override;
};






#endif //DUNGEON_RPG_SLIME_H