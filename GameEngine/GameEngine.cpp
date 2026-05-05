#include "GameEngine.h"
#include "../Inventory/Consumable.h"
#include "../Player/Player.h"
#include "../standardEnemies/StandardEnemy.h"
#include "../UI/UI.h"
#include <iostream>
#include <cctype>

using namespace std;

namespace {
    Player player("Hero");
}

GameEngine::GameEngine()
    : dungeon(20, 10),
      playerPosX(1),
      playerPosY(1),
      currentFloor(1),
      finalFloor(5),
      gameRunning(true)
{
    dungeon.generateFloor(currentFloor);
}

//when game starts, shows screen + processes map render and userinput
void GameEngine::runGame() {
    showTitleScreen();

    while (gameRunning) {
        renderGameScreen();
        userInput();
    }
}

void GameEngine::showTitleScreen() {
    UI::clearScreen();
    UI::printTitle();
    UI::printSeparator();

    cout << UI::CYAN << "You are a hero traversing an unknown dungeon, what awaits you at the bottom?" << endl;
    cout << "Controls: Up 'W', Left 'A', Down 'S', Right 'D'; Q to quit" << endl << UI::RESET;

    UI::printSeparator();
    UI::pressEnter();
}

void GameEngine::renderGameScreen() {
    UI::clearScreen();
    UI::printFloorHeader(currentFloor);

    dungeon.render(playerPosX, playerPosY);

    UI:: printSeparator();

    UI::printHPBar("Player", player.getHP(), player.getMaxHP());
    UI::printXPBar(player.getXP(), player.getXPToNext());
}

//handles player movement from user input
void GameEngine::userInput() {
    cout << "Move (W A S D), Q to quit: ";

    char input;
    cin >> input;

    //convert input to lowercase no matter what usertyped
    char lowInput = tolower(input);

    //calls movePlayer depending on user input
    if (lowInput == 'w') movePlayer(0, -1);
    else if (lowInput == 's') movePlayer(0, 1);
    else if (lowInput == 'a') movePlayer(-1, 0);
    else if (lowInput == 'd') movePlayer(1, 0);
    else if (lowInput == 'q') gameRunning = false; //closes game
    else {
        cout << UI::RED << "Invalid Input\n";
        UI::pressEnter();
    }
}

void GameEngine::movePlayer(int x, int y) {
    //add inputed position to player position for new position
    int newPosX = playerPosX + x;
    int newPosY = playerPosY + y;

    //check if there is a wall or not
    if (dungeon.checkWalkable(newPosX, newPosY)) {
        //move player position
        playerPosX = newPosX;
        playerPosY = newPosY;
        //check if there is a chest, enemy, or stair
        checkTile();
    }
}

void GameEngine::checkTile() {
    char tile = dungeon.getTile(playerPosX, playerPosY);

    //call the respective game thingy for this
    if (tile == 'C') {
        cout << UI::YELLOW << "\nYou found a chest!" << endl << UI::RESET;

        Consumable* potion = new Consumable("Health Potion", "Restores a small amount of HP.", 10, 20);
        if (player.getInventory().addItem(potion)) {
            cout << UI::GREEN << "You found a Health Potion and added it to your inventory!" << endl << UI::RESET;
        }
        else {
            delete potion;
            cout << UI::RED << "Your inventory is full, so you leave the potion behind." << endl << UI::RESET;
        }

        dungeon.setTile(playerPosX, playerPosY, ' '); //gets rid of the chest after player gets there
        UI::pressEnter();
    }
    else if (tile == 'E') {
        cout << UI::RED << "\nAn enemy appears!" << endl << UI::RESET;

        StandardEnemy enemy({playerPosX, playerPosY}, "Dungeon Enemy", 25, 8, {1, 3}, 'E');

        int playerDamage = player.getTotalAttack();
        enemy.changeHP(playerDamage);
        cout << "You hit the " << enemy.getName() << " for " << playerDamage << " damage." << endl;

        if (enemy.isDead()) {
            cout << UI::GREEN << "The enemy was defeated!" << endl << UI::RESET;
            player.gainXP(10);
        }
        else {
            int damageTaken = player.takeDamage(enemy.getAtkDmg());
            cout << "The enemy hits you for " << damageTaken << " damage." << endl;

            if (!player.isAlive()) {
                UI::printGameOver();
                gameRunning = false;
            }
        }

        dungeon.setTile(playerPosX, playerPosY, ' '); //clears the enemy after this simple encounter
        UI::pressEnter();
    }
    else if (tile == 'S') {
        nextFloor();
    }
}

void GameEngine::nextFloor() {
    currentFloor++;

    if (currentFloor > finalFloor) {
        UI::clearScreen();
        UI::printVictory();
        gameRunning = false;
        return;
    }

    dungeon.generateFloor(currentFloor);
    playerPosX = 1;
    playerPosY = 1;

    cout << UI::CYAN << "Descending to Floor: " << currentFloor << endl << UI::RESET;
    UI::pressEnter();
}
