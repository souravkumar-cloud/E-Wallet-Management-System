#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Utility function to convert string to lowercase
string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Class representing a User with private fields and improved encapsulation
class User {
private:
    string name;
    string email;
    string password;
    double balance;
    vector<string> transactionHistory;

public:
    // Constructors
    User() : name(""), email(""), balance(0) {}
    User(const string& name, const string& email, const string& password) 
        : name(name), email(email), password(password), balance(0) {}

    // Getters
    string getName() const { return name; }
    string getEmail() const { return email; }
    double getBalance() const { return balance; }

    // Password management
    bool checkPassword(const string& inputPassword) const {
        return inputPassword == password;
    }

    void changePassword(const string& oldPassword, const string& newPassword) {
        if (checkPassword(oldPassword)) {
            password = newPassword;
            cout << "Password changed successfully.\n";
        } else {
            cout << "Incorrect current password.\n";
        }
    }

    // Balance management methods
    void addBalance(double amount) {
        balance += amount;
        addTransaction("Added $" + to_string(amount) + " to wallet");
    }

    bool deductBalance(double amount) {
        if (balance >= amount) {
            balance -= amount;
            addTransaction("Deducted $" + to_string(amount) + " from wallet");
            return true;
        }
        return false;
    }

    // Transaction history methods
    void addTransaction(const string& transaction) {
        transactionHistory.push_back(transaction);
    }

    void showTransactions() const {
        if (transactionHistory.empty()) {
            cout << "No transactions found.\n";
        } else {
            cout << "Transaction History for " << email << ":\n";
            for (const auto& transaction : transactionHistory) {
                cout << "- " << transaction << endl;
            }
        }
    }
};

// Class for EWallet system
class EWallet {
private:
    unordered_map<string, User> users;

public:
    // Register a new user with unique email and password
    void registerUser(const string& name, const string& email, const string& password) {
        string lowerEmail = toLower(email);
        if (users.find(lowerEmail) == users.end()) {
            users[lowerEmail] = User(name, lowerEmail, password);
            cout << "User registered successfully.\n";
        } else {
            cout << "User with this email already exists.\n";
        }
    }

    // Change password for a user
    void changeUserPassword(const string& email, const string& oldPassword, const string& newPassword) {
        string lowerEmail = toLower(email);
        auto it = users.find(lowerEmail);
        if (it != users.end()) {
            it->second.changePassword(oldPassword, newPassword);
        } else {
            cout << "Invalid email.\n";
        }
    }

    // Add money to the user's wallet
    void addMoney(const string& email, double amt) {
        string lowerEmail = toLower(email);
        if (amt <= 0) {
            cout << "Invalid amount. Please enter a positive amount.\n";
            return;
        }
        if (users.find(lowerEmail) != users.end()) {
            users[lowerEmail].addBalance(amt);
            cout << "Added $" << amt << " to " << email << "'s wallet.\n";
        } else {
            cout << "User not found.\n";
        }
    }

    // Transfer money between users with password verification
    void sendMoney(const string& from_email, const string& to_email, double amt, const string& password) {
        string lowerFromEmail = toLower(from_email);
        string lowerToEmail = toLower(to_email);

        if (amt <= 0) {
            cout << "Invalid amount. Please enter a positive amount to transfer.\n";
            return;
        }

        if (users.find(lowerFromEmail) != users.end() && users.find(lowerToEmail) != users.end()) {
            if (users[lowerFromEmail].checkPassword(password)) {
                if (users[lowerFromEmail].deductBalance(amt)) {
                    users[lowerToEmail].addBalance(amt);
                    users[lowerFromEmail].addTransaction("Transferred $" + to_string(amt) + " to " + to_email);
                    users[lowerToEmail].addTransaction("Received $" + to_string(amt) + " from " + from_email);
                    cout << "Transferred $" << amt << " from " << from_email << " to " << to_email << ".\n";
                } else {
                    cout << "Insufficient balance.\n";
                }
            } else {
                cout << "Incorrect password.\n";
            }
        } else {
            cout << "Sender or recipient not found.\n";
        }
    }

    // View balance of a user with password verification
    void viewBalance(const string& email, const string& password) const {
        string lowerEmail = toLower(email);
        auto it = users.find(lowerEmail);
        if (it != users.end()) {
            if (it->second.checkPassword(password)) {
                cout << "Balance for " << email << " is $" << it->second.getBalance() << endl;
            } else {
                cout << "Incorrect password.\n";
            }
        } else {
            cout << "Invalid email.\n";
        }
    }

    // View transaction history of a user with password verification
    void viewTransactions(const string& email, const string& password) const {
        string lowerEmail = toLower(email);
        auto it = users.find(lowerEmail);
        if (it != users.end()) {
            if (it->second.checkPassword(password)) {
                it->second.showTransactions();
            } else {
                cout << "Incorrect password.\n";
            }
        } else {
            cout << "Invalid email.\n";
        }
    }
};

int main() {
    EWallet wallet;
    int choice;
    string name, email, toEmail, password, oldPassword, newPassword;
    double amount;

    do {
        cout << "\nE-Wallet Management System\n";
        cout << "1. Register User\n";
        cout << "2. Add Funds\n";
        cout << "3. Transfer Funds\n";
        cout << "4. View Balance\n";
        cout << "5. View Transaction History\n";
        cout << "6. Change Password\n";
        cout << "7. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Email: ";
            cin >> email;
            cout << "Enter Password: ";
            cin >> password;
            wallet.registerUser(name, email, password);
            break;

        case 2:
            cout << "Enter Email: ";
            cin >> email;
            cout << "Enter Amount to Add: ";
            cin >> amount;
            wallet.addMoney(email, amount);
            break;

        case 3:
            cout << "Enter Your Email: ";
            cin >> email;
            cout << "Enter Password: ";
            cin >> password;
            cout << "Enter Recipient Email: ";
            cin >> toEmail;
            cout << "Enter Amount to Transfer: ";
            cin >> amount;
            wallet.sendMoney(email, toEmail, amount, password);
            break;

        case 4:
            cout << "Enter Email: ";
            cin >> email;
            cout << "Enter Password: ";
            cin >> password;
            wallet.viewBalance(email, password);
            break;

        case 5:
            cout << "Enter Email: ";
            cin >> email;
            cout << "Enter Password: ";
            cin >> password;
            wallet.viewTransactions(email, password);
            break;

        case 6:
            cout << "Enter Email: ";
            cin >> email;
            cout << "Enter Current Password: ";
            cin >> oldPassword;
            cout << "Enter New Password: ";
            cin >> newPassword;
            wallet.changeUserPassword(email, oldPassword, newPassword);
            break;

        case 7:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid option! Please try again.\n";
            break;
        }
    } while (choice != 7);

    return 0;
}
