#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <cstdlib> //clear screen

using namespace std;

class Menu {
public:
    void showOptions();

private:
    void clearScreen();
    void doAction(int option);
};

#endif
