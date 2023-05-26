#include <fstream>
#include "file.h"

std::string File::encryptTestPhrase(const std::string& str, const std::string& key) {
    std::string encryptedStr = str;
    for (size_t i = 0; i < encryptedStr.length(); i++) {
        encryptedStr[i] = str[i] ^ key[i % key.length()];
    }
    return encryptedStr;
}

std::string File::decryptTestPhrase(const std::string& str, const std::string& key) {
    return encryptTestPhrase(str, key); //Encryption and decryption are the same
}

bool File::saveToFile(const std::string& filename, const std::string& content) {
    std::string encryptedContent = encryptTestPhrase(content, masterPassword);
    std::ofstream file(filename);
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
