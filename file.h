#ifndef FILE_H
#define FILE_H

#include <string>

class File {
public:
    static std::string encryptTestPhrase(const std::string& str, const std::string& key);
    static std::string decryptTestPhrase(const std::string& str, const std::string& key);
    static bool saveToFile(const std::string& filename, const std::string& content);
    static std::string readFromFile(const std::string& filename);
};

#endif
