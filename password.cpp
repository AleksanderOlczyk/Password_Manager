#include <iostream>
#include <algorithm>
#include "password.h"

using std::cout, std::cin, std::string, std::endl, std::ifstream, std::ofstream;

bool Password::isPasswordUsed(const string& username, const string& password) {
    string filename = username + "_passwords.txt";
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        if (line == password) {
            return true;
        }
    }

    return false;
}

void Password::generateAndSetPassword(const string& username) {
    int length;
    bool includeLowercase, includeUppercase, includeSpecialChars, includeDigits;

    cout << "Password Length: ";
    cin >> length;

    cout << "Include Lowercase Letters (Y/N): ";
    includeLowercase = getUserChoice();

    cout << "Include Uppercase Letters (Y/N): ";
    includeUppercase = getUserChoice();

    cout << "Include Special Characters (Y/N): ";
    includeSpecialChars = getUserChoice();

    cout << "Include Digits (Y/N): ";
    includeDigits = getUserChoice();

    string password = generatePassword(length, includeLowercase, includeUppercase, includeSpecialChars, includeDigits);

    while (isPasswordUsed(username, password)) {
        password = generatePassword(length, includeLowercase, includeUppercase, includeSpecialChars, includeDigits);
    }

    if (!password.empty())
        cout << "Generated password: " << password << endl;

    string filename = username + "_passwords.txt";
    ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << password << endl;
        file.close();

        cout << "Password saved to file: " << filename << endl;
    } else {
        cout << "Failed to open file for writing." << endl;
    }
}

string generatePassword(int length, bool includeLowercase, bool includeUppercase, bool includeSpecialChars, bool includeDigits) {
    const string lowercaseLetters = "abcdefghijklmnopqrstuvwxyz";
    const string uppercaseLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string specialChars = "!@#$%^&*";
    const string digits = "0123456789";

    string password;
    srand(static_cast<unsigned int>(time(nullptr)));

    string availableChars;
    if (includeLowercase)
        availableChars += lowercaseLetters;
    if (includeUppercase)
        availableChars += uppercaseLetters;
    if (includeSpecialChars)
        availableChars += specialChars;
    if (includeDigits)
        availableChars += digits;

    if (length < 4 || availableChars.empty()) {
        cout << "Invalid options. Please make sure to select at least one character type and a minimum length of 4." << endl;
    }

    if (includeLowercase)
        password += lowercaseLetters[rand() % lowercaseLetters.length()];
    if (includeUppercase)
        password += uppercaseLetters[rand() % uppercaseLetters.length()];
    if (includeSpecialChars)
        password += specialChars[rand() % specialChars.length()];
    if (includeDigits)
        password += digits[rand() % digits.length()];

    while (password.length() < length) {
        char c = availableChars[rand() % availableChars.length()];
        password += c;
    }

    std::random_shuffle(password.begin(), password.end());

    return password;
}

bool getUserChoice() {
    char choice;
    cin >> choice;
    return (choice == 'Y' || choice == 'y');
}

int Password::checkPasswordStrength(const string& password) {
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

    //Check if the password contains digits
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
