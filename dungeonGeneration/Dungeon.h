#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>

class Dungeon {
    private:
        int width;
        int height;
        std::vector<std::vector<char>> grid;

    public:
        Dungeon(int w = 20, int h = 10);

        void generateFloor(int floorNumber);

        void render(int playerX, int playerY) const;

        bool checkWalkable(int x, int y) const;

        char getTile(int x, int y) const;

        void setTile(int x, int y, char tile);

        int getWidth() const;
        int getHeight() const;

};

#endif