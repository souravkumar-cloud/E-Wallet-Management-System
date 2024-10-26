#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;
//Define the class with two constructor 
//this class make a user define data type
class User
{
public:
    string name;
    string email;
    double balance;
    //default constructor 
    User() : name(""), email(""), balance(0) {}
    //constructor taking argument
    User(string name, string email)
    {
        this->name = name;
        this->email = email;
        this->balance = 0;
    }
};
//this class is used to use data type of above class for storing the data in systematic manner
class EWallet
{
private:
//giving high level of security for the details of customer
    unordered_map<string, User> users;

public:
//this function is used to register new customer with unique gmail address
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
    //this function is use to add money to the wallet 
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
    //this function is use to send money from one wallet to another wallet
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
    //this function is use to show avalible money into the wallet
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
    //creating object 
    EWallet wallet;
    //choice variable is use in switch case to perform different functions accoding to the user 
    int choice;
    string name, email, toEmail;
    double amount;
//we use do while loop to use loop at least ones
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
