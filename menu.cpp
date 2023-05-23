#include <iostream>
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
        while (!(cin >> option)) {
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
            cout << "Opcja numer 3" << endl;
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
