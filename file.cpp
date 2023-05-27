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

bool File::saveToFile(const std::string& content) {
    std::string encryptedContent = encryptPhrase(content, masterPassword);
    std::ofstream file(filePath);
    if (!file.is_open()) {
        return false;
    }
    file << encryptedContent;
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
