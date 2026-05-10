#include "GameEngine.h"
#include "../Inventory/Consumable.h"
#include "../Inventory/Equipment.h"
#include "../Inventory/Item.h"
#include "../Inventory/InventoryMenu.h"
#include "../Player/Player.h"
#include "../UI/UI.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <limits>

using namespace std;

namespace {
    void openInventory(Player& player);

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
}

//sets up starting values
GameEngine::GameEngine()
    : dungeon(20, 10),
      player("Hero"),
      playerPosX(1),
      playerPosY(1),
      currentFloor(1),
      finalFloor(5),
      gameRunning(true)
{
    //creates floor 1
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

    //prints story
    cout << UI::CYAN << "A demon has been terrorizing the kingdom." << endl;
    cout << "It fled into a forgotten dungeon beneath the land." << endl;
    cout << "Descend through the dungeon and defeat it." << endl << UI::RESET;

    UI::printSeparator();
    UI::pressEnter();
}

//redraws screen after every turn
void GameEngine::renderGameScreen() {
    UI::clearScreen();
    UI::printFloorHeader(currentFloor);

    //prints dungeon w/ player at curr position
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
    else if (lowInput == 'i') InventoryMenu::open(player); //calls menu
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

    //checks if its a chest or an ememy
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
        //starts battle
        BattleResult result = battleSystem.startBattle(player, playerPosX, playerPosY, currentFloor);

        if (result == PlayerWon) {
            dungeon.setTile(playerPosX, playerPosY, ' '); //clears the enemy if player wins
            UI::pressEnter();
        }
        else if (result == PlayerDied) {
            UI::printGameOver();
            gameRunning = false; //game ends if player loses
        }
    }
    else if (tile == 'S') {
        nextFloor();
    }
}

void GameEngine::nextFloor() {
    currentFloor++;

    //if final floor, it becomes the boss floor
    if (currentFloor == finalFloor) {
    
        BattleResult result = battleSystem.startBossBattle(player);
        
        if (result == PlayerWon) {
            UI::clearScreen();
            cout << UI::GREEN << "The Dungeon Boss has been defeated!" << UI::RESET << "\n";
            UI::printVictory();
        }
        else if (result == PlayerFlee) {
            cout << UI::RED << "You flee from the final battle." << UI::RESET << "\n";
            UI::pressEnter();
        }
        else {
            UI::clearScreen();
            UI::printGameOver();
        }

        gameRunning = false;
        return;
    }

    //generate new floor for next floor (after going up stairs)
    dungeon.generateFloor(currentFloor);
    //player resets to (1,1)
    playerPosX = 1;
    playerPosY = 1;

    cout << UI::CYAN << "Descending to Floor: " << currentFloor << endl << UI::RESET;
    UI::pressEnter();
}
