//
// Created by diego on 4/8/2026.
//

#include "StandardEnemy.h"
//Constructors
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

StandardEnemy::StandardEnemy(const std::pair<int, int> pos, std::string &name, int enemyHealth, int attackDamage, std::pair<int, int> enemySpeedMinAndMax, char symbolASCII) {
    position.first = pos.first;
    position.second = pos.second;
    this->name = name;
    hp = enemyHealth;
    atkDmg = attackDamage;
    enemySpdMinMax.first = enemySpeedMinAndMax.first;
    enemySpdMinMax.second = enemySpeedMinAndMax.second;
    symbol = symbolASCII;
}

StandardEnemy::StandardEnemy(const std::pair<int, int> &pos, std::string &name, int enemyHealth, int attackDamage, std::pair<int, int> enemySpeedMinAndMax, char symbolASCII) {
    position.first = pos.first;
    position.second = pos.second;
    this->name = name;
    hp = enemyHealth;
    atkDmg = attackDamage;
    enemySpdMinMax.first = enemySpeedMinAndMax.first;
    enemySpdMinMax.second=enemySpeedMinAndMax.second;
    symbol = symbolASCII;
}



StandardEnemy::StandardEnemy(int pos_x, int pos_y, std::string& name, int enemyHealth, int attackDamage, std::pair<int,int> enemySpeedMinAndMax, char symbolASCII)
{
    position.first = pos_x;
    position.second = pos_y;
    this->name = name;
    hp = enemyHealth;
    atkDmg = attackDamage;
    enemySpdMinMax.first = enemySpeedMinAndMax.first;
    enemySpdMinMax.second = enemySpeedMinAndMax.second;
    symbol = symbolASCII;
}

//Standard Functions for All Enemies
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
int StandardEnemy::determineEnemySpd() //I have tried making this const before, but CLion keeps freaking out.
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
bool StandardEnemy::isDead() {
    if (hp <= 0)
    {
        return true;
    }
    return false;
}
