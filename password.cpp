#include <iostream>
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
    string generatedPassword = generateStrongPassword();
    cout << "Generated password: " << generatedPassword << endl;

    if (isPasswordUsed(username, generatedPassword)) {
        cout << "The generated password has been used before." << endl;
        cout << "Please enter a different password." << endl;
        return;
    }

    string filename = username + "_passwords.txt";
    ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << generatedPassword << endl;
        file.close();

        cout << "Password saved to file: " << filename << endl;
    } else {
        cout << "Failed to open file for writing." << endl;
    }
}

string Password::generateStrongPassword() {
    // Generate a strong password according to your criteria
    // Implement your logic here

    return "strongpassword123";
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
