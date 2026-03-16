#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
using namespace std;

class Account {
    private:
        string name;
        int id;
        double balance;

    public:
        Account();
        Account(int id, const string& name, double balance);

        int getID() const;
        string getName() const;
        double getBalance() const;

        void deposit(double amount);
        bool withdraw(double amount);
        void display() const;
};

#endif