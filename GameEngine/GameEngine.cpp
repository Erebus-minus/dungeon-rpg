#include "GameEngine.h"
#include "../Inventory/Consumable.h"
#include "../Inventory/Equipment.h"
#include "../Inventory/Item.h"
#include "../Player/Player.h"
#include "../standardEnemies/Boss.h"
#include "../standardEnemies/StandardEnemy.h"
#include "../UI/UI.h"
#include "../Player/Player.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <limits>

using namespace std;

namespace {
    Player player("Hero");

    void openInventory();

    Item* createChestLoot() {
        int lootRoll = rand() % 5;

        if (lootRoll == 0) {
            return new Consumable("Health Potion", "Restores a small amount of HP.", 10, 20);
        }
        else if (lootRoll == 1) {
            return new Equipment("Rusty Sword", "An old sword with a dull edge.", 5, 3, 0, "Weapon");
        }
        else if (lootRoll == 2) {
            return new Equipment("Iron Sword", "A reliable iron sword.", 20, 6, 0, "Weapon");
        }
        else if (lootRoll == 3) {
            return new Equipment("Leather Armor", "Light armor made from tough leather.", 15, 0, 3, "Armor");
        }

        return new Equipment("Iron Armor", "Sturdy armor made from iron plates.", 30, 0, 6, "Armor");
    }

    void runBossEncounter(bool& gameRunning) {
        UI::clearScreen();
        UI::printFloorHeader(5);
        cout << UI::RED << "The final floor is quiet... too quiet." << UI::RESET << "\n";
        cout << UI::RED << "The Dungeon Boss blocks your path!" << UI::RESET << "\n";
        UI::pressEnter();

        Boss boss({10, 5}, "Dungeon Boss", 180, 14, {1, 2}, 'B');

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
                openInventory();
                continue;
            }

            if (choice == 3) {
                cout << UI::RED << "You flee from the final battle." << UI::RESET << "\n";
                UI::pressEnter();
                gameRunning = false;
                return;
            }

            if (choice != 1) {
                cout << UI::RED << "Invalid choice." << UI::RESET << "\n";
                UI::pressEnter();
                continue;
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
            UI::clearScreen();
            cout << UI::GREEN << "The Dungeon Boss has been defeated!" << UI::RESET << "\n";
            UI::printVictory();
        }
        else {
            UI::clearScreen();
            UI::printGameOver();
        }

        gameRunning = false;
    }

    void openInventory() {
        UI::clearScreen();
        cout << UI::CYAN << "Inventory\n" << UI::RESET;
        UI::printSeparator();

        player.getInventory().displayInventory();

        if (player.getInventory().isEmpty()) {
            UI::pressEnter();
            return;
        }

        cout << "\nEnter item number to use, or 0 to go back: ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << UI::RED << "Invalid choice." << UI::RESET << "\n";
            UI::pressEnter();
            return;
        }

        if (choice == 0) {
            return;
        }

        if (choice < 1 || choice > player.getInventory().getSize()) {
            cout << UI::RED << "Invalid item number." << UI::RESET << "\n";
            UI::pressEnter();
            return;
        }

        player.getInventory().useItem(choice - 1, player);
        UI::pressEnter();
    }
}

GameEngine::GameEngine()
    : dungeon(20, 10),
      player("Hero"),
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

//Show into title screen
void GameEngine::showTitleScreen() {
    UI::clearScreen();
    UI::printTitle();
    UI::printSeparator();

cout << UI::CYAN << "A demon has been terrorizing the kingdom." << endl;
cout << "It fled into a forgotten dungeon beneath the land." << endl;
cout << "Descend through the dungeon and defeat it." << endl;
cout << "Controls: Up 'W', Left 'A', Down 'S', Right 'D'; I for inventory; Q to quit" << endl << UI::RESET;

    UI::printSeparator();
    UI::pressEnter();
}

void GameEngine::renderGameScreen() {
    UI::clearScreen();
    UI::printFloorHeader(currentFloor);

    dungeon.render(playerPosX, playerPosY);

    UI::printSeparator();

    //use player.h to insert player stats (HP and where they are in regards to XP
    UI::printHPBar("Player", player.getHP(), player.getMaxHP());
    UI::printXPBar(player.getXP(), player.getXPToNext());
}

//handles player movement from user input
void GameEngine::userInput() {
    cout << "Move (W A S D), I for inventory, Q to quit: ";

    char input;
    cin >> input;

    //convert input to lowercase no matter what usertyped
    char lowInput = tolower(input);

    //calls movePlayer depending on user input
    if (lowInput == 'w') movePlayer(0, -1);
    else if (lowInput == 's') movePlayer(0, 1);
    else if (lowInput == 'a') movePlayer(-1, 0);
    else if (lowInput == 'd') movePlayer(1, 0);
    else if (lowInput == 'i') openInventory();
    else if (lowInput == 'q') gameRunning = false; //closes game
    else {
        cout << UI::RED << "Invalid Input\n" << UI::RESET;
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

        Item* loot = createChestLoot();
        if (player.getInventory().addItem(loot)) {
            cout << UI::GREEN << "You found " << loot->getName()
                 << " and added it to your inventory!" << endl << UI::RESET;
        }
        else {
            cout << UI::RED << "Your inventory is full, so you leave "
                 << loot->getName() << " behind." << endl << UI::RESET;
            delete loot;
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

    if (currentFloor == finalFloor) {
        runBossEncounter(gameRunning);
        return;
    }

    if (currentFloor > finalFloor) {
        gameRunning = false;
        return;
    }

    dungeon.generateFloor(currentFloor);
    playerPosX = 1;
    playerPosY = 1;

    cout << UI::CYAN << "Descending to Floor: " << currentFloor << endl << UI::RESET;
    UI::pressEnter();
}
