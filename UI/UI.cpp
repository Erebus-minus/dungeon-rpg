#include "UI.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

namespace UI {
    void clearScreen(){
        cout << "\033[2J\033[H";

    }

    void printTitle() {
        cout << BOLD + MAGENTA;
        cout << R"(
         ____                                      ____                    _
        |  _ \ _   _ _ __   __ _  ___  ___  _ __ / ___|_ __ __ ___      _| | ___ _ __
        | | | | | | | '_ \ / _` |/ _ \/ _ \| '_ \ |   | '__/ _` \ \ /\ / / |/ _ \ '__|
        | |_| | |_| | | | | (_| |  __/ (_) | | | | |___| | | (_| |\ V  V /| |  __/ |
        |____/ \__,_|_| |_|\__, |\___|\___/|_| |_|\____|_|  \__,_| \_/\_/ |_|\___|_|
                            |___/
        
        )" << RESET << "\n";
    }

    void printSeparator() {
        cout << CYAN << " " << string(50, '-') << RESET << "\n";
    }
    
    void pressEnter() {
        cout << "\n  " << YELLOW
             << "[Press ENTER to continue...]" << RESET;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    void printHPBar(const string& name, int hp, int maxHP){
        const int barWidth = 20;
        int filled = (maxHP > 0) ? (hp * barWidth / maxHP) : 0;
        string bar = "[";
        for (int i = 0; i < barWidth; i++){
            bar += (i < filled) ? "#" : " ";
        }
        bar += "]";
        string hpColor = (hp > maxHP * 0.5) ? GREEN : (hp > maxHP * 0.25) ? YELLOW : RED;
        cout << " " << left << setw(10) << name << hpColor << bar << RESET << " " << hp << "/" << maxHP << "\n";
    }

    void printXPBar(int xp, int xpMax){
        const int barWidth = 20;
        int filled = (xpMax > 0) ? (xp * barWidth / xpMax) : 0;
        string bar = "[";
        for (int i = 0; i < barWidth; i++){
            bar += (i < filled) ? "=" : " ";
        }
        bar += "]";
        cout << " " << left << setw(10) << "XP" << CYAN << bar << RESET << " " << xp << "/" << xpMax << "\n";
    
    }

    void printFloorHeader(int floor){
        cout << BOLD + YELLOW << "\n === FLOOR " << floor << " ===" << RESET << "\n\n";
    }

    void printGameOver(){
        cout << BOLD + RED;
        cout << R"(
     ██████╗  █████╗ ███╗   ███╗███████╗    ██████╗ ██╗   ██╗███████╗██████╗ 
    ██╔════╝ ██╔══██╗████╗ ████║██╔════╝   ██╔═══██╗██║   ██║██╔════╝██╔══██╗
    ██║  ███╗███████║██╔████╔██║█████╗     ██║   ██║██║   ██║█████╗  ██████╔╝
    ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝     ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗
    ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗   ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║
     ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝    ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝
        )" << RESET << "\n";
        cout << "  Your adventure ends here. Better luck next time!\n\n";
        
        
    }

    void printVictory(){
        cout << BOLD + YELLOW;
        cout << R"(
        ██╗   ██╗██╗ ██████╗████████╗ ██████╗ ██████╗ ██╗██╗
        ██║   ██║██║██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗██║██║
        ██║   ██║██║██║        ██║   ██║   ██║██████╔╝██║██║
        ╚██╗ ██╔╝██║██║        ██║   ██║   ██║██╔══██╗╚═╝╚═╝
         ╚████╔╝ ██║╚██████╗   ██║   ╚██████╔╝██║  ██║██╗██╗
          ╚═══╝  ╚═╝ ╚═════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝╚═╝
        
        )" << RESET << "\n";
        cout << GREEN << "  You have conquered the dungeon!\n\n" << RESET;
    }

    string colorize(const string& text, const string& color){
        return color + text + RESET;
    }
}
