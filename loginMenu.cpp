#include <fstream>
#include "loginMenu.h"

using std::cout, std::cin, std::endl;

/**
 * This method clears the screen.
 */
void LoginMenu::clearScreen() {
    system("cls");
}

void LoginMenu::showOptions() {
    int option;

    do {
        clearScreen();
        cout << "Login Menu:" << endl;
        cout << "1. Log in" << endl;
        cout << "2. Sign up" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose option: ";

        while (!(cin >> option) || option < 0 || option > 2) {
            cout << "Invalid input. Please enter a valid option: ";
            cin.clear();
            cin.ignore();
        }

        switch (option) {
            case 0:
                exit(0);
            case 1:
                logIn();
                break;
            case 2:
                signUp();
                break;
        }
    } while (option != 0);
}

void LoginMenu::logIn() {
    clearScreen();
    cout << "Log In" << std::endl;

    string username;
    string password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");
    string line;

    bool found = false;
    while (getline(file, line)) {
        if (line == username + " " + password) {
            found = true;
            break;
        }
    }

    if (found) {
        cout << "Login successful!" << endl;
        Menu menu;
        menu.showOptions();
    } else {
        cout << "Invalid username or password. Please try again." << endl;
        cout << "Press enter to return to the menu..." << endl;
        cin.ignore();
        cin.get();
    }
}

void LoginMenu::signUp() {
    clearScreen();
    cout << "Sign Up" << endl;

    string username;
    string password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    if (isRegistered(username)) {
        cout << "Username already exists. Please choose a different username." << endl;
        cout << "Press enter to return to the menu..." << endl;
        cin.ignore();
        cin.get();
    } else {
        ofstream file("users.txt", ios::app);
        if (file.is_open()) {
            file << username << " " << password << endl;
            file.close();

            cout << "Registration successful!" << endl;
        } else {
            cout << "Failed to open users.txt for writing." << endl;
        }
    }
}

bool LoginMenu::isRegistered(const string& username) {
    ifstream file("users.txt");
    string line;

    while (getline(file, line)) {
        if (line.substr(0, username.length()) == username) {
            return true;
        }
    }

    return false;
}
