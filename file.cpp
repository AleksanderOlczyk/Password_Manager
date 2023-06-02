#include <fstream>
#include "file.h"

std::string File::encryptPhrase(const std::string& str, const std::string& key) {
    std::string encryptedStr;
    encryptedStr.reserve(str.length());

    for (size_t i = 0; i < str.length(); i++) {
        char encryptedChar = str[i] ^ key[i % key.length()];
        std::stringstream stream;
        stream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(encryptedChar);
        encryptedStr += stream.str();
    }
    return encryptedStr;
}

std::string File::decryptPhrase(const std::string& str, const std::string& key) {
    std::string decryptedStr;
    decryptedStr.reserve(str.length() / 2);

    for (size_t i = 0; i < str.length(); i += 2) {
        std::string byteStr = str.substr(i, 2);
        char decryptedChar = static_cast<char>(std::stoi(byteStr, nullptr, 16) ^ key[(i / 2) % key.length()]);
        decryptedStr += decryptedChar;
    }
    return decryptedStr;
}

std::string File::encryptString(const std::string& str) {
    std::string encryptedStr;
    encryptedStr.reserve(str.length());

    for (size_t i = 0; i < str.length(); i++) {
        char encryptedChar = str[i] ^ masterPassword[i % masterPassword.length()];
        std::stringstream stream;
        stream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(encryptedChar);
        encryptedStr += stream.str();
    }
    return encryptedStr;
}

std::string File::decryptString(const std::string& str) {
    std::string decryptedStr;
    decryptedStr.reserve(str.length() / 2);

    for (size_t i = 0; i < str.length(); i += 2) {
        std::string byteStr = str.substr(i, 2);
        char decryptedChar = static_cast<char>(std::stoi(byteStr, nullptr, 16) ^ masterPassword[(i / 2) % masterPassword.length()]);
        decryptedStr += decryptedChar;
    }
    return decryptedStr;
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

    std::string allCategoriesLine;
    for (const std::string& category : allCategories) {
        allCategoriesLine += category + "::";
    }

    if (!allCategoriesLine.empty())
        allCategoriesLine = allCategoriesLine.substr(0, allCategoriesLine.length() - 2);

    if (!allCategoriesLine.empty()) {
        std::string EncryptedAllCategoriesLine = encryptString(allCategoriesLine);
        file << EncryptedAllCategoriesLine << std::endl;
    }

    if (!names.empty()) {
        for (size_t i = 0; i < names.size(); i++) {
            std::string data = names[i] + "::" + passwords[i] + "::" + categories[i] + "::" + services[i] + "::" + logins[i];
            std::string encryptedData = encryptString(data);
            file << encryptedData << std::endl;
        }
    }
    file << "\n" << std::endl;

    file.close();
//    std::cout << "Data saved to file: " << filePath << std::endl;
    cin.ignore();
    cin.get();
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

    names.clear();
    passwords.clear();
    categories.clear();
    services.clear();
    logins.clear();
    allCategories.clear();

    std::string line;
    std::getline(file, line);

    //Ignore test phrase
    std::string testPhrase = decryptPhrase(line, masterPassword);

    //Decrypt and split the categories
    std::string categoriesLine;
    std::getline(file, categoriesLine);
    std::string decryptedCategoriesLine = decryptString(categoriesLine);
    std::vector<std::string> decryptedCategories = splitString(decryptedCategoriesLine, "::");

    // Add decrypted categories to allCategories set
    for (const std::string& category : decryptedCategories) {
        allCategories.insert(category);
    }

    while (std::getline(file, line)) {
        std::string decryptedLine = decryptString(line);

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
