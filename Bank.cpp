#include "Bank.hpp"

void Bank::adduser(string Name,string acc_no,long long balance){
   User user(Name,acc_no,balance);
   database[acc_no]=user;
}
void Bank::addCards(string card_num, string type, int pin, string acc_num){
    Card* new_card;
    if(type=="Debit"){
        long long balance = database[acc_num].getBalance();
        new_card = new DebitCard(card_num, pin,"Debit", balance);
    }
    else if(type == "Credit") {
        long long initial_limit = 10000;
        new_card = new CreditCard(card_num, pin,"Credit",initial_limit);
    }
   allusers[acc_num].push_back(new_card);
}
void Bank::printallCards(string acc_No){
   vector<Card*> allcards = allusers[acc_No];
for (auto &it:allcards) {
    it->printinfo();
}
}
string Bank::getUser(string Acc_No){
    if(database.find(Acc_No)!=database.end())return database[Acc_No].getName();
    return "";
}
string Bank::getcard(string Acc_No, string Card_No) {
    auto Cardlist = allusers[Acc_No];
    for (auto card : Cardlist) {
        if (card->getcardno() == Card_No) {
            return Card_No;
        }
    }
    return "";
}
void Bank::performTransaction(string type,string acc_No,string card_No,long long amount){
    vector<Card*>allcards=allusers[acc_No];
    for(auto it:allcards){
        if(it->getcardno()==card_No){
            it->transaction(type,amount);
        }
    }
}