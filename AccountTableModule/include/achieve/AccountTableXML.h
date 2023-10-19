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
    // 通过 AccountTableModuleAbstract 继承
    ErrorAccountTableModule NewAccount(const ATMAstring& platform, const ATMAstring& account) override;

    ErrorAccountTableModule NewAccountTable(const ATMAstring& fileName) override;

    ErrorAccountTableModule NewPlatform(const ATMAstring& fileName) override;

    ErrorAccountTableModule ini_module() override;


    // 通过 AccountTableModuleAbstract 继承

    ErrorAccountTableModule setPassword(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& password) override;

    ErrorAccountTableModule setPhoneNumber(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& phoneNumber) override;

    ErrorAccountTableModule setUser(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& user) override;

    ErrorAccountTableModule setEncrpyProperty(const ATMAstring& platform, const ATMAstring& account) override;

    ErrorAccountTableModule setPasswordLength(const ATMAstring& platform, const ATMAstring& account, ATMAint minimum, ATMAint Maximum) override;

    ErrorAccountTableModule sethaveSpecialSymbols(const ATMAstring& platform, const ATMAstring& account, ATMbool haveSpecialSymbols) override;

    ErrorAccountTableModule sethaveUppercaseLowercase(const ATMAstring& platform, const ATMAstring& account, ATMbool haveUppercaseLowercase) override;

    ErrorAccountTableModule setEncrpyIsIrreversible(const ATMAstring& platform, const ATMAstring& account, ATMbool EncrpyIsIrreversible) override;


    // 通过 AccountTableModuleAbstract 继承
    ErrorAccountTableModule save() override;


    // 通过 AccountTableModuleAbstract 继承
    ErrorAccountTableModule setAccount(const ATMAstring& platform, const ATMAstring& orginalAccount, const ATMAstring& newAccount) override;


    // 通过 AccountTableModuleAbstract 继承
    ErrorAccountTableModule deletePlatform(const ATMAstring& platform) override;

    ErrorAccountTableModule deletePlatform(const ATMAstring& platform, const ATMAstring& account) override;
public :
    /*以下用于实现重复操作*/
    ErrorAccountTableModule findPlatformNode(const ATMAstring & platform,pugi::xml_node & platformNode);
    ErrorAccountTableModule findAccountNode(const ATMAstring & platform,const ATMAstring & account, pugi::xml_node& accountNode);
    ErrorAccountTableModule findPlatformNode(const ATMAstring& platform);
    ErrorAccountTableModule findAccountNode(const ATMAstring& platform, const ATMAstring& account);
};


#endif // !ACCOUNTTABLEXML_H_

