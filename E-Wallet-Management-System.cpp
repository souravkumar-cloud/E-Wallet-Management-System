#include<bits/stdc++.h>
using namespace std;
class User{
    public:
    string name;
    string email;
    double balance;
    User(string name,string email){
        this->name=name;
        this->email=email;
        balance=0; 
    }
};
class EWallet{
    private:
    unordered_map<string,User>users;
    public:
    void registerUser(const string &name,const string &email){
        if(users.find(email)==users.end()){
            users[email]=User(name,email);
            cout<<"User registered sucessfully"<<endl;
        }
        else cout<<"User exist already"<<endl;
    }
    void addMoney(const string email,double amt){
        if(users.find(email)!=users.end()){
            users[email].balance+=amt;
            cout<<"Added $"<<amt<<"to"<<email<<"s' wallet"<<endl;
        }
        else cout<<"user not found"<<endl;
    }
    void sendmoney(string &from_email,string &to_email,double amt){
        if(users.find(from_email)!=users.end()){
            if(users[from_email].balance>=amt){
                users[from_email].balance-=amt;
                users[to_email].balance+=amt;
                cout<<"Transfered $ "<<amt<<" from "<<from_email<<"to"<<to_email<<endl;
            }
            else cout<<"insufficents balance"<<endl;
        }
        else cout<<"User is not found\nInvalid email"<<endl;
    }
    void viewbalance(string &email){
        if(users.find(email)!=users.end()){
            cout<<"The Balance from "<<email<<" is "<<users[email].balance<<endl;
        }
        else cout<<"Invalid email "<<endl;
    }
};
int main(){
    
    return 0;
}