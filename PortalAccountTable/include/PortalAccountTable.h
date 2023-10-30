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
    /*当且门户所管理的数据文件信息*/
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
    /*加载以及保存数据*/
    ErrorPortalAccountTable ini_portal();
    ErrorAccountTableModule save_change();
public:
    /*账户信息的操作以及信息读取接口*/
    AccountInfo search_account(const  ATMAstring& platform, const  ATMAstring& accountName);
    ErrorAccountTableModule set_account(const ATMAstring& platform, const AccountInfo & accountInfo);
    ErrorAccountTableModule newAccount(const  ATMAstring& platform,const AccountInfo& accountInfo);
    ErrorAccountTableModule newPlatform(const  ATMAstring& platform);
    ErrorAccountTableModule deletePlatform(const  ATMAstring& platform);
    ErrorAccountTableModule deleteAccount(const  ATMAstring& platform, const ATMAstring& accountName);
    ATMAStringList  PlatformList();
    ATMAAccountList AccountList(const  ATMAstring& platform);
    ATMAint AccountNumber();
    ATMAstring encrpyForUser(const AccountInfo & account);
public:
    /*当使用空的数据文件（新的数据文件）的时候使用这个函数初始化这个文件保证数据文件的格式正确以供使用*/
    void setNewFile(const std::string & filePath,const std::string & UID);
};



#endif // !PORTALACCOUNTTABLE_H_

