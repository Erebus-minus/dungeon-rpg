//
// Created by diego on 4/8/2026.
//

#ifndef DUNGEON_RPG_STANDARDENEMY_H
#define DUNGEON_RPG_STANDARDENEMY_H
#include <string>
#include <random>
#include <utility>

class StandardEnemy {
protected:
    //Basic Info
    std::pair<int,int> position; //pos_x,pos_y
    int hp = -1;
    int atkDmg = -1;
    std::pair<int,int> enemySpdMinMax = {-1,-1}; //spd_min,spd_max
    std::string name = "Enemy";
    char symbol = 'E';
public:


    StandardEnemy();

    StandardEnemy(const std::pair<int, int> &pos, const std::string &name, int enemyHealth, int attackDamage,
                  const std::pair<int, int> &enemySpeedMinAndMax, char symbolASCII);

    StandardEnemy(const std::pair<int, int> &pos, std::string &name, int enemyHealth, int attackDamage,
                  std::pair<int, int> enemySpeedMinAndMax, char symbolASCII);

    StandardEnemy(std::pair<int, int> pos, std::string &name, int enemyHealth, int attackDamage,
                  std::pair<int, int> enemySpeedMinAndMax, char symbolASCII);

    StandardEnemy(int pos_x, int pos_y, std::string& name, int enemyHealth, int attackDamage, std::pair<int,int> enemySpeedMinAndMax, char symbolASCII);

    void setPosition(const std::pair<int,int>& pos);
    [[nodiscard]] int getHP() const;
    virtual void changeHP(int value);
    [[nodiscard]] virtual int getAtkDmg() const;

    int determineEnemySpd();
    [[nodiscard]] char getSymbol() const;
    [[nodiscard]] std::string getName() const;

    [[nodiscard]] std::pair<int,int> getPosition() const;
    [[nodiscard]]  virtual bool isDead() const;

};

#endif //DUNGEON_RPG_STANDARDENEMY_H