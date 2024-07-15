#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

struct User {
    string username;
    string password;
};

void registerUser(unordered_map<string, string>& users) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    if (users.find(username) != users.end()) {
        cout << "Username already exists. Please try a different one." << endl;
        return;
    }
    cout << "Enter password: ";
    cin >> password;

    users[username] = password;
    ofstream file("users.txt", ios::app);
    file << username << " " << password << endl;
    file.close();

    cout << "Registration successful!" << endl;
}

bool loginUser(const unordered_map<string, string>& users) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    auto it = users.find(username);
    if (it != users.end() && it->second == password) {
        cout << "Login successful!" << endl;
        return true;
    }
    else {
        cout << "Invalid username or password." << endl;
        return false;
    }
}

unordered_map<string, string> loadUsers() {
    unordered_map<string, string> users;
    ifstream file("users.txt");
    string username, password;
    while (file >> username >> password) {
        users[username] = password;
    }
    file.close();
    return users;
}

int main() {
    unordered_map<string, string> users = loadUsers();
    int choice;

    do {
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            registerUser(users);
            break;
        case 2:
            loginUser(users);
            break;
        case 3:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
