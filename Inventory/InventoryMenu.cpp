#include "InventoryMenu.h"
#include "../UI/UI.h"

#include <iostream>
#include <limits>

using namespace std;

namespace InventoryMenu {
    void open(Player& player) {
        UI::clearScreen();
        cout << UI::CYAN << "Inventory\n" << UI::RESET;
        UI::printSeparator();

        player.getInventory().displayInventory();

        if (player.getInventory().isEmpty()) {
            UI::pressEnter();
            return;
        }

        cout << "\nEnter item number to use, or 0 to go back: ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << UI::RED << "Invalid choice." << UI::RESET << "\n";
            UI::pressEnter();
            return;
        }

        if (choice == 0) {
            return;
        }

        if (choice < 1 || choice > player.getInventory().getSize()) {
            cout << UI::RED << "Invalid item number." << UI::RESET << "\n";
            UI::pressEnter();
            return;
        }

        player.getInventory().useItem(choice - 1, player);
        UI::pressEnter();
    }
}