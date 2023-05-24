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

    void logIn();
    void signUp();
    bool isRegistered(const std::string& username);
};

#endif