#include <iostream>
#include "menu.h"
#include "password.h"

using namespace std;

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
        cout << "8. Log out" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose option: ";

        // Check if the input is a number.
        while (!(cin >> option) || option < 0 || option > 8) {
            cout << "Invalid input. Please enter a valid option: ";
            cin.clear();
            cin.ignore();
        }

        doAction(option);
    } while (option != 0);
}

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
        case 8:
            logOut();
            break;
    }

    cin.ignore();
    cin.get();
}

void Menu::addUserPassword() {
    string password;
    string username;

    cout << "Enter your username: ";
    cin >> username;

    cout << "Enter your password: ";
    cin >> password;

    // Check if the password has been used before
    if (Password::isPasswordUsed(username, password)) {
        cout << "This password has been used before." << endl;
        cout << "Do you want to set a new password? (y/n): ";

        char choice;
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            Password::generateAndSetPassword(username);
            return;
        }
    }

    // Check password strength
    int strength = Password::checkPasswordStrength(password);

    if (strength >= 3) {
        cout << "Your password is strong: " << strength << "/4." << endl;
    } else {
        cout << "Your password is weak: " << strength << "/4." << endl;
    }

    // Save the password to file
    string filename = username + "_passwords.txt";
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << password << endl;
        file.close();

        cout << "Password saved to file: " << filename << endl;
    } else {
        cout << "Failed to open file for writing." << endl;
    }

    cin.ignore();
    cin.get();
}

void Menu::logOut() {
    LoginMenu loginMenu;
    loginMenu.showOptions();
}
