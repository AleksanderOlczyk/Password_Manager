#include <fstream>
#include <filesystem>
#include "loginMenu.h"
#include "menu.cpp"
#include "file.cpp"
#include "password.cpp"

using std::cout, std::cin, std::endl, std::string;

const string testPhrase = "VeryWeakPassword123%";
std::string LoginMenu::masterPassword;
std::string LoginMenu::username;

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

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    LoginMenu::masterPassword = Password::getPasswordInput();

    string folderName = "users";
    string filename = folderName + "/" + username + "_passwords.txt";
    ifstream file(filename);

    if (isRegistered(filename)) {
        if (file) {
            string encryptedPassword;
            getline(file, encryptedPassword);

            string decryptedPhrase = File::decryptString(encryptedPassword, masterPassword);

            if (decryptedPhrase == testPhrase) {
                cout << "Login successful!" << endl;
                Menu menu;
                menu.showOptions();
                return;
            }
        }
    }

    cout << "Invalid username or password. Please try again." << endl;
    cout << "Press enter to return to the menu..." << endl;
    cin.ignore();
    cin.get();
}

void LoginMenu::signUp() {
    clearScreen();
    cout << "Sign Up" << endl;

    cout << "Enter username: ";
    cin >> username;

    string folderName = "users";
    string filename = folderName + "/" + username + "_passwords.txt";

    if (isRegistered(filename)) {
        cout << "Username already exists. Please choose a different username." << endl;
        cout << "Press enter to return to the menu..." << endl;
        cin.ignore();
        cin.get();
    } else {
        cout << "Enter password: ";
        cin >> masterPassword;

        ofstream file(filename);
        if (file.is_open()) {
            string encryptedTestPhrase = File::encryptString(testPhrase, masterPassword);
            file << encryptedTestPhrase << endl;
            file.close();

            cout << "Registration successful!" << endl;
        } else {
            cout << "Failed to open " << filename << " for writing." << endl;
        }
    }
}

bool LoginMenu::isRegistered(const string& filename) {
    return std::filesystem::exists(filename);
}
