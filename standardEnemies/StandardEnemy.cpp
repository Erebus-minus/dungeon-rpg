//
// Created by diego on 4/8/2026.
//

#include "StandardEnemy.h"

StandardEnemy::StandardEnemy()= default;
StandardEnemy::StandardEnemy(const std::pair<int,int>& pos, //pos_x,pos_y
                            const std::string& name,
                            const int enemyHealth,
                            const int attackDamage,
                            const std::pair<int,int>& enemySpeedMinAndMax,
                            const char symbolASCII)
{
    position.first = pos.first;
    position.second = pos.second;
    this->name = name;
    hp = enemyHealth;
    atkDmg = attackDamage;
    enemySpdMinMax = enemySpeedMinAndMax;
    symbol = symbolASCII;
}

void StandardEnemy::setPosition(const std::pair<int,int>& pos) //pos_x,pos_y
{
    position.first = pos.first;
    position.second = pos.second;
}
int StandardEnemy::getHP() const
{
 return hp;
}
void StandardEnemy::changeHP(int value)
{
    hp = hp-value;
}
int StandardEnemy::getAtkDmg() const
{
    return atkDmg;
}
int StandardEnemy::determineEnemySpd()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(this->enemySpdMinMax.first, this->enemySpdMinMax.second);
    return distrib(gen);
}
char StandardEnemy::getSymbol() const
{
    return symbol;
}
std::string StandardEnemy::getName() const
{
    return name;
}

std::pair<int,int> StandardEnemy::getPosition() const {
    return {position.first, position.second};
}
bool StandardEnemy::isDead() const {
    if (hp <= 0)
    {
        return true;
    }
    return false;
}
