#include "menu.h"

/***
 * This is a menu class.
 */

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
        cout << "1. Opcja numer 1" << endl;
        cout << "2. Opcja numer 2" << endl;
        cout << "3. Opcja numer 3" << endl;
        cout << "4. Opcja numer 4" << endl;
        cout << "5. Opcja numer 5" << endl;
        cout << "6. Opcja numer 6" << endl;
        cout << "7. Opcja numer 7" << endl;
        cout << "0. Exit" << endl;
        cout << "Chose option: ";
        cin >> option;

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
            cout << "Exit" << endl;
            break;
        case 1:
            cout << "Opcja numer 1" << endl;
            cin.ignore();
            cin.get();
            break;
        case 2:
            cout << "Opcja numer 2" << endl;
            cin.ignore();
            cin.get();
            break;
        case 3:
            cout << "Opcja numer 3" << endl;
            cin.ignore();
            cin.get();
            break;
        case 4:
            cout << "Opcja numer 4" << endl;
            cin.ignore();
            cin.get();
            break;
        case 5:
            cout << "Opcja numer 5" << endl;
            cin.ignore();
            cin.get();
            break;
        case 6:
            cout << "Opcja numer 6" << endl;
            cin.ignore();
            cin.get();
            break;
        case 7:
            cout << "Opcja numer 7" << endl;
            cin.ignore();
            cin.get();
            break;
    }
}
