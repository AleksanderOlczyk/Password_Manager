#ifndef FILE_H
#define FILE_H

#include <string>

class File {
public:
    static std::string encryptPhrase(const std::string& str, const std::string& key);
    static std::string decryptPhrase(const std::string& str, const std::string& key);
    static void saveToFile();
    static std::string encryptString(const std::string& str, const std::string& key);
    static std::string decryptString(const std::string& str, const std::string& key);
    static std::vector<std::string> splitString(const std::string& str, const std::string& delimiter);
    static void readFromFile();
};

#endif
