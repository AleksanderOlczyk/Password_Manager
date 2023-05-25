#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <cstdlib> //clear screen

using namespace std;

class Menu {
public:
    /**
     * This method shows the menu options.
     */
    void showOptions();

private:
    /**
     * This method clears the screen.
     */
    inline void clearScreen() {
        system("cls");
    }

    /**
     * This method executes the action.
     * @param option - action number
     */
    void doAction(int option);

    /**
     * This method adds a password.
     */
    void addUserPassword();

    /**
     * This method signs out.
     */
    void logOut();
};

#endif
