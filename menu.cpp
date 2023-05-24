#include <iostream>
#include <cstdlib>
#include <ctime>
#include "menu.h"

using namespace std;

/**
 * This method clears the screen.
 */
void Menu::clearScreen() {
    system("cls");
}

/**
 * This method shows the menu options.
 */
void Menu::showOptions() {
    int option;

    do {
        clearScreen();
        cout << "Menu:" << endl;
        cout << "1. Find passwords" << endl;
        cout << "2. Sort passwords" << endl;
        cout << "3. Add password" << endl;
        cout << "4. Edit password" << endl;
        cout << "5. Delete password" << endl;
        cout << "6. Add category" << endl;
        cout << "7. Delete category" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose option: ";

        // Check if the input is a number.
        while (!(cin >> option) || option < 0 || option > 7) {
            cout << "Invalid input. Please enter a valid option: ";
            cin.clear();
            cin.ignore();
        }

        doAction(option);
    } while (option != 0);
}

/**
 * This method executes the action.
 * @param option - action number
 */
void Menu::doAction(int option) {
    clearScreen();

    switch (option) {
        case 0:
            exit(0);
        case 1:
            cout << "Opcja numer 1" << endl;
            break;
        case 2:
            cout << "Opcja numer 2" << endl;
            break;
        case 3:
            addUserPassword();
            break;
        case 4:
            cout << "Opcja numer 4" << endl;
            break;
        case 5:
            cout << "Opcja numer 5" << endl;
            break;
        case 6:
            cout << "Opcja numer 6" << endl;
            break;
        case 7:
            cout << "Opcja numer 7" << endl;
            break;
    }

    cin.ignore();
    cin.get();
}

/**
 * This method adds a password.
 */
void Menu::addUserPassword() {
    string password;

    cout << "Enter your password: ";
    cin >> password;

    // Check password strength
    int strength = checkPasswordStrength(password);

    if (strength >= 3) {
        cout << "Your password is strong: " << strength << "\\3.\n";
    } else {
        cout << "Your password is weak: " << strength << "\\3.\n";
    }

    // Check if the password has been used before
    if (isPasswordUsed(password)) {
        cout << "This password has been used before." << endl;
    }

    cin.ignore();
    cin.get();
}

/**
 * This method checks the strength of a password.
 * @param password - password to check
 * @return strength level (0 - weak, 1 - medium, 2 - strong)
 */
int Menu::checkPasswordStrength(const string& password) {
    int length = password.length();
    if (length < 8) {
        return 0; // Weak password
    }

    //Check if the password contains uppercase letters
    bool hasUppercase = false;
    for (char c : password) {
        if (isupper(c)) {
            hasUppercase = true;
            break;
        }
    }

    //Check if the password contains lowercase letters
    bool hasLowercase = false;
    for (char c : password) {
        if (islower(c)) {
            hasLowercase = true;
            break;
        }
    }

    //Check if the password contains special characters
    bool hasSpecialChars = false;
    for (char c : password) {
        if (!isalnum(c)) {
            hasSpecialChars = true;
            break;
        }
    }

    //Check if the password contains special characters
    bool hasDigit = false;
    for (char c : password) {
        if (!isdigit(c)) {
            hasDigit = true;
            break;
        }
    }

    int strength = 0;
    if (hasUppercase) {
        strength++;
    }
    if (hasLowercase) {
        strength++;
    }
    if (hasSpecialChars) {
        strength++;
    }
    if (hasDigit) {
        strength++;
    }

    return strength;
}

/**
 * This method checks if a password has been used before.
 * @param password - password to check
 * @return true if the password has been used before, false otherwise
 */
bool Menu::isPasswordUsed(const string& password) {
    // TODO: Implement password checking logic
    return false;
}
