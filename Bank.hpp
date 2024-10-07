#include<bits/stdc++.h>
#include "users.hpp"
#include "Card.hpp"
using namespace std;

class Bank{
    private:
    unordered_map<string,vector<Card*>>allusers;
    unordered_map<string,User>database;
    // Here I have used singelton pattern to create the single instance of the class
    Bank() {}
    Bank(const Bank&) = delete;
    Bank& operator=(const Bank&) = delete;
    public:
    static Bank& getInstance() {
        static Bank instance;
        return instance;
    }
    void adduser(string Name,string Acc_No,long long balance);
    string getUser(string Acc_No);
    void printallCards(string acc_no);
    void addCards(string acc_num, string type, int pin, string name);
    string getcard(string acc_no,string card_no);
    void performTransaction(string type,string acc_No,string card_no,long long amount);
};