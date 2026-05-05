#include "dungeonGeneration/Dungeon.h"
#include "Inventory/Consumable.h"
#include "Inventory/Equipment.h"
#include "Inventory/Inventory.h"
#include "Player/Player.h"
#include <ctime>
#include <iostream>

using namespace std;

int main(){
    srand(time(0));
    cout << "Dungeon RPG commencing..." << endl;

    // Temporary item system demo. Remove this block when items are added to gameplay.
    Player demoPlayer("Demo Hero");
    Inventory demoInventory;

    demoPlayer.takeDamage(25);
    demoInventory.addItem(new Consumable("Health Potion", "Restores a small amount of HP.", 10, 20));
    demoInventory.addItem(new Equipment("Rusty Sword", "An old sword with a dull edge.", 5, 3, 0, "Weapon"));

    cout << "\nItem demo before using potion:\n";
    demoInventory.displayInventory();

    demoInventory.useItem(0, demoPlayer);

    cout << "\nItem demo after using potion:\n";
    demoInventory.displayInventory();
    
    Dungeon dungeon(20, 10);

    dungeon.generateFloor(1);

    // pretend player is at (1,1)
    dungeon.render(1, 1);

    return 0;
}
