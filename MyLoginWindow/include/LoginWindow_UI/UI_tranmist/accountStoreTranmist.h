#ifndef ACCOUNTSTORETRANMSIT_H_
#define ACCOUNTSTORWTRANMSIT_H_

#include<String>

class AccountStoreAbstract;

enum AccountStoreTranmsitResult {
    EmptyAccount = 0, ExistingAccount = 1,
    ErrorPassword = 2, RightPassword = 4,
    SavedAccountFailed = 5, SavedAccountSucceed = 6
};

class AccountStoreTranmsit {
private:
    AccountStoreAbstract* m_accountStoreAbstract;

public:
    AccountStoreTranmsit();

    ~AccountStoreTranmsit();

    AccountStoreTranmsitResult searchAccount(const std::string& account);

    AccountStoreTranmsitResult checkPassword(const std::string& account, const std::string& password);

    AccountStoreTranmsitResult saveAccountInfo(const std::string& account, const std::string& password);

};


#endif // !saveAccount

