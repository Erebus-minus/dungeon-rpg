#include "BattleSystem.h"
#include "../UI/UI.h"

#include <iostream>
#include <cstdlib>

using namespace std;

BattleResult BattleSystem::startBattle(Player& player, int x, int y, int floor) {
    //make a rand enemy at the tile player is on
    unique_ptr<StandardEnemy> enemy = createRandomEnemy(x, y, floor);

    cout << UI::RED << "\n A " << enemy->getName() << " appears!" << endl << UI::RESET;

    //trade hits untill someone dies
    while (player.isAlive() && !enemy->isDead()) {
        //player attacks first (calculates attack on ememy from stats + equipment)
        int playerDamage = player.getTotalAttack();
        enemy->changeHP(playerDamage); //deal dmg to enemy
        
        cout << "You hit the " << enemy->getName() << " for " << playerDamage << " damage." << endl;
        
        //if hp gone, player wins
        if (enemy->isDead()) {
            cout << UI::GREEN << "You defeated the " << enemy->getName() << "!" << endl << UI::RESET;
            player.gainXP(10); //give xp
            return PlayerWon;
        }
        
        //enemy survived so now it gets to hit player back
        int damageTaken = player.takeDamage(enemy->getAtkDmg());
        cout << "The " << enemy->getName() << " hits you for " << damageTaken << " damage." << endl;

        //if player hp = 0; game over
        if (!player.isAlive()) {
            UI::printGameOver();
            return PlayerDied;
        }
    }

    //needed a saftey return
    return PlayerDied;

}

//enemy is created randomly (depending on number and is given diff stats depending on the enemy)
unique_ptr<StandardEnemy> BattleSystem::createRandomEnemy(int x, int y, int floor) {
    int roll = rand() % 4;

    if (roll == 0) {
        return make_unique<StandardEnemy>(
            pair<int, int>{x, y},
            "Goblin",
            25 + floor * 3,
            6 + floor,
            pair<int, int>{5, 10},
            'E'
        );
    }
    else if (roll == 1) {
        return make_unique<StandardEnemy>(
            pair<int, int>{x, y},
            "Skeleton",
            30 + floor * 4,
            7 + floor,
            pair<int, int>{3, 8},
            'E'
        );
    }
    else if (roll == 2) {
        return make_unique<StandardEnemy>(
            pair<int, int>{x, y},
            "Slime",
            35 + floor * 4,
            5 + floor,
            pair<int, int>{3, 8},
            'E'
        );
    }
    else {
        return make_unique<StandardEnemy>(
            pair<int, int>{x, y},
            "Troll",
            40 + floor * 4,
            9 + floor,
            pair<int, int>{3, 8},
            'E'
        );
    }

}