#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "password.h"

bool Password::isPasswordUsed(const std::string& password) {
    std::ifstream file(filePath);
    std::string line;

    while (getline(file, line)) {
        if (line == password) {
            return true;
        }
    }

    return false;
}

std::string Password::generateAndSetPassword() {
    int length;
    bool includeLowercase, includeUppercase, includeSpecialChars, includeDigits;

    std::cout << "Password Length: ";
    std::cin >> length;

    std::cout << "Include Lowercase Letters (Y/N): ";
    includeLowercase = getUserChoice();

    std::cout << "Include Uppercase Letters (Y/N): ";
    includeUppercase = getUserChoice();

    std::cout << "Include Special Characters (Y/N): ";
    includeSpecialChars = getUserChoice();

    std::cout << "Include Digits (Y/N): ";
    includeDigits = getUserChoice();

    std::string password = generatePassword(length, includeLowercase, includeUppercase, includeSpecialChars, includeDigits);

    while (isPasswordUsed(password)) {
        password = generatePassword(length, includeLowercase, includeUppercase, includeSpecialChars, includeDigits);
    }

    if (!password.empty())
        std::cout << "Generated password: " << password << std::endl;

    return password;
}

std::string Password::generatePassword(int length, bool includeLowercase, bool includeUppercase, bool includeSpecialChars, bool includeDigits) {
    const std::string lowercaseLetters = "abcdefghijklmnopqrstuvwxyz";
    const std::string uppercaseLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string specialChars = "!@#$%^&*";
    const std::string digits = "0123456789";

    std::string password;
    srand(static_cast<unsigned int>(time(nullptr)));

    std::string availableChars;
    if (includeLowercase)
        availableChars += lowercaseLetters;
    if (includeUppercase)
        availableChars += uppercaseLetters;
    if (includeSpecialChars)
        availableChars += specialChars;
    if (includeDigits)
        availableChars += digits;

    if (length < 4 || availableChars.empty()) {
        std::cout << "Invalid options. Please make sure to select at least one character type and a minimum length of 4." << std::endl;
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

bool Password::getUserChoice() {
    char choice;
    std::cin >> choice;
    return (choice == 'Y' || choice == 'y');
}

int Password::checkPasswordStrength(const std::string& password) {
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

string Password::getPasswordInput() {
    string password;
    char c;

    while ((c = _getwch()) != '\r') {
        if (c == '\b') {
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        } else {
            cout << '*';
            password.push_back(c);
        }
    }

    cout << endl;
    return password;
}
