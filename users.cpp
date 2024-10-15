#include "users.hpp"
using namespace std;

string User::getName(){
      return name;
}
long long User::getBalance(){
      return balance;
}
string User::gettype(){
    return type;
}
void User::deposit(long long amount){
    balance+=amount;
    return;
}
void User::checklimits(){
cout << "You have " << transactionsleft << " transactions remaining and your account limit is " << limit << "." << endl;
    return;
}
void User::transfer(User*reciever,long long amount){
    if(limit!=-1){
        if(balance>=amount && limit>=amount){
            balance-=amount;
            reciever->balance+=amount;
            limit-=amount;
            cout<<amount<<" is Successfully transfer to the"<<reciever->getName()<<" Account"<<endl;
        }
        else if(limit<amount){
            cout<<"Sorry your limit is reached for your transaction"<<endl;
        }
        else{
            cout<<"Transfer of Amount is Failed due to insufficient Balance"<<endl;
        }
    }
    else{
        if(balance>=amount){
            balance-=amount;
            reciever->balance+=amount;
            cout<<amount<<" is Successfully transfer to the"<<reciever->getName()<<" Account"<<endl;
        }
        else{
            cout<<"Transfer of Amount is Failed due to insufficient Balance"<<endl;
        }
    }
}
void User::addCards(string card_num, string card_type, int pin,bool isblock){ 
    if(myCards.find(card_num)==myCards.end()){
        Card* new_card;
    if(card_type=="Debit"){
        new_card = new DebitCard(card_num, pin,"Debit",isblock,&balance,&limit,&transactionsleft);
    }
    else if(card_type == "Credit") {
        long long initial_limit = 10000;
        new_card = new CreditCard(card_num, pin,"Credit",isblock,initial_limit);
    }
     myCards[card_num]=new_card;
    }
    else{
    cout<<"Card with this card Number already exist for the user"<<endl;
    }
}
Card* User::getcard(string Card_No) {
    if(myCards.find(Card_No)!=myCards.end()){
        return myCards[Card_No];
    }
    return nullptr;
}
void User::printallCards(){
   unordered_map<string,Card*> allcards = this->myCards;
   cout<<"Card Number"<<" "<<"Card Type"<<" "<<"Card block status"<<endl;
for (auto &it:allcards) {
    it.second->printinfo();
}
}
unordered_map<string,Card*>User::getcards(){
    return myCards;
}
void User::deletecardfromuser(string cardnum){
    Card* mycard=getcard(cardnum);
     if (mycard->getcardtype() == "Credit") {
                    CreditCard* myCreditCard = dynamic_cast<CreditCard*>(mycard);
                    if (myCreditCard && myCreditCard->hasloan()) {
                        cout << "You have a loan on your credit card " << cardnum << ".\n";
                        int choice;
                        cout << "Do you want to repay the loan? (1: Yes, 2: No): ";
                        cin >> choice;

                        switch (choice) {
                            case 1: 
                                long long repaymentAmount;
                                cout << "Enter amount to repay: ";
                                cin >> repaymentAmount;
                                
                                if (myCreditCard->transaction("Deposit",repaymentAmount)) {
                                    cout << "Loan repaid successfully!" << endl;
                                    delete mycard;
                                } else {
                                    cout << "Repayment failed. Unable to delete the card." << endl;
                                    return;
                                }
                                break; 

                            case 2:
                                cout << "Cannot delete user. Outstanding loan on credit card." << endl;
                                return; 

                            default: 
                                cout << "Invalid choice. Cannot proceed." << endl;
                                return; 
                        }
                    }
                }
                else{
                delete mycard; 
                }
    myCards.erase(cardnum);
}