#ifndef ACCOUNTTABLEXML_H_
#define ACCOUNTTABLEXML_H_

#include"AccountTableModuleAbstract.h"
#include<string>
#include"pugixml.hpp"

class AccountTableXML
    :public AccountTableModuleAbstract {
private:
    pugi::xml_document m_doc;
    std::string m_filePath{};
    std::string m_UID{};
public:
    AccountTableXML() {}
    AccountTableXML(const std::string & filePath, const std::string& UID)
        :m_filePath(filePath), m_UID(UID){}
    ~AccountTableXML() {}
protected:
    // Í¨¹ý AccountTableModuleAbstract ¼Ì³Ð
    ErrorAccountTableModule NewAccount(const ATMAstring& platform, const ATMAstring& account) override;

    ErrorAccountTableModule NewPassword() override;

    ErrorAccountTableModule NewPhoneNumber() override;

    ErrorAccountTableModule NewUser() override;

    ErrorAccountTableModule NewEncrpyProperty() override;

    ErrorAccountTableModule NewPasswordLength() override;

    ErrorAccountTableModule NewhaveSpecialSymbols() override;

    ErrorAccountTableModule NewhaveUppercaseLowercase() override;

    ErrorAccountTableModule NewEncrpyIsIrreversible() override;
public:
    ErrorAccountTableModule setAccount(const ATMAstring& platform, const ATMAstring& account) override;

    ErrorAccountTableModule setPassword(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& password) override;

    ErrorAccountTableModule setPhoneNumber(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& phoneNumber) override;

    ErrorAccountTableModule setUser(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& user) override;

    ErrorAccountTableModule setEncrpyProperty(const ATMAstring& platform, const ATMAstring& account) override;

    ErrorAccountTableModule setPasswordLength(const ATMAstring& platform, const ATMAstring& account, ATMAint minimum, ATMAint Maximum) override;

    ErrorAccountTableModule sethaveSpecialSymbols(const ATMAstring& platform, const ATMAstring& account, ATMbool haveSpecialSymbols) override;

    ErrorAccountTableModule sethaveUppercaseLowercase(const ATMAstring& platform, const ATMAstring& account, ATMbool haveUppercaseLowercase) override;

    ErrorAccountTableModule setEncrpyIsIrreversible(const ATMAstring& platform, const ATMAstring& account, ATMbool EncrpyIsIrreversible) override;

    ErrorAccountTableModule NewAccountTable(const ATMAstring& fileName) override;

    ErrorAccountTableModule NewPlatform(const ATMAstring& fileName) override;

    ErrorAccountTableModule ini_module() override;

};


#endif // !ACCOUNTTABLEXML_H_

