#ifndef FILE_H
#define FILE_H

#include <string>

class File {
public:
    /**
     * This method encrypt test phrase.
     */
    static std::string encryptPhrase(const std::string& str, const std::string& key);

    /**
     * This method decrypt test phrase.
     */
    static std::string decryptPhrase(const std::string& str, const std::string& key);

    /**
     * This method encrypt string.
     */
    static std::string encryptString(const std::string& str);

    /**
     * This method decrypt string.
     */
    static std::string decryptString(const std::string& str);

    /**
     * This method save to file.
     */
    static void saveToFile();

    /**
     * This method split string to vector.
     */
    static std::vector<std::string> splitString(const std::string& str, const std::string& delimiter);

    /**
     * This method read from file.
     */
    static void readFromFile();

    /**
     * This method clear file data.
     */
    static void clearFile(const string &filePath);
};

#endif
