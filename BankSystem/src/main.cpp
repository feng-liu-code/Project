#include "BankSystem.h"

int main() {
    BankSystem bank;
    bank.load();

    int choice;
    while(true) {
        cout << "1. Create Account" << endl;
        cout << "2. Deposit" <<endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Show Accounts" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            bank.createAccount();
            break;
        case 2:
            bank.deposit();
            break;
        case 3:
            bank.withdraw();
            break;
        case 4:
            bank.showAccounts();
            break;
        case 0:
            bank.save();
            return 0;
        
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }
    return 0;
}