#include "GameEngine/GameEngine.h"
#include <iostream>

using namespace std;

int main(){
    srand(time(0));
    
    GameEngine game;
    game.runGame();

    return 0;
}