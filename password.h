#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>

class Password {
public:
    /**
     * This method checks if the password has been used before.
     */
    static bool isPasswordUsed(const std::string& password);

    /**
     * This method generates a random password and saves it to a file.
     */
    static std::string generateAndSetPassword();

    /**
     * This method checks if the password strength.
     */
    static int checkPasswordStrength(const std::string& password);

    /**
     * This method displays * instead of the actual password.
     */
    static string getPasswordInput();

private:
    /**
     * This method generates a random password.
     */
    static std::string generatePassword(int length, bool includeLowercase, bool includeUppercase, bool includeSpecialChars, bool includeDigits);

    /**
     * This method checks what user want to do.
     */
    static bool getUserChoice();

};

#endif
