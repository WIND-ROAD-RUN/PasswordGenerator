#ifndef ACCOUNTTABLEXML_H_
#define ACCOUNTTABLEXML_H_

#include"AccountTableModuleAbstract.h"
#include<string>
#include"pugixml.hpp"

class AccountTableXML
    :public AccountTableModuleAbstract {
private:
    pugi::xml_document m_doc;
    ATMAstring m_filePath{};
    ATMAstring m_UID{};
public:
    AccountTableXML() {}
    AccountTableXML(const std::string & filePath, const std::string& UID)
        :m_filePath(filePath), m_UID(UID){}
    ~AccountTableXML() {}
public:
    void setFilePath(const std::string& filePath) { m_filePath = filePath; }
    void setUID(const std::string& UID) { m_UID = UID; }
public:
    void setNewFile(const std::string & filePath,const std::string & UID);
public:
    /*新增节点*/
    ErrorAccountTableModule NewAccount(const ATMAstring& platform, const ATMAstring& account) override;

    ErrorAccountTableModule NewAccountTable(const ATMAstring& fileName) override;

    ErrorAccountTableModule NewPlatform(const ATMAstring& platform) override;

    /*初始化模块*/
    ErrorAccountTableModule ini_module() override;

    /*设置数据信息*/
    ErrorAccountTableModule setPassword(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& password) override;

    ErrorAccountTableModule setPhoneNumber(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& phoneNumber) override;

    ErrorAccountTableModule setUser(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& user) override;

    ErrorAccountTableModule setPasswordLength(const ATMAstring& platform, const ATMAstring& account, ATMAint minimum, ATMAint maximum) override;

    ErrorAccountTableModule sethaveSpecialSymbols(const ATMAstring& platform, const ATMAstring& account, ATMAbool haveSpecialSymbols) override;

    ErrorAccountTableModule sethaveUppercaseLowercase(const ATMAstring& platform, const ATMAstring& account, ATMAbool haveUppercaseLowercase) override;

    ErrorAccountTableModule setEncrpyIsIrreversible(const ATMAstring& platform, const ATMAstring& account, ATMAbool EncrpyIsIrreversible) override;

    ErrorAccountTableModule setAccount(const ATMAstring& platform, const ATMAstring& orginalAccount, const ATMAstring& newAccount) override;
    
    /*保存数据信息*/
    ErrorAccountTableModule save() override;

    /*删除数据信息*/
    ErrorAccountTableModule deletePlatform(const ATMAstring& platform) override;

    ErrorAccountTableModule deleteAccount(const ATMAstring& platform, const ATMAstring& account) override;
public :
    /*提炼函数*/
    ErrorAccountTableModule findPlatformNode(const ATMAstring & platform,pugi::xml_node & platformNode);
    
    ErrorAccountTableModule findAccountNode(const ATMAstring & platform,const ATMAstring & account, pugi::xml_node& accountNode);
    
    ErrorAccountTableModule findPlatformNode(const ATMAstring& platform);
    
    ErrorAccountTableModule findAccountNode(const ATMAstring& platform, const ATMAstring& account);
public:
    /*返回数据信息*/
    ATMAstring Password(const ATMAstring& platform, const ATMAstring& account) override;
    
    ATMAstring PhoneNumber(const ATMAstring& platform, const ATMAstring& account) override;
    
    ATMAstring User(const ATMAstring& platform, const ATMAstring& account) override;
    
    ATMApair PasswordLength(const ATMAstring& platform, const ATMAstring& account) override;
    
    ATMAbool haveSpecialSymbols(const ATMAstring& platform, const ATMAstring& account) override;
    
    ATMAbool haveUppercaseLowercase(const ATMAstring& platform, const ATMAstring& account) override;
    
    ATMAbool EncrpyIsIrreversible(const ATMAstring& platform, const ATMAstring& account) override;

    AccountInfo Account(const ATMAstring& platform, const ATMAstring& account) override;

    ErrorAccountTableModule NewAccount(const ATMAstring& platform, const AccountInfo& account) override;
    
    ErrorAccountTableModule setAccount(const ATMAstring& platform, const AccountInfo& account) override;

    ATMAStringList getPlatformList() override;

    ATMAAccountList getAccountList(const ATMAstring& platform) override;

};


#endif // !ACCOUNTTABLEXML_H_

