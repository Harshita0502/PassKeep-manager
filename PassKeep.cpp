#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

bool isStrongPassword(const std::string& password) {
    // Check length
    if (password.length() < 8) {
        return false;
    }

    // Check for lowercase, uppercase, digit, and special character
    bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;
    for (char ch : password) {
        if (islower(ch)) {
            hasLower = true;
        } else if (isupper(ch)) {
            hasUpper = true;
        } else if (isdigit(ch)) {
            hasDigit = true;
        } else if (ispunct(ch) || ch == ' ') {
            hasSpecial = true;
        }
    }

    // Check if all criteria are met
    return (hasLower && hasUpper && hasDigit && hasSpecial);
}

void savePassword(const std::string& siteName, const std::string& username, const std::string& password) {
    std::string folderName = "PassKeep";
    if (!fs::exists(folderName)) {
        fs::create_directory(folderName);
    }

    std::string fileName;
    std::cout << "Enter the file name (without extension) to save the password: ";
    std::cin >> fileName;

    std::ofstream outputFile(folderName + "/" + fileName + ".txt");
    if (outputFile.is_open()) {
        outputFile << "SiteName: " << siteName << std::endl;
        outputFile << "Username: " << username << std::endl;
        outputFile << "Password: " << password << std::endl;
        outputFile.close();
        std::cout << "Password saved successfully in " << folderName << "/" << fileName << ".txt\n";
    } else {
        std::cout << "Unable to save the password.\n";
    }
}

int main() {
    std::string password;
    bool strongPassword = false;

    while (!strongPassword) {
        std::cout << "Enter your password: ";
        std::cin >> password;

        if (isStrongPassword(password)) {
            std::cout << "Strong password!\n";

            char saveChoice;
            std::cout << "Do you want to save this password? (y/n): ";
            std::cin >> saveChoice;

            if (tolower(saveChoice) == 'y') {
                std::string siteName, username;
                std::cout << "Enter the site you want to use this password for: ";
                std::cin.ignore(); // Clearing input buffer
                std::getline(std::cin, siteName);
                std::cout << "Enter your username on the site: ";
                std::getline(std::cin, username);

                savePassword(siteName, username, password);
            }

            strongPassword = true;
        } else {
            std::cout << "Weak password! Password should contain at least 8 characters, including lowercase, uppercase, digit, and special character.\n";
        }
    }

    return 0;
}
