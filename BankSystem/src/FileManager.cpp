#include "FileManager.h"

#include <fstream>
#include <iostream>

void FileManager::saveAccounts(const vector<Account>& accounts) {
    ofstream outFile("accounts.txt");
    if(!outFile) {
        cout << "Error opening file for writing!" << endl;
    }
    for(const auto& acc : accounts) {
        outFile << acc.getID() << " " 
             << acc.getName() << " "
             << acc.getBalance() << endl;
    }
}

void FileManager::loadAccounts(vector<Account>& accounts) {
    ifstream inFile("accounts.txt");
    if(!inFile) {
        cout << "Error opening file for reading!" << endl;
        return;
    }
    int id;
    string name;
    double balance;

    while(inFile >> id >> name >> balance) {
        accounts.emplace_back(id, name, balance);
    }
}