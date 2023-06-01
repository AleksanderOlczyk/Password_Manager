#include <iostream>
#include <set>
#include "menu.h"
#include "password.h"
#include "file.h"

using namespace std;

string masterPassword;
string filePath;
std::set<std::string> allCategories;

string testPhrase;
std::vector<std::string> names;
std::vector<std::string> passwords;
std::vector<std::string> categories;
std::vector<std::string> services;
std::vector<std::string> logins;

void Menu::showOptions(const std::string& masterKey, const std::string& fileAbsolutePath, const std::string& test) {
    int option;
    masterPassword = masterKey;
    filePath = fileAbsolutePath;
    testPhrase = test;

    File::readFromFile();

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
                findPasswords();
                break;
            case 2:
//                sortPasswords();
                cout << "Opcja numer 2" << endl;
                break;
            case 3:
                addUserPassword();
                break;
            case 4:
//                editPassword();
                cout << "Opcja numer 4" << endl;
                break;
            case 5:
//                deletePassword();
                cout << "Opcja numer 5" << endl;
                break;
            case 6:
                addCategory();
                break;
            case 7:
//                deleteCategory();
                cout << "Opcja numer 7" << endl;
                break;
            case 8:
                logOut();
                break;
        }
    } while (option != 0);
}

void Menu::findPasswords() {
    int selectedPassword = -1;
    string lastPassword;
    string passwordStars;

    while (true) {
        clearScreen();
        if (names.empty()) {
            cout << "No passwords found. Please add a password." << endl;
            cout << "Press enter to continue...";
            cin.ignore();
            cin.get();
            break;
        }
        for (int i = 0; i < names.size(); i++) {
            cout << i + 1 << ". Name: " << names[i] << " Password: ";

            if (selectedPassword == i + 1) {
                cout << lastPassword;
            } else {
                passwordStars = string(passwords[i].length(), '*');
                cout << passwordStars;
            }

            cout << " Category: " << categories[i] << " Service: " << services[i] << " Login: " << logins[i] << endl;
        }

        cout << "Enter the number to view the password (0 to return to the menu): ";

        while (!(cin >> selectedPassword) || selectedPassword < 0 || selectedPassword > names.size()) {
            cout << "Invalid input. Please enter a valid option: ";
            cin.clear();
            cin.ignore();
        }

        if (selectedPassword == 0) {
            break;
        }

        selectedPassword--;
        lastPassword = passwords[selectedPassword];
        cout << "Password: " << lastPassword << endl;

        cout << "Press enter to continue...";
        cin.ignore();
        cin.get();
    }

    showOptions(masterPassword, filePath, testPhrase);
}

void Menu::addUserPassword() {
    string name;
    string password;
    string category;
    string service = "none";
    string login = "none";

    while (true) {
        clearScreen();
        cout << "Add password:" << endl;
        cout << "1. Set password name (mandatory)" << endl;
        cout << "2. Set password (mandatory)" << endl;
        cout << "3. Set category (mandatory)" << endl;
        cout << "4. Set site url / service" << endl;
        cout << "5. Set login" << endl;
        cout << "6. Show summary" << endl;
        cout << "Choose option (0 to return): ";

        int option;

        if (!(cin >> option) || option < 0 || option > 6) {
            cout << "Invalid input. Please enter a valid option." << endl;
            cin.clear();
            cin.ignore();
            cin.get();
            continue;
        }

        switch (option) {
            case 0:
                return;
            case 1:
                cin.ignore();
                cout << "Enter password name: ";
                getline(cin, name);
                break;
            case 2: {
                cout << "Do you want to generate a password? (y/n): ";
                char choice;
                cin >> choice;

                if (choice == 'y' || choice == 'Y') {
                    clearScreen();
                    Password::generateAndSetPassword();
                } else {
                    cout << "Enter your password: ";
                    password = Password::getPasswordInput();
                }

                if (Password::isPasswordUsed(password)) {
                    cout << "This password has been used before." << endl;
                    cout << "Do you want to set a new password? (y/n): ";

                    cin >> choice;
                    if (choice == 'y' || choice == 'Y') {
                        password = Password::generateAndSetPassword();
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
                cout << "Press Enter to continue..." << endl;

                cin.ignore();
                cin.get();
                break;
            }
            case 3: {
                clearScreen();
                showCategories();
                cout << "Select category: ";

                int categoryOption;
                if (!(cin >> categoryOption) || categoryOption < 1 || categoryOption > allCategories.size()) {
                    cout << "Invalid input. Please enter a valid option." << endl;
                    cin.clear();
                    cin.ignore();
                    cin.get();
                    break;
                }

                auto it = allCategories.begin();
                std::advance(it, categoryOption - 1);
                category = *it;

                cin.ignore();
                break;
            }
            case 4:
                cin.ignore();
                cout << "Enter site url / service: ";
                getline(cin, service);
                break;
            case 5:
                cin.ignore();
                cout << "Enter login: ";
                getline(cin, login);
                break;
            case 6:
                clearScreen();
                if (name.empty() || password.empty() || category.empty()) {
                    cout << "Name, password, and category are mandatory fields. Please fill them in." << endl;
                    cin.ignore();
                    cin.get();
                    break;
                }

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
                    names.push_back(name);
                    passwords.push_back(password);
                    categories.push_back(category);
                    services.push_back(service);
                    logins.push_back(login);
                    File::saveToFile();
                    cout << "Password saved successfully." << endl;
                    cout << "Press enter to continue..." << endl;
                    cin.ignore();
                    cin.get();
                    return;
                } else {
                    cout << "Do you want to edit the password? (y/n): ";
                    cin >> choice;

                    if (choice == 'y' || choice == 'Y') {
                        continue;
                    } else {
                        cin.ignore();
                        cin.get();
                        return;
                    }
                }
        }
    }
}

void Menu::addCategory() {
    clearScreen();
    showCategories();

    std::string newCategory;
    std::cout << "Enter the name of the new category (or '0' to return to the menu): ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, newCategory);

    if (newCategory == "0") {
        return;
    }

    if (std::find(allCategories.begin(), allCategories.end(), newCategory) != allCategories.end()) {
        std::cout << "Category already exists." << std::endl;
        return;
    }

    allCategories.insert(newCategory);
    File::saveToFile();
    std::cout << "Category added: " << newCategory << std::endl;
}

void Menu::showCategories() {
    if (allCategories.empty()) {
        std::cout << "No categories found." << std::endl;
        return;
    }

    int i = 1;
    for (const string& existingCategory : allCategories) {
        cout << i << ". " << existingCategory << endl;
        i++;
    }
}

void Menu::logOut() {
    File::saveToFile();
    LoginMenu loginMenu;
    loginMenu.showOptions();
}