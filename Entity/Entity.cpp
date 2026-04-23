#include "Entity.h"
#include <algorithm>
using namespace std;

Entity::Entity(const string& name, int hp, int atk, int def, int spd) : name(name), alive(true) {
    stats.maxHP = hp;
    stats.hp = hp;
    stats.attack = atk;
    stats.defense = def;
    stats.speed = spd;
}

int Entity::takeDamage(int damage){
    int actualDamage = max(1, damage - stats.defense);
    stats.hp = max(0, stats.hp - actualDamage);
    if(stats.hp <= 0) alive = false;
    return actualDamage;
}

void Entity::heal(int amount){
    stats.hp = min(stats.maxHP, stats.hp + amount);
    alive = true;
}

void Entity::setHP(int hp){
    stats.hp = max(0, min(stats.maxHP, hp));
    if(stats.hp <= 0) alive = false;
}