cmake_minimum_required(VERSION 3.20)
project(dungeon_rpg)

set(CMAKE_CXX_STANDARD 17)

add_executable(dungeon_rpg
    main.cpp
    Entity/Entity.cpp
    UI/UI.cpp
    Player/Player.cpp
    Inventory/Item.cpp
    Inventory/Consumable.cpp
    Inventory/Equipment.cpp
    Inventory/Inventory.cpp
    dungeonGeneration/Dungeon.cpp
    standardEnemies/StandardEnemy.cpp
    standardEnemies/Slime.cpp
    standardEnemies/Skeleton.cpp
    standardEnemies/Goblin.cpp
    standardEnemies/Troll.cpp
    standardEnemies/Boss.cpp
    

)
