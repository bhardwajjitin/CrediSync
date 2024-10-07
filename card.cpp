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
