#include<bits/stdc++.h>

using namespace std;

class Transaction{
    private:
    string type;
    long long amount;
    long long balance;
    string status;
    string cardtype;
    public:
    Transaction(string transactiontype,long long amount,long long balance,string status,string cardtype){
       this->type=transactiontype;
       this->amount=amount;
       this->balance=balance;
       this->status=status;
       this->cardtype=cardtype;
    }
    void printinfo();
};