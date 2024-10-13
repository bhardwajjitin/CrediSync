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
void User::addCards(string card_num, string type, int pin){
    Card* new_card;
    if(type=="Debit"){
        new_card = new DebitCard(card_num, pin,"Debit",&balance,&limit);
    }
    else if(type == "Credit") {
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
}
void User::printallCards(){
   vector<Card*> allcards = this->myCards;
for (auto &it:allcards) {
    it->printinfo();
}
}