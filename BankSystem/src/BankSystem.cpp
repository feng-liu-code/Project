#include "BankSystem.h"
#include "FileManager.h"
#include <cctype>
#include <limits>

BankSystem::BankSystem() {}

Account* BankSystem::findAccount(int id) {
    for(auto& acc : accounts) {
        if(acc.getID() == id) {
            return &acc;
        }
    }
    return nullptr;
}

void BankSystem::createAccount() {
    int id;
    string name;
    double balance;

    cout << "Enter ID: ";
    cin >> id;
    if(findAccount(id)) {
        cout << "account already exists!" << endl;
        return;
    }

    cout << "Enter Name:";
    cin >> name;

    cout << "Enter initial balance: ";
    cin >> balance;

    accounts.emplace_back(id, name, balance);
    cout << "Account created" << endl;
}

void BankSystem::deposit() {
    int id;
    double amount;

    cout << "Enter account ID: ";
    cin >> id;
    Account* acc = findAccount(id);
    if(!acc) {
        cout << "account not found!" << endl;
        return;
    }
    cout << "Enter deposit amount: ";
    cin >> amount;
    acc->deposit(amount);
    cout << "Deposit successful " << endl;
}

void BankSystem::withdraw() {
    int id;
    double amount;

    cout << "Enter account ID: ";
    cin >> id;
    Account* acc = findAccount(id);
    if(!acc) {
        cout << "account not found!" << endl;
        return;
    }
    cout << "Enter amount: " ;
    cin >> amount;

    if(acc->withdraw(amount)) {
        cout << "Withdraw success" << endl;
    }else {
        cout << "Insufficient balance!" << endl;
    }
}

void BankSystem::showAccounts() {
    for(const auto& acc : accounts) {
        acc.display();
    }
}

void BankSystem::load() {
    FileManager::loadAccounts(accounts);
}

void BankSystem::save() {
    FileManager::saveAccounts(accounts);
}