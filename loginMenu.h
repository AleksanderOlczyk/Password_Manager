#ifndef LOGINMENU_H
#define LOGINMENU_H

#include <iostream>
#include <fstream>
#include <string>

class LoginMenu {
public:
    void showOptions();

private:
    /**
     * This method clears the screen.
     */
    void clearScreen();

    /**
     * This method logs in the user.
     */
    void logIn();

    /**
     * This method displays * instead of the actual password.
     */
    string getPasswordInput();

    /**
     * This method signs up the user.
     */
    void signUp();

    /**
     * This method checks if the username is already registered.
     */
    bool isRegistered(const std::string& username);
};

#endif