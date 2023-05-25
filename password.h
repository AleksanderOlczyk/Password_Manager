#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>

class Password {
public:
    static bool isPasswordUsed(const std::string& username, const std::string& password);
    static void generateAndSetPassword(const std::string& username);
    static int checkPasswordStrength(const std::string& password);

private:
    static std::string generatePassword(int length, bool includeLowercase, bool includeUppercase, bool includeSpecialChars, bool includeDigits);
    static bool getUserChoice();
};

#endif
