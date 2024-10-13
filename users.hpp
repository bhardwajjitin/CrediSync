#include<bits/stdc++.h>
#include "Card.hpp"
using namespace std;

class User{
   private:
   string name;
   string accountNumber;
   long long balance;
   string type;
   vector<Card*>myCards;
   long long limit;
   public:
   User(const string& name, const string& acc_no, long long balance,string acctype,long long initlimit)
        : name(name), accountNumber(acc_no), balance(balance),type(acctype),limit(initlimit) {}
   string getName();
   long long getBalance();
   void addCards(string card_num, string type, int pin);
   Card* getcard(string card_no);
   void printallCards();
   string gettype();
};