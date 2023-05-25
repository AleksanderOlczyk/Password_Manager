#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>
#include <fstream>

class Password {
public:
    /**
     * This method checks if the password is used.
     */
    static bool isPasswordUsed(const std::string& username, const std::string& password);

    /**
     * This method generates and sets a password for the user.
     */
    static void generateAndSetPassword(const std::string& username);

    /**
     * This method generates a password.
     */
    static string generatePassword(int length, bool includeLowercase, bool includeUppercase, bool includeSpecialChars, bool includeDigits);

    /**
     * This method checks the password strength.
     */
    static int checkPasswordStrength(const std::string& password);

    /**
     * This method checks if the user wants to include a character set.
     */
    static bool getUserChoice();
};

#endif
