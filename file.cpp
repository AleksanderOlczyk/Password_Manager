#include <fstream>
#include "file.h"

std::string File::encryptPhrase(const std::string& str, const std::string& key) {
    std::string encryptedStr = str;

    ///
    cout << "Encrypt phrase master pass: " << key << endl;
    cout << "str: " << str << endl;
    ///
    for (size_t i = 0; i < encryptedStr.length(); i++) {
        encryptedStr[i] = static_cast<unsigned char>(str[i]) ^ static_cast<unsigned char>(key[i % key.length()]);
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

    file << "\xEF\xBB\xBF"; // BOM (Byte Order Mark) dla UTF-8
    ////
    cout << "Master password: " << masterPassword << endl;
    ////
    clearFile(filePath);
    std::string encryptedTestPhrase = encryptPhrase(testPhrase, masterPassword);
    ///
    std::cout << "Original test: " << testPhrase << std::endl;
    std::cout << "Encrypted test: " << encryptedTestPhrase << std::endl;
    ///
    file << encryptedTestPhrase << std::endl;

    std::string allCategoriesLine;
    for (const std::string& category : allCategories) {
        allCategoriesLine += category + "::";
    }

    if (!allCategoriesLine.empty())
        allCategoriesLine = allCategoriesLine.substr(0, allCategoriesLine.length() - 2);

    /////
    std::cout << "Category: " << allCategoriesLine << std::endl;
    /////

    if (!allCategoriesLine.empty()) {
        std::string EncryptedAllCategoriesLine = encryptString(allCategoriesLine);
        file << EncryptedAllCategoriesLine << std::endl;
        std::cout << "Encrypted category: " << EncryptedAllCategoriesLine << std::endl;
    }

    if (!names.empty()) {
        for (size_t i = 0; i < names.size(); i++) {
            std::string data =
                    names[i] + "::" + passwords[i] + "::" + categories[i] + "::" + services[i] + "::" + logins[i];
            ///
            std::cout << "Encrypted data from file: " << data << std::endl;
            ///
            std::string encryptedData = encryptString(data);
            ///
            std::cout << "Decrypted data: " << encryptedData << std::endl;
            ///

            file << encryptedData << std::endl;
        }
    }

    file.close();
    std::cout << "Data saved to file: " << filePath << std::endl;
    cin.ignore();
    cin.get();
}

std::string File::encryptString(const std::string& str) {
    std::string encryptedStr = str;

    ///
    cout << "Encrypt string master pass: " << masterPassword << endl;
    cout << "str: " << str << endl;
    ///
    for (size_t i = 0; i < encryptedStr.length(); i++) {
        encryptedStr[i] = static_cast<unsigned char>(str[i]) ^ static_cast<unsigned char>(masterPassword[i % masterPassword.length()]);
    }
    ///
    cout << "Encrypt string: " << encryptedStr << endl;
    ///
    return encryptedStr;
}

std::string File::decryptString(const std::string& str) {
    return encryptString(str); //Encryption and decryption are the same
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

    // pomijanie BOM, jeśli istnieje
    char bom[3];
    file.read(bom, 3);
    if (bom[0] == '\xEF' && bom[1] == '\xBB' && bom[2] == '\xBF') {
        // plik zawiera BOM, można go pominąć
    } else {
        // przewinięcie pliku do początku
        file.seekg(0);
    }

    names.clear();
    passwords.clear();
    categories.clear();
    services.clear();
    logins.clear();
    allCategories.clear();

    std::string line;
    std::getline(file, line);
    ///
    cout << "Master password: " << masterPassword << endl;
    std::string tmp = decryptPhrase(line, masterPassword);
    cout << "Decrypted test: " << tmp << endl;
    ///

    // Decrypt and split the categories
    std::string categoriesLine;
    std::getline(file, categoriesLine);
    ///
    cout << "Categories line: " << categoriesLine << endl;
    ///
    std::string decryptedCategoriesLine = decryptString(categoriesLine);
    std::vector<std::string> decryptedCategories = splitString(decryptedCategoriesLine, "::");

    /////
    std::cout << "Decrypted category line: " << decryptedCategoriesLine << std::endl;
    std::cout << "Decrypted categories: " << std::endl;
    for (const std::string& category : decryptedCategories) {
        std::cout << category << endl;
    }
    std::cout << "Decrypted categories end" << std::endl;
    /////

    // Add decrypted categories to allCategories set
    for (const std::string& category : decryptedCategories) {
        allCategories.insert(category);
    }

    ///
    std::cout << "\n\nDecrypted lines: " << std::endl;
    ///
    while (std::getline(file, line)) {
        std::string decryptedLine = decryptString(line);
        ///
        std::cout << "Decrypted line: " << decryptedLine << std::endl;
        ///

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

    ///
    cin.ignore();
    cin.get();
    ///
}

void File::clearFile(const std::string& filePath) {
    std::ofstream file(filePath, std::ofstream::out | std::ofstream::trunc);
    if (!file.is_open()) {
        std::cout << "Failed to open file for clearing: " << filePath << std::endl;
        return;
    }
    file.close();
}
