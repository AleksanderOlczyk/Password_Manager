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
    void showOptions(const std::string& masterKey, const std::string& filePath);

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
     * This method add new category.
     */
    void addCategory();

    /**
     * This method display all categories.
     */
    void showCategories();

    /**
     * This method display all passwords.
     */
    void showPasswords();

    /**
     * This method sort passwords.
     */
    void sortPasswords();

    /**
     * This method sort passwords by name.
     */
    void sortByName(bool ascending);

    /**
     * This method sort passwords by category.
     */
    void sortByCategory(bool ascending);

    /**
     * This method show passwords from category.
     */
    void displayPasswordsFromCategory();

    /**
     * This method display passwords.
     */
    void displayPasswords();

    /**
     * This method signs out.
     */
    void logOut();
};

#endif
