#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include "../Player/Player.h"
#include "../standardEnemies/StandardEnemy.h"

//easy to read result
enum BattleResult {
    PlayerWon,
    PlayerDied,
    PlayerFlee
};

class BattleSystem {
    public:
        BattleResult startBattle(Player& player, int x, int y, int floor);

    private:
        std::unique_ptr<StandardEnemy> createRandomEnemy(int x, int y, int floor);
};

#endif