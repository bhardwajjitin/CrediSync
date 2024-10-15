#include "Bank.hpp"

void Bank::adduser(string Name,string acc_no,long long balance,string acctype,long long limit,int left){
if(database.find(acc_no)==database.end()){
   User* newuser=new User(Name,acc_no,balance,acctype,limit,left);
   database[acc_no]=newuser;
   }
   else{
    cout<<"User Already exists with this Account number"<<endl;
   }
}

User* Bank::getUser(string Acc_No){
    return database[Acc_No];
}

bool Bank::alreadyexists(string cardNo){
    if(allcards.find(cardNo)==allcards.end()){
        allcards.insert(cardNo);
        return true;
    }
    return false;
}
void Bank::deletecard(User*user,string cardnum){
    if(allcards.find(cardnum)!=allcards.end()){
        allcards.erase(cardnum);
        user->deletecardfromuser(cardnum);
    }
    else{
        cout<<"The Card Does Not Exist in The Database"<<endl;
    }
}
void Bank::deleteuser(string accnum) {
    if (database.find(accnum) != database.end()) {
        User* myuser = database[accnum];
        unordered_map<string, Card*> mycardmap = myuser->getcards();

        for (auto iterator:mycardmap) {
            string cardnum = iterator.first;
            Card* mycard = iterator.second;

            if (allcards.find(cardnum) != allcards.end()) {
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
                delete mycard; 
                allcards.erase(cardnum);
                mycardmap.erase(cardnum);
            } else {
                cout << "Card " << cardnum << " does not exist in the bank database." << endl;
            }
        }
        database.erase(accnum);
        delete myuser; 
        cout << "User with account number " << accnum << " has been deleted." << endl;
    } else {
        cout << "User does not exist with this account number." << endl;
    }
}
