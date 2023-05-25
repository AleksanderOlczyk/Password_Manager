#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>
#include <fstream>

class Password {
public:
    static bool isPasswordUsed(const std::string& username, const std::string& password);
    static void generateAndSetPassword(const std::string& username);
    static std::string generateStrongPassword();
    static int checkPasswordStrength(const std::string& password);
};

#endif
