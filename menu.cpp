#include <iostream>
#include "menu.h"
#include "password.h"
#include "file.h"

using namespace std;

string masterPassword;
string filePath;

void Menu::showOptions(const std::string& masterKey) {
    int option;
    masterPassword = masterKey;

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

        while (!(cin >> option) || option < 0 || option > 8) {
            cout << "Invalid input. Please enter a valid option: ";
            cin.clear();
            cin.ignore();
        }

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
    } while (option != 0);
}

void Menu::doAction(int option) {
    clearScreen();

    cin.ignore();
    cin.get();
}

void Menu::addUserPassword() {
    int option;

    do {
        clearScreen();
        cout << "Add password:" << endl;
        cout << "1. Set password name (mandatory)" << endl;
        cout << "2. Set password (mandatory)" << endl;
        cout << "3. Set category (mandatory)" << endl;
        cout << "4. Set site url / service" << endl;
        cout << "5. Set login" << endl;
        cout << "6. Show summary" << endl;
        cout << "0. Return" << endl;
        cout << "Choose option: ";

        if (!(cin >> option) || option < 0 || option > 6) {
            cout << "Invalid input. Please enter a valid option: ";
            cin.clear();
            cin.ignore();
        }
    } while (option < 0 || option > 6);

    string name;
    string password;
    string category;
    string service;
    string login;

    switch (option) {
        case 0:
            showOptions(masterPassword);
            break;
        case 1:
            //nie wiem czemu nie działa
            getline(cin, name);
            cout << "Enter password name: ";
            cin >> name;
            break;
        case 2: {
            cout << "Do you want to generate a password? (y/n): ";
            char choice;
            cin >> choice;

            if (choice == 'y' || choice == 'Y') {
                Password::generateAndSetPassword(masterPassword);
            } else {
                cout << "Enter your password: ";
                password = Password::getPasswordInput();
            }

            if (Password::isPasswordUsed(password)) {
                cout << "This password has been used before." << endl;
                cout << "Do you want to set a new password? (y/n): ";

                cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    Password::generateAndSetPassword(masterPassword);
                } else {
                    cout << "Enter your password: ";
                    password = Password::getPasswordInput();
                }
            }

            int strength = Password::checkPasswordStrength(password);
            if (strength >= 3) {
                cout << "Your password is strong: " << strength << "/4." << endl;
            } else {
                cout << "Your password is weak: " << strength << "/4." << endl;
            }

            cin.ignore();
            cin.get();
            break;
        }
        case 3:
            cin.ignore();
            cout << "Enter category: ";
            cin >> category;
            break;
        case 4:
            cin.ignore();
            cout << "Enter site url / service: ";
            cin >> service;
            break;
        case 5:
            cin.ignore();
            cout << "Enter login: ";
            cin >> login;
            break;
        case 6:
            cout << "Summary:" << endl;
            cout << "Name: " << name << endl;
            cout << "Password: " << password << endl;
            cout << "Category: " << category << endl;
            cout << "Service: " << service << endl;
            cout << "Login: " << login << endl;
            cout << "Do you want to save this password? (y/n): ";
            char choice;
            cin >> choice;

            if (choice == 'y' || choice == 'Y') {
                File::savePassword(name, password, category, service, login);
            } else {
                cout << "Password not saved." << endl;
                addUserPassword();
            }

            cin.ignore();
            cin.get();
            break;
    }
}

void Menu::logOut() {
    LoginMenu loginMenu;
    loginMenu.showOptions();
}
