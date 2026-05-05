#include <iostream>
#include <ctime>
#include <cstdlib>
#include "GameEngine/GameEngine.h"

using namespace std;

int main(){
    srand(time(0));
    
    GameEngine game;
    game.runGame();

    return 0;
}
