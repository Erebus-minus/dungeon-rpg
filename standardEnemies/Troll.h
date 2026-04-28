//
// Created by diego on 4/22/2026.
//

#ifndef DUNGEON_RPG_TROLL_H
#define DUNGEON_RPG_TROLL_H
#include "StandardEnemy.h"


class Troll: public StandardEnemy {
    private:
    int armor = 2; //Trolls have very tough skin, and take a flat amount of
                   //reduced damage everytime they are hit
    bool isEnraged = false; //When trolls fall beneath a certain health threshold
                            //They deal an additional amount of damage
    public:

    void changeHP(int value) override;
    [[nodiscard]] int getAtkDmg() const override;

};




#endif //DUNGEON_RPG_TROLL_H