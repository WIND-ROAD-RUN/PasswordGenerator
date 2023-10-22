#ifndef PORTALACCOUNTTABLE_H_
#define PORTALACCOUNTTABLE_H_

#include"NameDefineForPAT.h"

class AccountTableXML;
class PasswordEncrpySimplyAch;

/*实现为单例模式*/

class PortalAccountTable {
private:
    PATmap m_map;
private:
    AccountTableXML* m_accountTableXML;
    PasswordEncrpySimplyAch* m_EncrpyCom;
private:
    ATMAstring m_filePath{};
    ATMAstring m_UID{};
private:
    static PortalAccountTable* m_instance;
    PortalAccountTable(const ATMAstring& filePath, const ATMAstring& UID);
    PortalAccountTable();
public:
    static PortalAccountTable*
        getInstance() {
        if (!m_instance) {
            m_instance = new PortalAccountTable();
        }
        return m_instance;
    }
    static PortalAccountTable*
        getInstance(const ATMAstring& filePath, const ATMAstring& UID) {
        if (!m_instance) {
            m_instance = new PortalAccountTable(filePath, UID);
        }
        return m_instance;
    }
    ~PortalAccountTable();
public:
    void setFilePath(const ATMAstring& filePath) { m_filePath = filePath; }
    void setUID(const ATMAstring& UID) { m_UID = UID; }
public:
    ErrorPortalAccountTable ini_portal();
public:
    AccountInfo search_account(const  ATMAstring& platform, const  ATMAstring& accountName);
    void set_account(const AccountInfo & accountInfo);
    ErrorAccountTableModule newAccount(const  ATMAstring& platform,const AccountInfo& accountInfo);
    ErrorAccountTableModule deletePlatform(const  ATMAstring& platform);
    ErrorAccountTableModule deleteAccount(const  ATMAstring& platform, const ATMAstring& accountName);
};



#endif // !PORTALACCOUNTTABLE_H_

