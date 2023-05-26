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
        cout << "1. Chose file" << endl;
        cout << "2. Provide file absolut path" << endl;
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
                chooseFile();
                break;
            case 2:
                provideFilePath();
                break;
        }
    } while (option != 0);
}

void LoginMenu::logIn(const string& filename) {
    clearScreen();
    cout << "Log In" << std::endl;

    cout << "Selected file: " << filename << endl;
    cout << "Enter password: ";
    masterPassword = Password::getPasswordInput();

    string folderName = "users";
    ifstream file(folderName + "/" + filename);

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

    cout << "Invalid username or password. Please try again." << endl;
    cout << "Press enter to return to the menu..." << endl;
    cin.ignore(10000, '\n');
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

void LoginMenu::chooseFile() {
    clearScreen();
    std::string folderName = "users";
    std::string extension = ".txt";
    std::vector<std::string> files;

    for (const auto& entry : std::filesystem::directory_iterator(folderName)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            if (filename.size() >= extension.size() && std::equal(extension.rbegin(), extension.rend(), filename.rbegin())) {
                files.push_back(filename);
            }
        }
    }

    if (files.empty()) {
        cout << "No files with the .txt extension found." << endl;
    } else {
        for (size_t i = 0; i < files.size(); ++i) {
            cout << i + 1 << ". " << files[i] << endl;
        }

        int choice;
        cout << "Choose a file: ";

        while (!(cin >> choice) || choice < 1 || choice > files.size()) {
            cout << "Invalid input. Please enter a valid choice: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        string selectedFile = files[choice - 1];
        logIn(selectedFile);
    }

    cout << "Press enter to return to the menu..." << endl;
    cin.ignore();
    cin.get();
}


void LoginMenu::provideFilePath() {

}
