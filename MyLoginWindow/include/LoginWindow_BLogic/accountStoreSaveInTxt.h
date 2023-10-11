#ifndef ACCOUNTSTORESAVEINTXT_H_
#define ACCOUNTSTORESAVEINTXT_H_

#include"accountStoreAbstract.h"
#include<vector>

/*实现为单例类*/
class AccountStoreSaveInTxt:public AccountStoreAbstract {
private:
    static AccountStoreSaveInTxt* my_instance;
    AccountStoreSaveInTxt() {}
public:
    static AccountStoreSaveInTxt* getInstance() {
        if (!my_instance) {
            my_instance = new AccountStoreSaveInTxt();
            my_instance->ini_accountTable();
        }
        return my_instance;
    }
    ~AccountStoreSaveInTxt() { delete my_instance; }
private:
    std::vector<Account> m_accountTable;
    std::string m_fileName{ R"(G:\project\code_place\vs_code_place\MyPasswordGenerator\PasswordGeneratorProject\MyLoginWindow\bin\x64\Debug\password.txt)" };
public:
    // 通过 AccountStoreAbstract 继承
    void ini_accountTable() override;
    void clear_registTable() override;
    bool search_account(const std::string& account) override;
    void save_account(const std::string& account, const std::string& password) override;
    bool save_account_exceptExist(const std::string& account, const std::string& password) override;
    bool check_password(const std::string& account, const std::string& password) override;
};



#endif // !ACCOUNTSTORESAVEINTXT_H_


