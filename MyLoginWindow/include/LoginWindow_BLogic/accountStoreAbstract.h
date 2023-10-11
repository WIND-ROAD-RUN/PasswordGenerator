#ifndef ACCOUNTSTOREABSTRACT_H_
#define ACCOUNTSTOREABSTRACT_H_

#include<string>

class AccountStoreAbstract {
protected:
    struct Account {
        std::string account;
        std::string password;
    };
public:
    AccountStoreAbstract() {}
    ~AccountStoreAbstract() {}
public:
    virtual void ini_accountTable() = 0;
    virtual void clear_registTable()=0;
    virtual bool search_account(const std::string& account) = 0;
    virtual void save_account(const std::string& account, const std::string& password)=0;
    virtual bool save_account_exceptExist(const std::string& account, const std::string& password)=0;
    virtual bool check_password(const std::string& account, const std::string& password)=0;
};




#endif // !ACCOUNTSTOREABSTRACT_H_
