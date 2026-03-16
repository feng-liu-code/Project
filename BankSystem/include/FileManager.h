#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Account.h"
#include <vector>

class FileManager {
    public:
        static void saveAccounts(const vector<Account>& accounts);
        static void loadAccounts(vector<Account>& accounts);
};

#endif