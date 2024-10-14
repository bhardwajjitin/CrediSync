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
void User::addCards(string card_num, string card_type, int pin){
    Card* new_card;
    if(card_type=="Debit"){
        new_card = new DebitCard(card_num, pin,"Debit",&balance,&limit,&transactionsleft);
    }
    else if(card_type == "Credit") {
        long long initial_limit = 10000;
        new_card = new CreditCard(card_num, pin,"Credit",initial_limit);
    }
   this->myCards.push_back(new_card);
}
Card* User::getcard(string Card_No) {
    auto Cardlist = this->myCards;
    for (auto card : Cardlist) {
        if (card->getcardno() == Card_No) {
            return card;
        }
    }
    return nullptr;
}
void User::printallCards(){
   vector<Card*> allcards = this->myCards;
for (auto &it:allcards) {
    it->printinfo();
}
}