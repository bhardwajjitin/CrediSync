#include "Bank.hpp"
#include "ATM.hpp"
using namespace std;

int main() {
    Bank& PNB = Bank::getInstance();  // Singleton Bank instance
    cout << "==== Welcome to the PNB Bank System ====" << endl;

    while (true) {
        cout << "\nMain Menu:" << endl;
        cout << "1. Create New User" << endl;
        cout << "2. Login to Existing User" << endl;
        cout << "3. Exit the System" << endl;
        cout << "Please enter your choice: ";
        int mainOption;
        cin >> mainOption;

        switch (mainOption) {
            case 1: {
                // Create a new user
                string name, accNo;
                long long balance;
                int type;
                cout << "Enter the User's Name: ";
                cin >> name;
                cout << "Enter the User's Account Number: ";
                cin >> accNo;
                cout << "Enter the Initial Balance: ";
                cin >> balance;
                cout<<"Enter the Type of Account \n 1.Savings \n 2.Current"<<endl;
                cin>>type;
                if(type==1){
                    PNB.adduser(name, accNo, balance,"Savings",50000);
                }
                else if(type==2){
                    PNB.adduser(name, accNo, balance,"Current",-1);
                }
                else{
                    cout<<"Please Enter the Valid Choice"<<endl;
                    continue;
                }
                cout<<" Account for " << name << " created successfully!" << endl;
                break;
            }
            case 2: {
                // User login
                string accNo;
                cout << "Enter Account Number to Login: ";
                cin >> accNo;
                User* currentUser = PNB.getUser(accNo);

                if (currentUser == nullptr) {
                    cout << "Invalid Account Number! Try again." << endl;
                    break;
                }

                bool userLoggedIn = true;
                cout << "\nWelcome, " << currentUser->getName() << "!" << endl;
                while (userLoggedIn) {
                    cout << "1. Create New Card" << endl;
                    cout << "2. Use Existing Card" << endl;
                    cout << "3. Balance Enquiry" << endl;
                    cout << "4. Deposit Money" << endl;
                    cout << "5. Transfer Funds to Another User" << endl;
                    cout << "6. Transfer Funds Between Own Accounts" << endl;
                    cout << "7. Logout" << endl;
                    cout << "Enter your choice: ";
                    int userOption;
                    cin >> userOption;

                    switch (userOption) {
                        case 1: {
                            // Create a new card
                            int cardType;
                            cout << "Select Card Type: 1. Debit  2. Credit: ";
                            cin >> cardType;

                            if (cardType >= 1 && cardType <= 2) {
                                string cardNo;
                                int pin;
                                cout << "Enter 5-digit Card Number: ";
                                cin >> cardNo;
                                cout << "Set a 4-digit PIN for the Card: ";
                                cin >> pin;

                                string cardTypeStr = (cardType == 1) ? "Debit" : "Credit";
                                currentUser->addCards(cardNo, cardTypeStr, pin);
                                cout << cardTypeStr<<" Card created successfully!" << endl;
                            } else {
                                cout << "Invalid card type!" << endl;
                            }
                            break;
                        }
                        case 2: {
                            // Use an existing card
                            currentUser->printallCards();
                            string cardNo;
                            cout << "Enter the Card Number: ";
                            cin >> cardNo;
                            Card* selectedCard = currentUser->getcard(cardNo);

                            if (selectedCard != nullptr) {
                                int cardPin;
                                cout << "Enter Card PIN for verification: ";
                                cin >> cardPin;

                                if (selectedCard->getpin() == cardPin) {
                                    bool cardSessionActive = true;
                                    while (cardSessionActive) {
                                        int cardOption;
                                        cout << "\n1. Deposit\n2. Withdraw\n3. Check Balance\n4. End Session" << endl;
                                        cout << "Enter your choice: ";
                                        cin >> cardOption;

                                        string type = "";
                                        long long amount;
                                        switch (cardOption) {
                                            case 1:
                                                type = "Deposit";
                                                cout << "Enter amount to deposit: ";
                                                cin >> amount;
                                                break;
                                            case 2:
                                                type = "Withdraw";
                                                cout << "Enter amount to withdraw: ";
                                                cin >> amount;
                                                break;
                                            case 3:
                                                cout << "Your current balance: " << currentUser->getBalance() << endl;
                                                continue;
                                            case 4:
                                                cardSessionActive = false;
                                                cout << "Ending session for card." << endl;
                                                continue;
                                            default:
                                                cout << "Invalid operation." << endl;
                                                continue;
                                        }

                                        if (!type.empty()) {
                                            if (selectedCard->transaction(type, amount)) {
                                                cout << "Transaction successful! New Balance: " << currentUser->getBalance() << endl;
                                            } else {
                                                cout << "Transaction failed!" << endl;
                                            }
                                        }
                                    }
                                } else {
                                    cout << "Incorrect PIN!" << endl;
                                }
                            } else {
                                cout << "Invalid Card Number!" << endl;
                            }
                            break;
                        }
                        case 3:
                            // Balance enquiry
                            cout << "Your current balance for your <<: " << currentUser->getBalance() << endl;
                            break;
                        case 4: {
                            // Deposit money
                            long long amount;
                            cout << "Enter amount to deposit: ";
                            cin >> amount;
                            // currentUser->deposit(amount);
                            cout << "Deposit successful! New Balance: " << currentUser->getBalance() << endl;
                            break;
                        }
                        case 5:
                            // Transfer to another account (implementation needed)
                            cout << "Enter recipient account number and amount: " << endl;
                            // Code for transfer
                            break;
                        case 6:
                            // Transfer within own accounts (implementation needed)
                            cout << "Enter source and destination accounts: " << endl;
                            // Code for internal transfer
                            break;
                        case 7:
                            userLoggedIn = false;
                            cout << "Logged out successfully!" << endl;
                            break;
                        default:
                            cout << "Invalid option! Please try again." << endl;
                    }
                }
                break;
            }
            case 3:
                cout << "Thank you for using PNB Bank System! Goodbye." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please enter a valid option." << endl;
        }
    }

    return 0;
}

