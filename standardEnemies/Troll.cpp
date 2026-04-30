//
// Created by diego on 4/22/2026.
//

#include "Troll.h"

void Troll::changeHP(int value) {
    if (hp< 5) {
        isEnraged = true;
    }
    hp -= (value-armor);
}

int Troll::getAtkDmg() const {

    if (isEnraged) {
        return atkDmg + 2;
    }
    return atkDmg;
}