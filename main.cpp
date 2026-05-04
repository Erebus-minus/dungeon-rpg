#include "dungeonGeneration/Dungeon.h"
#include <iostream>

using namespace std;

int main(){
    srand(time(0));
    cout << "Dungeon RPG commencing..." << endl;
    
    Dungeon dungeon(20, 10);

    dungeon.generateFloor(1);

    // pretend player is at (1,1)
    dungeon.render(1, 1);

    return 0;
}