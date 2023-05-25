#ifndef FILE_H
#define FILE_H

#include <string>

class File {
public:
    static std::string encryptString(const std::string& str, const std::string& key);
    static std::string decryptString(const std::string& str, const std::string& key);
    static bool saveToFile(const std::string& filename, const std::string& content);
    static std::string readFromFile(const std::string& filename);
};

#endif
