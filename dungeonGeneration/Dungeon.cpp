#include "Dungeon.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

//constructer for dungeon generation (i think)
Dungeon::Dungeon(int w, int h) : width(w), height(h) {
    grid.resize(height, vector<char>(width, '#'));
}

//constructing a floor
void Dungeon::generateFloor(int floorNumber) {
    //fill everything in with walls '#'
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid[y][x] = '#';
        }
    }
    
    //create a path from player position [1,1] to stair position
    int startX = 1;
    int startY = 1;
    int stairsX = width - 2;
    int stairsY = height - 2;

    grid[startY][startX] = ' '; //blank space

    //loop if start position hasn't reached stair position
    while (startX != stairsX || startY != stairsY) {
        //goes right or down randomly (from starting point which is top left most space)
        if (startX < stairsX && (rand() % 2 == 0 || startY == stairsY)) {
            startX++;
        }
        else if (startY < stairsY) {
            startY++;
        }

        //turns that position into a free tile
        grid[startY][startX] = ' ';
    }

    //add extra space (calculating how many open tiles)
    int extraSpaces = width * height / 2;

    for (int i = 0; i < extraSpaces; i++) {
        //avoids left(0) wall and right (19) walls
        int x = 1 + rand() % (width - 2);
        //avoids top(0) wall and bottom (9) walls
        int y = 1 + rand() % (height - 2);

        grid[y][x] = ' ';
    }

    //places stairs at the corner of the screen after path is created (right most bottom tile)
    grid[stairsY][stairsX] = 'S';
    
    //placing chests + enenmies depending on floornumber
    int numChests = 1 + floorNumber / 2;
    int numEnemies = 2 + floorNumber;
    
    //loop for finding rand blank spaces for chests
    for (int i = 0; i < numChests; i++) {
        int x;
        int y;

        do {
            //can only use tiles from 1-18 or 1-8; avoid walls
            x = 1 + rand() % (width - 2);
            y = 1 + rand() % (height - 2);
        }
        while (grid[y][x] != ' '); //keep looping if not an empty tile
        
        //place chest
        grid[y][x] = 'C';
    }

    //loop for finding rand blank spaces for enemies
    for (int i = 0; i < numEnemies; i++) {
        int x;
        int y;

        do {
            //can only use tiles from 1-18 or 1-8; avoid walls
            x = 1 + rand() % (width - 2);
            y = 1 + rand() % (height - 2);
        }
        while (grid[y][x] != ' '); //keep looping if not an empty tile

        //place enemy
        grid[y][x] = 'E';
    }
}

// rendering/printing the actual dungeon (tile by tile)
void Dungeon::render(int playerX, int playerY) const {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            //checks for player tile, if so prints player
            if (x == playerX && y == playerY) {
                cout << 'P';
            }
            else {
                cout << grid[y][x];
            }
        }

        cout << '\n';
    }
}

//checking if walkable (basically if theres any walls or floors around)
bool Dungeon::checkWalkable(int x, int y) const {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        return false;
    }
    return grid[y][x] != '#';
}

//get tile
char Dungeon::getTile(int x, int y) const {
    return grid[y][x];
}

//set tile
void Dungeon::setTile(int x, int y, char tile) {
    grid[y][x] = tile;
}

//get width
int Dungeon::getWidth() const {
    return width;
}

//get width
int Dungeon::getHeight() const {
    return height;
}