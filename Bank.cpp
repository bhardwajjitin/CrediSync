#include "Bank.hpp"

void Bank::adduser(string Name,string acc_no,long long balance,string acctype,long long limit){
   User* newuser=new User(Name,acc_no,balance,acctype,limit);
   database[acc_no]=newuser;
}

User* Bank::getUser(string Acc_No){
    return database[Acc_No];
}
