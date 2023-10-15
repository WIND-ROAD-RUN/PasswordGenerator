#ifndef ACCOUNTSTORESAVEINXML_H_
#define ACCOUNTSTORESAVEINXML_H_

#include"accountStoreAbstract.h"
#include<vector>
#include<string>
#include<pugixml.hpp>

/*实现为单例类*/
class AccountStoreSaveInXML
    :public AccountStoreAbstract {
private:
    std::vector<Account> m_accountTable;
private:
    std::string m_accountFilePath{};
    pugi::xml_document m_doc;
private:
    static AccountStoreSaveInXML* my_instance;
    AccountStoreSaveInXML() {}
    AccountStoreSaveInXML(const std::string& filePath) :m_accountFilePath(filePath) {}
public:
    static AccountStoreSaveInXML* getInstance() {
        if (!my_instance) {
            my_instance = new AccountStoreSaveInXML();
        }
        return my_instance;
    }
    static AccountStoreSaveInXML* getInstance(const std::string& filePath) {
        if (!my_instance) {
            my_instance = new AccountStoreSaveInXML(filePath);
        }
        return my_instance;
    }

    ~AccountStoreSaveInXML() {}
public:
    void setFilePath(const std::string& filePath) { m_accountFilePath = filePath; }
public:
    // 通过 AccountStoreAbstract 继承
    void ini_accountTable() override;

    void clear_registTable() override;

    bool search_account(const std::string& account) override;

    void save_account(const std::string& account, const std::string& password) override;

    bool save_account_exceptExist(const std::string& account, const std::string& password) override;

    bool check_password(const std::string& account, const std::string& password) override;

};




#endif // !ACCOUNTSTORESAVEINXML_H_

