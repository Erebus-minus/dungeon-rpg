#pragma once
#include <string>
using namespace std;

struct Stats {
    int maxHP;
    int hp;
    int attack;
    int defense;
    int speed;
};

class Entity {
    protected: 
        string name;
        Stats stats;
        bool alive;
    
    public: 
        Entity(const string& name, int hp, int atk, int def, int spd);
        virtual ~Entity() = default;

        virtual int takeDamage(int damage);
        virtual string getAction() = 0;

        bool isAlive() const { return alive && stats.hp > 0; }
        const string& getName() const { return name; }
        int getHP () const { return stats.hp; }
        int getMaxHP() const { return stats.maxHP; }
        int getDefense() const { return stats.defense; }
        int getSpeed() const { return stats.speed; }
        void setHP(int hp);
        void setAttack(int atk) { stats.attack = atk; }
        void setDefense(int def) { stats.defense = def; }
        void setSpeed(int spd) { stats.speed = spd; }
        void heal(int amount);
};