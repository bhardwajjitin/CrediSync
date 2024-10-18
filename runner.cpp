#include "Bank.hpp"
using namespace std;

int main()
{
    Bank &PNB = Bank::getInstance(); // Singleton Bank instance
    cout << "==== Welcome to the PNB Bank System ====" << endl;

    while (true)
    {
        cout << "\nMain Menu:" << endl;
        cout << "1. Create New User" << endl;
        cout << "2. Login to Existing User" << endl;
        cout << "3. Exit the System" << endl;
        cout << "Please enter your choice: ";
        int mainOption;
        cin >> mainOption;

        switch (mainOption)
        {
        case 1:
        {
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
            cout << "Enter the Type of Account \n 1.Savings \n 2.Current" << endl;
            cin >> type;
            if (type == 1)
            {
                PNB.adduser(name, accNo, balance, "Savings", 50000, 5);
            }
            else if (type == 2)
            {
                PNB.adduser(name, accNo, balance, "Current", -1, -1);
            }
            else
            {
                cout << "Please Enter the Valid Choice" << endl;
                continue;
            }
            break;
        }
        case 2:
        {
            // User login
            string accNo;
            cout << "Enter Account Number to Login: ";
            cin >> accNo;
            User *currentUser = PNB.getUser(accNo);

            if (currentUser == nullptr)
            {
                cout << "Invalid Account Number! Try again." << endl;
                break;
            }

            bool userLoggedIn = true;
            cout << "\nWelcome, " << currentUser->getName() << "!" << endl;
            while (userLoggedIn)
            {
                cout << "1. Create New Card" << endl;
                cout << "2. Use Existing Card" << endl;
                cout << "3. Balance Enquiry" << endl;
                cout << "4. Deposit Money" << endl;
                cout << "5. Transfer Funds to Another User" << endl;
                cout << "6. Transfer Funds Between Own Accounts" << endl;
                cout << "7. Check Your limits" << endl;
                cout << "8. Delete the User" << endl;
                cout << "9. Logout" << endl;
                cout << "Enter your choice: ";
                int userOption;
                cin >> userOption;

                switch (userOption)
                {
                case 1:
                {
                    // Create a new card
                    int cardType;
                    cout << "Select Card Type: 1. Debit  2. Credit: ";
                    cin >> cardType;

                    if (cardType >= 1 && cardType <= 2)
                    {
                        string cardNo;
                        int pin;
                        cout << "Enter 5-digit Card Number: ";
                        cin >> cardNo;
                        cout << "Set a 4-digit PIN for the Card: ";
                        cin >> pin;

                        string cardTypeStr = (cardType == 1) ? "Debit" : "Credit";
                        if (PNB.alreadyexists(cardNo))
                        {
                            currentUser->addCards(cardNo, cardTypeStr, pin, false);
                            cout << cardTypeStr << " Card created successfully!" << endl;
                        }
                        else
                        {
                            cout << "Card Number should be unique" << endl;
                        }
                    }
                    else
                    {
                        cout << "Invalid card type!" << endl;
                    }
                    break;
                }
                case 2:
                {
                    // Use an existing card
                    currentUser->printallCards();
                    string cardNo;
                    cout << "Enter the Card Number: ";
                    cin >> cardNo;

                    Card *selectedCard = currentUser->getcard(cardNo);

                    if (selectedCard == nullptr)
                    {
                        cout << "Invalid Card Number!" << endl;
                    }
                    else if (!selectedCard->iscardblock())
                    {
                        string unblockOption;
                        cout << "This card is blocked. Do you want to unblock it? (y/n): ";
                        cin >> unblockOption;

                        if (unblockOption == "y" || unblockOption == "Y")
                        {
                            selectedCard->unblockCard();
                            cout<<"Card is Unblocked"<<endl;
                        }
                        else
                        {
                            cout << "Card remains blocked. Cannot proceed!" << endl;
                            break;
                        }
                    }
                    else
                    {
                        int cardPin;
                        int attempts = 0;
                        int maxAttempts = 3;

                        while (attempts < maxAttempts)
                        {
                            cout << "Enter Card PIN for verification: ";
                            cin >> cardPin;

                            if (selectedCard->getpin() == cardPin)
                            {
                                bool cardSessionActive = true;
                                while (cardSessionActive)
                                {
                                    int cardOption;
                                    cout << "\n1. Deposit\n2. Withdraw\n3. Check Balance\n4. Delete Card \n"
                                         << "5. Reset PIN\n6. Show Transaction History\n"
                                         << "7. Block Card\n8. End Session" << endl;
                                    cout << "Enter your choice: ";
                                    cin >> cardOption;

                                    string type = "";
                                    long long amount;
                                    switch (cardOption)
                                    {
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
                                        PNB.deletecard(currentUser, cardNo);
                                        cout << "Card deleted successfully." << endl;
                                        cardSessionActive = false; // End session after deleting the card
                                        continue;
                                    case 5: // Reset PIN option
                                    {
                                        int oldPin, newPin;
                                        cout << "Enter your old PIN: ";
                                        cin >> oldPin;
                                        cout << "Enter your new PIN: ";
                                        cin >> newPin;
                                        if (selectedCard->resetPin(oldPin, newPin))
                                        {
                                            cout << "PIN reset successful." << endl;
                                        }
                                        else
                                        {
                                            cout << "Failed to reset PIN." << endl;
                                        }
                                        continue;
                                    }
                                    case 6:
                                    
                                        selectedCard->printTransactionHistory();
                                        continue;
                                    case 7: // Block card and exit
                                        selectedCard->blockcard();
                                        cout << "Card has been successfully blocked." << endl;
                                        cardSessionActive = false;
                                        continue;
                                    case 8: // End session
                                        cardSessionActive = false;
                                        cout << "Ending Card Session." << endl;
                                        continue;
                                    default:
                                        cout << "Invalid operation." << endl;
                                        continue;
                                    }

                                    if (!type.empty())
                                    {
                                        if (selectedCard->transaction(type, amount))
                                        {
                                            selectedCard->addTransaction(type,amount,currentUser->getBalance(),"Success",selectedCard->getcardtype());
                                            // cout << "Transaction successful! New Balance: " << currentUser->getBalance() << endl;
                                        }
                                        else
                                        {
                                            selectedCard->addTransaction(type,amount,currentUser->getBalance(),"Failed",selectedCard->getcardtype());
                                            cout << "Transaction failed!" << endl;
                                        }
                                    }
                                }
                                break;
                            }
                            else
                            {
                                attempts++;
                                cout << "Incorrect PIN! You have " << (maxAttempts - attempts) << " attempts left." << endl;
                            }
                        }
                        if (attempts >= maxAttempts)
                        {
                            cout << "Too many incorrect attempts. Session terminated." << endl;
                        }
                    }
                    break;
                }
                case 3:
                    // Balance enquiry
                    cout << "Your current balance for your Account is <<: " << currentUser->getBalance() << endl;
                    break;
                case 4:
                {
                    // Deposit money
                    long long amount;
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    currentUser->deposit(amount);
                    cout << "Deposit successful! New Balance: " << currentUser->getBalance() << endl;
                    break;
                }
                case 5:
                {
                    cout << "Enter recipient account number " << endl;
                    string receive;
                    long long amount;
                    cin >> receive;
                    if (receive != accNo)
                    {
                        User *receiver = PNB.getUser(receive);
                        if(receiver!=nullptr){
                        cout << "Enter the Amount you want to Transfer" << endl;
                        cin >> amount;
                        currentUser->transfer(receiver, amount);
                        }
                        else{
                            cout<<"User Does Not Exist with this Account Number"<<endl;
                        }
                    }
                    else
                    {
                        continue;
                    }
                    break;
                }
                case 6:
                {
                    cout << "Enter your destinated account number" << endl;
                    string dest;
                    long long myamount;
                    cin >> dest;
                    User *destinated = PNB.getUser(dest);
                    if(destinated!=nullptr){
                    cout << "Enter the Amount you want to transfer to your own accounts" << endl;
                    cin >> myamount;
                    currentUser->transfer(destinated, myamount);
                    }
                    else{
                        cout<<"Please Enter the Valid Account Number"<<endl;
                    }
                    break;
                }
                case 7:
                    currentUser->checklimits();
                    break;
                case 8:
                    PNB.deleteuser(accNo);
                    userLoggedIn = false;
                    cout << "User Successfully Deleted" << endl;
                    break;
                case 9:
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
