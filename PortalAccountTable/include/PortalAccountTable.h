#ifndef PORTALACCOUNTTABLE_H_
#define PORTALACCOUNTTABLE_H_

#include"NameDefineForPAT.h"

class AccountTableXML;
class PasswordEncrpySimplyAch;

class PortalAccountTable {
private:
    PATmap m_map;
private:
    AccountTableXML* m_accountTableXML;
    PasswordEncrpySimplyAch* m_EncrpyCom;
private:
    ATMAstring m_filePath{};
    ATMAstring m_UID{};
public:
    PortalAccountTable(const ATMAstring& filePath,const ATMAstring& UID);
    PortalAccountTable();
    ~PortalAccountTable();
public:
    void setFilePath(const ATMAstring& filePath) { m_filePath = filePath; }
    void setUID(const ATMAstring& UID) { m_UID = UID; }
public:
    ErrorPortalAccountTable ini_portal();

};



#endif // !PORTALACCOUNTTABLE_H_

