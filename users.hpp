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
   int transactionsleft;
   public:
   User(const string& myname, const string& acc_no, long long mybalance,string acctype,long long initlimit,int left)
        : name(myname), accountNumber(acc_no), balance(mybalance),type(acctype),limit(initlimit), transactionsleft(left) {}
   string getName();
   long long getBalance();
   void addCards(string card_num, string type, int pin);
   Card* getcard(string card_no);
   void printallCards();
   string gettype();
   void deposit(long long amount);
   void transfer(User*receiver,long long amount);
   void checklimits();
};