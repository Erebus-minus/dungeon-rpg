#include "dungeonGeneration/Dungeon.h"
#include "Inventory/Consumable.h"
#include "Inventory/Equipment.h"
#include "Inventory/Inventory.h"
#include "Player/Player.h"
#include "standardEnemies/Boss.h"
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

    // Temporary boss encounter demo. Remove this block when boss rooms are added to gameplay.
    Boss demoBoss({18, 8}, "Dungeon Boss", 100, 12, {1, 2}, 'B');

    cout << "\nBoss encounter demo:\n";
    cout << demoBoss.getName() << " starts in phase " << demoBoss.getPhase() << ".\n";
    demoBoss.attack(demoPlayer);

    cout << "\nThe player strikes the boss for 55 damage.\n";
    demoBoss.changeHP(55);
    demoBoss.updatePhase();
    cout << demoBoss.getName() << " is now in phase " << demoBoss.getPhase() << ".\n";
    demoBoss.attack(demoPlayer);

    return 0;
}
