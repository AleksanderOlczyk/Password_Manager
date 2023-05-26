#ifndef LOGINMENU_H
#define LOGINMENU_H

#include <iostream>
#include <fstream>
#include <string>

class LoginMenu {
public:
    static std::string masterPassword;
    static std::string fileName;
    void showOptions();

private:
    /**
     * This method clears the screen.
     */
    inline void clearScreen() {
        system("cls");
    }

    /**
     * This method logs in the user.
     */
    void logIn(const std::string& filename);

    /**
     * This method signs up the user.
     */
    void signUp();

    /**
     * This method checks if the fileName is already registered.
     */
    bool isRegistered(const std::string& username);

    void chooseFile();

    void provideFilePath();
};

#endif