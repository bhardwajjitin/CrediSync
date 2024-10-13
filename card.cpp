#include "Card.hpp"
using namespace std;


void Card::changepin(int new_pin){
       if(pin!=new_pin){
       pin=new_pin;
        }
       else{
        cout<<"Please enter the new pin"<<endl;
       }
    }

void Card::printinfo(){
        cout<<this->card_number<<" "<<this->type<<endl;
    }
string Card::getcardno(){
    return this->card_number;
}
int Card::getpin(){
    return this->pin;
}
bool DebitCard::transaction(string type,long long amount){
        if (type == "Deposit") {
            *user_balance += amount;
            cout << "Deposit successful! New balance: " << *user_balance <<endl;
            return true;
        } else if (type == "Withdraw") {
            if(*limitleft!=-1){
            if (*user_balance >= amount && *limitleft>=amount) {
                *user_balance -= amount;
                *limitleft-=amount;
                cout << "Withdraw successful! New balance: " << *user_balance <<endl;
                return true;
            } 
            else if(*limitleft<amount){
                cout<<"Your Limit has been reached! Feel free the Contact your branch to increase your Limits"<<endl;
                return false;
            }
            else {
                cout << "Insufficient funds for withdrawal!" << std::endl;
                return false;
            }
            }
            else{
                if (*user_balance >= amount) {
                *user_balance -= amount;
                cout << "Withdraw successful! New balance: " << *user_balance <<endl;
                return true;
            } else {
                cout << "Insufficient funds for withdrawal!" << std::endl;
                return false;
            }
            }
        }
        return false;
    }

 bool CreditCard::transaction(string type,long long amount) {
        if (type == "Deposit") {
            if (loan >= amount) {
                loan -= amount;
                cout << "Deposit successful! Remaining loan: " <<loan <<endl;
            } else {
                double extra = amount - loan;
                loan = 0;
                creditlimit += extra;
                cout << "Loan repaid! New credit limit: " << creditlimit <<endl;
            }
            return true;
        } else if (type == "Withdraw") {
            if (loan + amount <= creditlimit) {
                loan += amount;
                cout << "Withdraw successful! Credit used: " <<creditlimit
                          << " / " << creditlimit <<endl;
                return true;
            } else {
                cout << "Credit limit exceeded!" <<endl;
                return false;
            }
        }
        return false;
    }