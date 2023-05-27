#ifndef FILE_H
#define FILE_H

#include <string>

class File {
public:
    static std::string encryptPhrase(const std::string& str, const std::string& key);
    static std::string decryptPhrase(const std::string& str, const std::string& key);
    static bool saveToFile(const std::string& content);
    static std::string readFromFile(const std::string& filename);

    static void savePassword(const string &name, const string &password, const string &category, const string &service,
                             const string &login);
};

#endif
