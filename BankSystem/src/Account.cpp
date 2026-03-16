#include "Account.h"

Account::Account() : id(0), name(""), balance(0.0) {}

Account::Account(int id, const string& name, double balance) {
    this->id = id;
    this->name = name;
    this->balance = balance;
}

int Account::getID() const {
    return id;
}

string Account::getName() const {
    return name;
}

double Account::getBalance() const {
    return balance;
}

void Account::deposit(double amount) {
    balance += amount;
}

bool Account::withdraw(double amount) {
    if(balance < amount) {
        return false;
    }

    balance -= amount;
    return true;
}



void Account::display() const {
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Balance: " << balance << endl;
}