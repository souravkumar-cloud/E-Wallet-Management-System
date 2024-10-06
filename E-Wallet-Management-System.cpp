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
};
int main(){
    
    return 0;
}