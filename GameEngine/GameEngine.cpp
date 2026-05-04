#include "GameEngine.h"
#include "../UI/UI.h"
#include <iostream>
#include <cctype>

using namespace std;

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

    //placeholder stats
    UI::printHPBar("Player", 100, 100);
    UI::printXPBar(0, 100);
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
        dungeon.setTile(playerPosX, playerPosY, ' '); //gets rid of the item after player gets there
        UI::pressEnter();
    }
    else if (tile == 'E') {
        cout << UI::RED << "\nAn enemy appears!" << endl << UI::RESET;
        dungeon.setTile(playerPosX, playerPosY, ' '); //gets rid of the item after player gets there
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