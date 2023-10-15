#ifndef ACCOUNTSTORESAVEINXML_H_
#define ACCOUNTSTORESAVEINXML_H_

#include"accountStoreAbstract.h"
#include<vector>
#include<string>
#include<pugixml.hpp>

class AccountStoreSaveInXML
    :public AccountStoreAbstract {
private:
    std::vector<Account> m_accountTable;
private:
    std::string m_accountFilePath{};
    pugi::xml_document m_doc;
public:
    AccountStoreSaveInXML() {}
    AccountStoreSaveInXML(const std::string & filePath):m_accountFilePath(filePath) {}
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

