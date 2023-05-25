#ifndef LOGINMENU_H
#define LOGINMENU_H

#include <iostream>
#include <fstream>
#include <string>

class LoginMenu {
public:
    void showOptions();

private:
    void clearScreen();

    /**
     * This method logs in the user.
     */
    void logIn();

    /**
     * This method displays * instead of the actual password.
     */
    string getPasswordInput();

    void signUp();
    bool isRegistered(const std::string& username);
};

#endif