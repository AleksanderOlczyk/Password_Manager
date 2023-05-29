#include <fstream>
#include "file.h"

std::string File::encryptPhrase(const std::string& str, const std::string& key) {
    std::string encryptedStr = str;
    for (size_t i = 0; i < encryptedStr.length(); i++) {
        encryptedStr[i] = str[i] ^ key[i % key.length()];
    }
    return encryptedStr;
}

std::string File::decryptPhrase(const std::string& str, const std::string& key) {
    return encryptPhrase(str, key); //Encryption and decryption are the same
}

void File::savePassword(const std::string& name, const std::string& password, const std::string& category, const std::string& service, const std::string& login) {
    std::string content = name + "::" + password + "::" + category + "::" + service + "::" + login + "\n";
    saveToFile(content);
}

void File::saveToFile(const std::string& filename, const std::string& masterPassword, const std::vector<std::string>& names, const std::vector<std::string>& passwords, const std::vector<std::string>& categories, const std::vector<std::string>& services, const std::vector<std::string>& logins) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open file for writing." << std::endl;
        return;
    }

    // Encrypt the test phrase and write it on the first line
    std::string encryptedTestPhrase = encryptPhrase(testPhrase, masterPassword);
    file << encryptedTestPhrase << std::endl;

    // Save the data in the specified format
    for (size_t i = 0; i < names.size(); i++) {
        std::string encryptedName = encryptString(names[i], masterPassword);
        std::string encryptedPassword = encryptString(passwords[i], masterPassword);
        std::string encryptedCategory = encryptString(categories[i], masterPassword);
        std::string encryptedService = encryptString(services[i], masterPassword);
        std::string encryptedLogin = encryptString(logins[i], masterPassword);

        file << encryptedName << "::" << encryptedPassword << "::" << encryptedCategory << "::" << encryptedService << "::" << encryptedLogin << std::endl;
    }

    file.close();
    std::cout << "Data saved to file: " << filename << std::endl;
}

std::string File::encryptString(const std::string& str, const std::string& key) {
    std::string encryptedStr = str;
    for (size_t i = 0; i < encryptedStr.length(); i++) {
        encryptedStr[i] = str[i] ^ key[i % key.length()];
    }
    return encryptedStr;
}

void File::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return ""; //Failed to open file
    }
    std::string content((std::istreambuf_iterator<char>(file)),
                        (std::istreambuf_iterator<char>()));
    file.close();
    return content;
}
