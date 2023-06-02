#ifndef LOGINMENU_H
#define LOGINMENU_H

#include <iostream>
#include <fstream>
#include <string>

class LoginMenu {
public:
    /**
     * This method display options.
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
     * This method log in the user.
     */
    void logIn(const std::string& filename);

    /**
     * This method sign up the user.
     */
    void signUp();

    /**
     * This method checks if the fileName is already registered.
     */
    bool isRegistered(const std::string& username);

    /**
     * This method shows all file in folder /users.
     */
    void chooseFile();

    /**
     * This method get the file path from user.
     */
    void provideFilePath();

    /**
     * This method add time stamp.
     */
    void addTimeStamp();
};

#endif