#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "../dungeonGeneration/Dungeon.h"

class GameEngine{
    private:
        Dungeon dungeon;
        int playerPosX;
        int playerPosY;
        int currentFloor;
        int finalFloor;
        bool gameRunning;

        void showTitleScreen();
        void renderGameScreen();
        void userInput();
        void movePlayer(int x, int y);
        void checkTile();
        void nextFloor();

    public:
        GameEngine();
        void runGame();
};

#endif