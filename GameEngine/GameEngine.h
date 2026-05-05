#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "../dungeonGeneration/Dungeon.h"
#include "../Player/Player.h"
#include "../BattleSystem/BattleSystem.h"

class GameEngine{
    private:
        Dungeon dungeon;
        Player player;
        BattleSystem battleSystem;
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