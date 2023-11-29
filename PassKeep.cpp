#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

struct User {
    string username;
    string birthdate;
    string password;
};

bool containsSubstring(const string& str, const string& substr) {
    return str.find(substr) != string::npos;
}

void printStrength(const string& password, const string& username, const string& birthdate) {
    int n = password.length();

    // Checking lower alphabet in string
    bool hasLower = false, hasUpper = false;
    bool hasDigit = false;
    int specialCount = 0; // Count of special characters
    string normalChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";
    string specialChars = "@#!$%^&*()_+=-~`.<>,;:'\"/?|\\][}{";

    for (int i = 0; i < n; i++) {
        if (islower(password[i]))
            hasLower = true;
        if (isupper(password[i]))
            hasUpper = true;
        if (isdigit(password[i]))
            hasDigit = true;

        // Check for special characters and count them
        if (specialChars.find(password[i]) != string::npos) {
            specialCount++;
        }
    }

    // Check if the password contains the username or birthdate
    bool containsUsername = containsSubstring(password, username);
    bool containsBirthdate = containsSubstring(password, birthdate);

    // Strength of password
    cout << "\nPassKeep Strength: ";
    if (hasLower && hasUpper && hasDigit &&
        specialCount >= 2 && (n >= 8) && !containsUsername && !containsBirthdate)
        cout << "Strong\n";
    else if ((hasLower || hasUpper || hasDigit) &&
            specialCount >= 2 && (n >= 6) && !containsUsername && !containsBirthdate)
        cout << "Moderate\n";
    else
        cout << "Weak\n";

    // Check if the password contains the username or birthdate and provide a warning
    if (containsUsername || containsBirthdate) {
        cout << "Warning: Avoid using your username or birthdate in the password.\n";
    }
}

void saveToFile(const string& filename, const string& username, const string& password) {
    ofstream file(filename);

    if (file.is_open()) {
        file << "Username: " << username << endl;
        file << "Password: " << password << endl;
        cout << "Credentials saved to file: " << filename << endl;
        file.close();
    } else {
        cerr << "Unable to open file " << filename << " for writing." << endl;
    }
}

int main() {
    cout << "PassKeep Manager and Strength Checker\n";
    cout << "-------------------------------------\n";

    vector<User> users; // Store user information

    char choice;
    cout << "Do you want to use PassKeep Manager? (y/n): ";
    cin >> choice;

    if (tolower(choice) == 'y') {
        string folderName = "PassKeep";
        fs::create_directory(folderName);

        string filename;
        cout << "Enter the name of the file to be saved (without extension): ";
        cin >> filename;
        filename = folderName + "/" + filename + ".txt";

        while (fs::exists(filename)) {
            cout << "File already exists. Enter a different name: ";
            cin >> filename;
            filename = folderName + "/" + filename + ".txt";
        }

        cout << "Enter your username: ";
        string username;
        cin >> username;

        cout << "Enter your birthdate (YYYYMMDD): ";
        string birthdate;
        cin >> birthdate;

        cout << "Enter your password: ";
        string password;
        cin >> password;

        saveToFile(filename, username, password);
    }

    // Password strength check for each user
    for (const auto& user : users) {
        cout << "\nPassKeep Strength for User: " << user.username << endl;
        printStrength(user.password, user.username, user.birthdate);
    }

    return 0;
}
