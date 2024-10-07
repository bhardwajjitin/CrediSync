#include "Bank.hpp"
#include "ATM.hpp"
using namespace std;

int main() {
    int stop;
    Bank& PNB = Bank::getInstance();
    do {
        cout << "Press 1 to Create New User" << endl;
        cout << "Press 2 to Use Already Exist User" << endl;
        cout << "Press 3 to stop the execution" << endl;
        cin >> stop;

        if (stop == 1) {
            string Name, Acc_No;
            long long balance;
            cout << "Enter the Name of the User" << endl;
            cin >> Name;
            cout << "Enter the Account Number of the User" << endl;
            cin >> Acc_No;
            cout << "Enter the Initial Balance of the User" << endl;
            cin >> balance;
            PNB.adduser(Name, Acc_No, balance);
        }
        else if (stop == 2) {
            string Acc_No;
            cout << "Enter the Acc_No to get the User" << endl;
            cin >>Acc_No;
            string username = PNB.getUser(Acc_No);

            if (!username.empty()) {
                cout << "Hey " << username << endl;
                
                int flag = 1;
                cout << "Press 1 to Create New Card" << endl;
                cout << "Press 2 to Use Already Exist Card" << endl;
                cout << "To stop creating the card press 3" << endl;

                while (flag != 3) {
                    cout << "Enter the Card type -> 1.Debit 2.Credit" << endl;
                    int num;
                    cin >> num;

                    if (num < 1 || num > 2) {
                        cout << "Enter the Correct Card type" << endl;
                        continue;
                    }
                    string cardtype = (num == 1) ? "Debit" : "Credit";
                    string acc_num;
                    int pin;
                    cout << "Enter the 5 digits Card Number" << endl;
                    cin >> acc_num;
                    cout << "Enter the pin for the Card" << endl;
                    cin >> pin;
                    PNB.addCards(acc_num, cardtype, pin, Acc_No);
                    cout << "Press 1 to Create Another Card" << endl;
                    cout << "Press 2 to Use Existing Card" << endl;
                    cin >> flag;

                    if (flag == 2) {
                        cout << "Hey " << username << " You have the following Cards which one you want to use" << endl;
                        PNB.printallCards(Acc_No);
                        string card_no;
                        cout << "Enter the Card Number to choose the Card" << endl;
                        cin >> card_no;

                        string mycard = PNB.getcard(Acc_No, card_no);
                        if (!mycard.empty()) {
                            cout << "What operation do you want to perform?" << endl;
                            cout << "1. Deposit 2. Withdraw 3. Check Balance" << endl;
                            int operation;
                            cin >> operation;
                            string type="";
                            switch (operation) {
                                case 1:
                                    type="Deposit";
                                    break;
                                case 2:
                                    type="Withdraw";
                                    break;
                                case 3:
                                //    balance check logic here
                                   break;
                                default:
                                    cout << "Invalid operation." << endl;
                                    break;
                            }
                            if(type!=""){
                                long long amount;
                                cout<<"Enter the Transaction Amount"<<endl;
                                cin>>amount;
                                PNB.performTransaction(type,Acc_No,card_no,amount);
                            }
                        } else {
                            cout << "The Card Does Not exist for the Particular User" << endl;
                        }
                    } else if (flag != 1) {
                        cout << "Oops you have made a wrong choice" << endl;
                    }
                }
            }
        }
    } while (stop != 3);

    return 0;
}
