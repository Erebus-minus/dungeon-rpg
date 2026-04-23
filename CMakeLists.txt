cmake_minimum_required(VERSION 3.20)
project(dungeon_rpg)

set(CMAKE_CXX_STANDARD 17)

add_executable(dungeon_rpg
    main.cpp
        standardEnemies/StandardEnemy.h
        standardEnemies/StandardEnemy.cpp
        standardEnemies/Slime.cpp
        standardEnemies/Slime.h
        standardEnemies/Skeleton.cpp
        standardEnemies/Skeleton.h
        standardEnemies/Goblin.cpp
        standardEnemies/Goblin.h
        standardEnemies/Troll.cpp
        standardEnemies/Troll.h


)