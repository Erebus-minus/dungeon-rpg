#pragma once
#include <string>
using namespace std;

namespace UI { 
    const string RESET = "\033[0m";
    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string YELLOW = "\033[33m";
    const string BLUE = "\033[34m";
    const string MAGENTA = "\033[35m";
    const string CYAN = "\033[36m";
    const string WHITE = "\033[37m";
    const string BOLD = "\033[1m";
    const string SLATE = "\033[90m";

    void clearScreen();
    void printTitle();
    void printSeparator();
    void pressEnter();
    void printHPBar(const string& name, int hp, int maxHP);
    void printXPBar(int xp, int xpMax);
    void printFloorHeader(int floor);
    void printGameOver();
    void printVictory();
    string colorize(const string& text, const string& color); 
}