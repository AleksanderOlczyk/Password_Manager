#ifndef FILE_H
#define FILE_H

#include <string>

class File {
public:
    static std::string encryptPhrase(const std::string& str, const std::string& key);
    static std::string decryptPhrase(const std::string& str, const std::string& key);
    void saveToFile(const std::string& filename, const std::string& masterPassword, const std::vector<std::string>& names, const std::vector<std::string>& passwords, const std::vector<std::string>& categories, const std::vector<std::string>& services, const std::vector<std::string>& logins);
    std::string encryptString(const std::string& str, const std::string& key);
    void readFromFile(const std::string& filename);

    void savePassword(const std::string &name, const std::string &password, const std::string &category, const std::string &service,
                             const std::string &login);
};

#endif
