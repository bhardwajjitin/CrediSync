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
    void printinfo();
    string getcardno();
    virtual bool transaction(string type,long long amount);
};
class DebitCard:public Card{
    long long user_balance;
public:
    DebitCard(const std::string& cardNum, int pin,string type,long long balance) : Card(cardNum, pin,type), user_balance(balance) {}

    bool transaction(string type,long long amount) override {
        if (type == "deposit") {
            user_balance += amount;
            cout << "Deposit successful! New balance: " << user_balance << std::endl;
            return true;
        } else if (type == "withdraw") {
            if (user_balance >= amount) {
                user_balance -= amount;
                cout << "Withdraw successful! New balance: " << user_balance << std::endl;
                return true;
            } else {
                cout << "Insufficient funds for withdrawal!" << std::endl;
                return false;
            }
        }
        return false;
    }

};

class CreditCard:public Card{
    long long loan;
    long long limit;
public:
    CreditCard(const string& cardNum, int pin,string type,long long user_limit) : Card(cardNum, pin,type),limit(user_limit),loan(0){}

    bool transaction(string type,long long amount) override {
        if (type == "deposit") {
            if (loan >= amount) {
                loan -= amount;
                cout << "Deposit successful! Remaining loan: " <<loan <<endl;
            } else {
                double extra = amount - loan;
                loan = 0;
                limit += extra;
                cout << "Loan repaid! New credit limit: " << limit <<endl;
            }
            return true;
        } else if (type == "withdraw") {
            if (loan + amount <= limit) {
                loan += amount;
                cout << "Withdraw successful! Credit used: " <<limit
                          << " / " << limit <<endl;
                return true;
            } else {
                cout << "Credit limit exceeded!" <<endl;
                return false;
            }
        }
        return false;
    }
};