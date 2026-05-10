#include "BattleSystem.h"
#include "../Inventory/InventoryMenu.h"
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

BattleResult BattleSystem::startBossBattle(Player& player) {
    UI::clearScreen();
    UI::printFloorHeader(5);
    cout << UI::RED << "The final floor is quiet... too quiet." << UI::RESET << "\n";
    cout << UI::RED << "The Demon Lord blocks your path!" << UI::RESET << "\n";
    UI::pressEnter();
    
    Boss boss({10, 5}, "Demon Lord", 220, 10, {1, 2}, 'B');
    
    while (player.isAlive() && !boss.isDead()) {
        UI::clearScreen();
        cout << UI::BOLD << "Boss Fight\n" << UI::RESET;
        UI::printSeparator();
        cout << boss.getName() << " HP: " << boss.getHP() << " | Phase: " << boss.getPhase() << "\n";
        UI::printHPBar("Player", player.getHP(), player.getMaxHP());
        UI::printSeparator();
        
        cout << "[1] Attack\n";
        cout << "[2] Open inventory\n";
        cout << "[3] Run/Quit\n";
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << UI::RED << "Invalid choice." << UI::RESET << "\n";
            UI::pressEnter();
            continue;
        }
        
        if (choice == 2) {
            InventoryMenu::open(player);
            continue;
        }
        
        if (choice == 3) {
            return PlayerFlee;
        }
        
        int playerDamage = player.getTotalAttack();
        boss.changeHP(playerDamage);
        cout << "You hit the " << boss.getName() << " for " << playerDamage << " damage.\n";
        boss.updatePhase();
        
        if (boss.isDead()) {
            break;
        }
        
        boss.attack(player);
        
        if (!player.isAlive()) {
            break;
        }
        
        UI::pressEnter();
    }
    
    if (boss.isDead()) {
        return PlayerWon;
    }
    else {
        return PlayerDied;
    }

}