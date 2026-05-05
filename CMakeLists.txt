cmake_minimum_required(VERSION 3.20)
project(dungeon_rpg)

set(CMAKE_CXX_STANDARD 17)

add_executable(dungeon_rpg
    main.cpp
    Entity/Entity.cpp
    GameEngine/GameEngine.cpp
    UI/UI.cpp
    Player/Player.cpp
    standardEnemies/StandardEnemy.cpp
    standardEnemies/Slime.cpp
    standardEnemies/Skeleton.cpp
    standardEnemies/Goblin.cpp
    standardEnemies/Troll.cpp
    

)