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
    void clearScreen();

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
     * This method checks the strength of a password.
     * @param password - password to check
     * @return strength level (0 - weak, 1 - medium, 2 - strong)
     */
    int checkPasswordStrength(const string &password);

    /**
     * This method checks if the password has been used before.
     * @param password - password to check
     * @return true if the password has been used before, false otherwise
     */
    bool isPasswordUsed(const string &username, const string &password);

    void generateAndSetPassword(const string &username);

    string generateStrongPassword();

    /**
     * This method signs out.
     */
    void logOut();
};

#endif
