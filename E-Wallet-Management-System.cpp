#include <bits/stdc++.h>
using namespace std;
class User
{
public:
    string name;
    string email;
    double balance;
    User(string name, string email)
    {
        this->name = name;
        this->email = email;
        this->balance = 0;
    }
};
class EWallet
{
private:
    unordered_map<string, User> users;

public:
    void registerUser(const string &name, const string &email)
    {
        if (users.find(email) == users.end())
        {
            users[email] = User(name, email);
            cout << "User registered sucessfully" << endl;
        }
        else
            cout << "User exist already" << endl;
    }
    void addMoney(const string email, double amt)
    {
        if (users.find(email) != users.end())
        {
            users[email].balance += amt;
            cout << "Added $" << amt << "to" << email << "s' wallet" << endl;
        }
        else
            cout << "user not found" << endl;
    }
    void sendmoney(string from_email, string to_email, double amt)
    {
        if (users.find(from_email) != users.end())
        {
            if (users.find(to_email) != users.end())
            {
                if (users[from_email].balance >= amt)
                {
                    users[from_email].balance -= amt;
                    users[to_email].balance += amt;
                    cout << "Transfered $ " << amt << " from " << from_email << "to" << to_email << endl;
                }
                else
                    cout << "insufficents balance" << endl;
            }
            else
                cout << "Recipient not found" << endl;
        }
        else
            cout << "User is not found\nInvalid email" << endl;
    }
    void viewbalance(string email)
    {
        if (users.find(email) != users.end())
        {
            cout << "The Balance from " << email << " is " << users[email].balance << endl;
        }
        else
            cout << "Invalid email " << endl;
    }
};
int main()
{
    EWallet wallet;
    int choice;
    string name, email, toEmail;
    double amount;

    do
    {
        cout << "E-Wallet Management System\n";
        cout << "1. Register User\n";
        cout << "2. Add Funds\n";
        cout << "3. Transfer Funds\n";
        cout << "4. View Balance\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Email: ";
            cin >> email;
            wallet.registerUser(name, email);
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
            cout << "Enter Recipient Email: ";
            cin >> toEmail;
            cout << "Enter Amount to Transfer: ";
            cin >> amount;
            wallet.sendmoney(email, toEmail, amount);
            break;

        case 4:
            cout << "Enter Email: ";
            cin >> email;
            wallet.viewbalance(email);
            break;

        case 5:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid option! Please try again.\n";
            break;
        }
    } while (choice != 5);

    return 0;
}