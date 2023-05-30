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

void File::saveToFile() {
    std::ofstream file(filePath);
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
    std::cout << "Data saved to file: " << filePath << std::endl;
}

std::string File::encryptString(const std::string& str, const std::string& key) {
    std::string encryptedStr = str;
    for (size_t i = 0; i < encryptedStr.length(); i++) {
        encryptedStr[i] = str[i] ^ key[i % key.length()];
    }
    return encryptedStr;
}

std::string File::decryptString(const std::string& str, const std::string& key) {
    return encryptString(str, key); //Encryption and decryption are the same
}

std::vector<std::string> File::splitString(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }

    tokens.push_back(str.substr(start, end));

    return tokens;
}

void File::readFromFile() {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Failed to open file for reading." << std::endl;
        return;
    }

    // Read the encrypted test phrase from the first line
    std::string encryptedTestPhrase;
    std::getline(file, encryptedTestPhrase);

    // Decrypt the test phrase
    std::string decryptedTestPhrase = decryptPhrase(encryptedTestPhrase, masterPassword);
    if (decryptedTestPhrase != testPhrase) {
        std::cout << "Incorrect master password. Cannot decrypt the data." << std::endl;
        return;
    }

    // Read the categories from the second line
    std::string categoriesLine;
    std::getline(file, categoriesLine);

    // Decrypt and split the categories
    std::string decryptedCategoriesLine = decryptString(categoriesLine, masterPassword);
    std::vector<std::string> decryptedCategories = splitString(decryptedCategoriesLine, "::");
    categories.assign(decryptedCategories.begin(), decryptedCategories.end());

    std::string line;
    while (std::getline(file, line)) {
        // Decrypt the line
        std::string decryptedLine = decryptString(line, masterPassword);

        // Split the decrypted line into data fields
        std::vector<std::string> dataFields = splitString(decryptedLine, "::");
        if (dataFields.size() == 5) {
            names.push_back(dataFields[0]);
            passwords.push_back(dataFields[1]);
            categories.push_back(dataFields[2]);
            services.push_back(dataFields[3]);
            logins.push_back(dataFields[4]);
        }
    }

    file.close();
}
