#include<bits/stdc++.h>
using namespace std;

class User{
   private:
   string name;
   string accountNumber;
   long long balance;
   public:
   User(string user_name,string acc_no,long long balance){
      name=user_name;
      accountNumber=acc_no;
      this->balance=balance;
   }
   string getName(){
      return this->name;
   }
   long long getBalance(){
      return this->balance;
   }
};