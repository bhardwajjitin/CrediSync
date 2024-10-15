#include<bits/stdc++.h>
#include "users.hpp"
using namespace std;

class Bank{
    private:
    unordered_map<string,User*>database;
    unordered_set<string>allcards;
    // Here I have used singelton pattern to create the single instance of the class
    Bank() {}
    Bank(const Bank&) = delete;
    Bank& operator=(const Bank&) = delete;
    public:
    static Bank& getInstance() {
        static Bank instance;
        return instance;
    }
    void adduser(string Name,string Acc_No,long long balance,string type,long long initlimit,int left);
    User* getUser(string Acc_No);
    bool alreadyexists(string card_no);
    void deleteuser(string accnum);
    void deletecard(User*user,string cardnum);
};