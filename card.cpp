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
bool DebitCard::transaction(string transactiontype, long long amount) {
    if (*transactionsleft != -1) {
        if (transactiontype == "Deposit") {
            *user_balance += amount;
            *transactionsleft -= 1;
            cout << "Deposit successful! New balance: " << *user_balance << endl;
            return true;
        } 
        else if (transactiontype == "Withdraw") {
            if (*limitleft != -1 && *transactionsleft > 0) {
                if (*user_balance >= amount && *limitleft >= amount) {
                    *user_balance -= amount;
                    *limitleft -= amount;  
                    *transactionsleft -= 1; 
                    cout << "Withdraw successful! New balance: " << *user_balance << endl;
                    return true;
                } 
                else if (*limitleft < amount) {
                    cout << "Withdrawal limit exceeded! Contact your branch to increase your limits." << endl;
                    return false;
                } 
                else {
                    cout << "Insufficient funds for withdrawal!" << endl;
                    return false;
                }
            } else {
                cout << "Your transaction limit has been reached!" << endl;
                return false;
            }
        }
    } 
    else {
        if (transactiontype == "Deposit") {
            *user_balance += amount;
            cout << "Deposit successful! New balance: " << *user_balance << endl;
            return true;
        } 
        else if (transactiontype == "Withdraw") {
            if (*user_balance >= amount) {
                *user_balance -= amount;
                cout << "Withdraw successful! New balance: " << *user_balance << endl;
                return true;
            } else {
                cout << "Insufficient funds for withdrawal!" << endl;
                return false;
            }
        }
    }
    return false; 
}

 bool CreditCard::transaction(string transactiontype,long long amount) {
        if (transactiontype == "Deposit") {
            if (loan >= amount) {
                loan -= amount;
                cout << "Deposit successful! Remaining loan: " <<loan <<endl;
            } else {
                long long extra = amount - loan;
                loan = 0;
                creditlimit += extra;
                cout << "Loan repaid! New credit limit: " << creditlimit <<endl;
            }
            return true;
        } else if (transactiontype == "Withdraw") {
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