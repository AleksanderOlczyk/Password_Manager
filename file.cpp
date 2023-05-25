#include <fstream>
#include "file.h"

std::string File::encryptString(const std::string& str, const std::string& appPassword) {
    std::string encryptedStr = str;
    std::string key = LoginMenu::masterPassword;
    for (size_t i = 0; i < encryptedStr.length(); i++) {
        encryptedStr[i] = str[i] ^ key[i % key.length()];
    }
    return encryptedStr;
}

std::string File::decryptString(const std::string& str, const std::string& key) {
    return encryptString(str, key); //Encryption and decryption are the same
}

bool File::saveToFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    file << content;
    file.close();
    return true;
}

std::string File::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return ""; //Failed to open file
    }
    std::string content((std::istreambuf_iterator<char>(file)),
                        (std::istreambuf_iterator<char>()));
    file.close();
    return content;
}
