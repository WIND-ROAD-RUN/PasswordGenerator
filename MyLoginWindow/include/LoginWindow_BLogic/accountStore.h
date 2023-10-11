#ifndef ACCOUNTSTORE_H_
#define ACCOUNTSTORE_H_

#include<String>
#include<vector>
#include<sstream>

class AccountStore {
private:
    struct Account {
        std::string account;
        std::string password;
    };
    std::string m_fileName{ "G:\\project\\code_place\\vs_code_place\\game_project\\password.txt" };
    std::vector<Account> m_accountTable;
public:
    void ini_file();
    AccountStore() { ini_file(); }
    ~AccountStore() {}
    void clear_registTable();
    bool search_account(const std::string& account);
    void save_account(const std::string & account,const std::string& password);
    bool save_account_exceptExist(const std::string& account, const std::string& password);
    bool check_password(const std::string& account, const std::string& password);
};


#endif // !ACCOUNTSTORE_H_
