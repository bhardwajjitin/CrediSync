#include <bits/stdc++.h>
using namespace std;

class Card{
    private:
    int pin;
    string card_number;
    string type;
    public:
    // constructor for the card class
    Card(const string&acc_num,int card_pin,string type)
    : card_number(acc_num),pin(card_pin){
        this->type=type;
    }
    
    void changepin(int new_pin);
    string getcardno();
    int getpin();
    virtual bool transaction(string type, long long amount) = 0;  // Pure virtual function
    void printinfo();
};
class DebitCard:public Card{
    long long *user_balance;
    long long *limitleft;
public:
    DebitCard(string& cardNum, int pin,string type,long long *balance,long long *limit) : Card(cardNum, pin,type), user_balance(balance),limitleft(limit) {}

    bool transaction(string type,long long amount) override;
};

class CreditCard:public Card{
    long long loan;
    long long creditlimit;
public:
    CreditCard(string& cardNum, int pin,string type,long long user_limit) : Card(cardNum, pin,type),creditlimit(user_limit),loan(0){}

    bool transaction(string type,long long amount) override;
};