#include <filesystem>
#include "loginMenu.h"
#include "menu.cpp"
#include "file.cpp"
#include "password.cpp"

using std::cout, std::cin, std::endl, std::string;

void LoginMenu::showOptions() {
    testPhrase = "VeryWeakPassword123%";

    int option;
    do {
        clearScreen();
        cout << "Login Menu:" << endl;
        cout << "1. Chose file" << endl;
        cout << "2. Provide file absolut path" << endl << endl;
        cout << "3. Create new file" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose option: ";

        while (!(cin >> option) || option < 0 || option > 3) {
            cout << "Invalid input. Please enter a valid option: ";
            cin.clear();
            cin.ignore();
        }

        switch (option) {
            case 0:
                exit(0);
            case 1:
                chooseFile();
                break;
            case 2:
                provideFilePath();
                break;
            case 3:
                signUp();
                break;
        }
    } while (option != 0);
}

void LoginMenu::logIn(const string& filename) {
    clearScreen();
    cout << "Log In" << std::endl;

    cout << "Selected file: " << filename << endl;
    cout << "Enter password: ";
    masterPassword = Password::getPasswordInput();

    string folderName = "users";
    filePath = folderName + "/" + filename;

    ifstream file(filePath);
    if (file) {
        string encryptedPhrase;
        getline(file, encryptedPhrase);
        string decryptedPhrase = File::decryptPhrase(encryptedPhrase, masterPassword);

        if (decryptedPhrase == testPhrase) {
            cout << "Login successful!" << endl;
            Menu menu;
            menu.showOptions(masterPassword, filePath);
            return;
        }
    }

    addTimeStamp();
    cout << "Invalid fileName or password. Please try again." << endl;
    cout << "Press enter to return to the menu..." << endl;
    cin.ignore();
    cin.get();
}

void LoginMenu::signUp() {
    clearScreen();
    cout << "Create file" << endl;

    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;

    string folderName = "users";
    string fileAbsolutPath = folderName + "/" + fileName + ".txt";

    if (isRegistered(fileAbsolutPath)) {
        cout << "File name already exists. Please choose a different fileName." << endl;
        cout << "Press enter to return to the menu..." << endl;
        cin.ignore();
        cin.get();
    } else {
        cout << "Enter password: ";
        cin >> masterPassword;

        ofstream file(fileAbsolutPath);
        if (file.is_open()) {
            filePath = fileAbsolutPath;

            names.clear();
            passwords.clear();
            categories.clear();
            services.clear();
            logins.clear();

            allCategories.clear();
            allCategories.insert("Social Media");
            allCategories.insert("Work");
            allCategories.insert("None");

            File::saveToFile();
            file.close();

            cout << "Registration successful!" << endl;
        } else {
            cout << "Failed to open " << fileAbsolutPath << " for writing." << endl;
        }
    }
}

bool LoginMenu::isRegistered(const string& fileAbsolutPath) {
    return std::filesystem::exists(fileAbsolutPath);
}

void LoginMenu::chooseFile() {
    clearScreen();
    std::string folderName = "users";
    std::string extension = ".txt";
    std::vector<std::string> files;

    for (const auto& entry : std::filesystem::directory_iterator(folderName)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            if (filename.size() >= extension.size() && std::equal(extension.rbegin(), extension.rend(), filename.rbegin())) {
                files.push_back(filename);
            }
        }
    }

    if (files.empty()) {
        cout << "No files with the .txt extension found." << endl;
    } else {
        for (size_t i = 0; i < files.size(); ++i) {
            cout << i + 1 << ". " << files[i] << endl;
        }

        int choice;
        cout << "Choose a file (0 to return to menu): ";
        while (!(cin >> choice) || choice < 1 || choice > files.size()) {
            cout << "Invalid input. Please enter a valid choice: ";
            cin.clear();
            if (choice == 0)
                showOptions();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        string selectedFile = files[choice - 1];
        logIn(selectedFile);
    }

    cout << "Press enter to return to the menu..." << endl;
    cin.ignore();
    cin.get();
}

void LoginMenu::provideFilePath() {
    clearScreen();
    string extension = ".txt";

    cout << "Enter the file path (including the .txt extension) (0 return to menu): ";
    cin >> filePath;

    if (filePath == "0")
        showOptions();

    if (filePath.size() < extension.size() || !std::equal(extension.rbegin(), extension.rend(), filePath.rbegin())) {
        cout << "Invalid file path. The file should have the .txt extension." << endl;
    } else {
        if (!std::filesystem::exists(filePath)) {
            cout << "The specified file does not exist." << endl;
        } else {
            cout << "Enter password: ";
            masterPassword = Password::getPasswordInput();

            ifstream file(filePath);
            if (file) {
                string encryptedPhrase;
                getline(file, encryptedPhrase);
                string decryptedPhrase = File::decryptPhrase(encryptedPhrase, masterPassword);

                if (decryptedPhrase == testPhrase) {
                    cout << "Login successful!" << endl;
                    Menu menu;
                    menu.showOptions(masterPassword, filePath);
                    return;
                }
            }
        }
    }

    addTimeStamp();
    cout << "Invalid fileName or password. Please try again." << endl;
    cout << "Press enter to return to the menu..." << endl;
    cin.ignore();
    cin.get();
}

string generateRandomChars(int length) {
    const string characters = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int charactersLength = characters.length();

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    string randomString;
    for (int i = 0; i < length; ++i) {
        int randomIndex = std::rand() % charactersLength;
        randomString += characters[randomIndex];
    }

    return randomString;
}

void LoginMenu::addTimeStamp() {
    time_t now = time(nullptr); //system time
    tm* timeinfo = localtime(&now); //detailed information about time

    char timestamp[9];
    strftime(timestamp, sizeof(timestamp), "%T", timeinfo);

    string encryptedData = generateRandomChars(10) + to_string(timeinfo->tm_year + 1900) + generateRandomChars(11) +
                           to_string(timeinfo->tm_mon + 1) + generateRandomChars(12) +
                           to_string(timeinfo->tm_mday) + generateRandomChars(13) +
                           to_string(timeinfo->tm_hour) + generateRandomChars(14) +
                           to_string(timeinfo->tm_min) + generateRandomChars(15) +
                           to_string(timeinfo->tm_sec);

    ofstream file(filePath, std::ios_base::app);
    if (file) {
        file << encryptedData << endl;
        file.close();
    }
}
