#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include "Account.h"
#include <iostream>
#include <vector>
using namespace std;

class BankSystem {
    private:
        vector<Account> accounts;

        Account* findAccount(int id); // Helper function to find an account by ID

    public:
        BankSystem();

        void createAccount(); //创建账户函数应该接受账户ID、姓名和初始余额作为参数
        void deposit(); //存款函数应该接受账户ID和存款金额作为参数
        void withdraw(); //取款函数应该接受账户ID和取款金额作为参数
        void showAccounts(); //展示所有账户信息

        void load(); //从文件加载数据
        void save(); //保存数据到文件
};

#endif