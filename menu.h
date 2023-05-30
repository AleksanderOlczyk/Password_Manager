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
    void showOptions(const std::string& masterKey, const std::string& filePath, const std::string& test);

private:
    /**
     * This method clears the screen.
     */
    inline void clearScreen() {
        system("cls");
    }

    /**
     * This method finds passwords.
     */
    void findPasswords();

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
