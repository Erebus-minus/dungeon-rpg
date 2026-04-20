cmake_minimum_required(VERSION 3.20)
project(dungeon_rpg)

set(CMAKE_CXX_STANDARD 17)

add_executable(dungeon_rpg
    main.cpp
    standardEnemies/StandardEnemy.cpp
    Entity/Entity.cpp

)