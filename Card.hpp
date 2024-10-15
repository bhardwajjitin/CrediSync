#include <bits/stdc++.h>
using namespace std;

class Card{
    private:
    string card_number;
    int pin;
    protected:
    string type;
    bool isblock=false;
    public:
    virtual ~Card() {} 
    // constructor for the card class
   Card(const string& acc_num, int card_pin, string cardtype,bool flag)
    : card_number(acc_num), pin(card_pin), type(cardtype),isblock(flag) {}
   
    bool resetPin(int oldpin,int new_pin);
    string getcardno();
    int getpin();
    virtual bool transaction(string type, long long amount) = 0;  // Pure virtual function
    void printinfo();
    string getcardtype();
    bool iscardblock();
    void blockcard();
};
class DebitCard:public Card{
    long long *user_balance;
    long long *limitleft;
    int *transactionsleft;
public:
    DebitCard(string& cardNum, int cardpin,string cardtype,bool isblock,long long *balance,long long *limit,int *left) : Card(cardNum, cardpin,cardtype,isblock), user_balance(balance),limitleft(limit),transactionsleft(left) {}

    bool transaction(string type,long long amount) override;
};

class CreditCard:public Card{
    private:
    long long creditlimit;
    long long loan; 
public:
    CreditCard(string& cardNum, int cardpin,string cardtype,bool isblock,long long user_limit) : Card(cardNum, cardpin,cardtype,isblock),creditlimit(user_limit),loan(0){}

    bool transaction(string type,long long amount) override;
    bool hasloan();
};