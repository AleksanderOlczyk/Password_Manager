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
        std::cout << "Failed to open file for writing: " << filePath << std::endl;
        return;
    }
    clearFile(filePath);

    std::string encryptedTestPhrase = encryptPhrase(testPhrase, masterPassword);
    file << encryptedTestPhrase << std::endl;

    //Encrypt allCategories to file
    std::string encryptedAllCategories;
    for (const std::string& category : allCategories) {
        encryptedAllCategories += category + "::";
    }

    if (!encryptedAllCategories.empty()) {
        encryptedAllCategories = encryptedAllCategories.substr(0, encryptedAllCategories.length() - 2);
    }
    encryptedAllCategories = encryptString(encryptedAllCategories, masterPassword);
    file << encryptedAllCategories << std::endl;

    // Save the data in the specified format
    for (int i = 0; i < names.size(); i++) {
        std::string data = names[i] + "::" + passwords[i] + "::" + categories[i] + "::" + services[i] + "::" + logins[i];
        std::string encryptedData = encryptString(data, masterPassword);
        file << encryptedData << std::endl;
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

//void File::readFromFile() {
//    std::ifstream file(filePath);
//    if (!file.is_open()) {
//        std::cout << "Failed to open file for reading." << std::endl;
//        return;
//    }
//    std::string tmp;
//    std::getline(file, tmp);
//
//    std::string categoriesLine;
//    std::getline(file, categoriesLine);
//
//    //Decrypt and split the categories
//    std::string decryptedCategoriesLine = decryptString(categoriesLine, masterPassword);
//    std::vector<std::string> decryptedCategories = splitString(decryptedCategoriesLine, "::");
//
//    //Add decrypted categories to allCategories set
//    for (const std::string& category : decryptedCategories) {
//        allCategories.insert(category);
//    }
//
//    std::string line;
//    while (std::getline(file, line)) {
//        //Decrypt the line
//        std::string decryptedLine = decryptString(line, masterPassword);
//
//        //Split the decrypted line into data fields
//        std::vector<std::string> dataFields = splitString(decryptedLine, "::");
//        if (dataFields.size() == 5) {
//            names.push_back(dataFields[0]);
//            passwords.push_back(dataFields[1]);
//            categories.push_back(dataFields[2]);
//            services.push_back(dataFields[3]);
//            logins.push_back(dataFields[4]);
//        }
//    }
//    file.close();
//}

void File::readFromFile() {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Failed to open file for reading." << std::endl;
        return;
    }

    names.clear();
    passwords.clear();
    categories.clear();
    services.clear();
    logins.clear();
    allCategories.clear();

    std::string line;
    std::getline(file, line);

    // Decrypt and split the categories
    std::string categoriesLine;
    std::getline(file, categoriesLine);
    std::string decryptedCategoriesLine = decryptString(categoriesLine, masterPassword);
    std::vector<std::string> decryptedCategories = splitString(decryptedCategoriesLine, "::");

    // Add decrypted categories to allCategories set
    for (const std::string& category : decryptedCategories) {
        allCategories.insert(category);
    }

    while (std::getline(file, line)) {
        std::string decryptedLine = decryptString(line, masterPassword);

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

void File::clearFile(const std::string& filePath) {
    std::ofstream file(filePath, std::ofstream::out | std::ofstream::trunc);
    if (!file.is_open()) {
        std::cout << "Failed to open file for clearing: " << filePath << std::endl;
        return;
    }
    file.close();
}
