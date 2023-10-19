#include "AccountTableXML.h"

#include <fstream>

ErrorAccountTableModule AccountTableXML::NewAccountTable(const ATMAstring& fileName)
{
    std::ofstream file(fileName);
    if (file.is_open()) {
        file.close();
        auto NewAccountTableNode=m_doc.append_child("AccountTable");
        if (!NewAccountTableNode) 
        { 
            return ErrorAccountTableModule::NewAccountTable_ERROR; 
        }
        if (!NewAccountTableNode.append_attribute("UID").set_value(m_UID.c_str())) 
        { 
            return ErrorAccountTableModule::NewAccountTable_ERROR; 
        }
        if (!m_doc.save_file(fileName.c_str())) {
            return ErrorAccountTableModule::NewAccountTable_ERROR; 
        }
        return ErrorAccountTableModule::No_ERROR;
    }
    else {
        return ErrorAccountTableModule::NewAccountTable_ERROR;
    }
}

ErrorAccountTableModule AccountTableXML::NewPlatform(const ATMAstring& platform)
{
    auto AccountTableNode = m_doc.child("AccountTable");
    if (!AccountTableNode) { return ErrorAccountTableModule::NewPlatform_ERROR; }
    if (AccountTableNode.find_child_by_attribute("NAME", platform.c_str())) { return ErrorAccountTableModule::PlatformAlreadyExist; }

    auto PlatformNode=AccountTableNode.append_child("Platform");
    if (!PlatformNode) { return ErrorAccountTableModule::NewPlatform_ERROR; }
    if (!PlatformNode.append_attribute("NAME").set_value(platform.c_str())) { return ErrorAccountTableModule::NewPlatform_ERROR; }
    return ErrorAccountTableModule::No_ERROR;
}

ErrorAccountTableModule AccountTableXML::ini_module()
{
    if (!m_doc.load_file(m_filePath.c_str())) { return ErrorAccountTableModule::Initialization_ERROR; }
    else { return ErrorAccountTableModule::No_ERROR; }
}



ErrorAccountTableModule AccountTableXML::setPassword(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& password)
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::setPhoneNumber(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& phoneNumber)
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::setUser(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& user)
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::setEncrpyProperty(const ATMAstring& platform, const ATMAstring& account)
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::setPasswordLength(const ATMAstring& platform, const ATMAstring& account, ATMAint minimum, ATMAint Maximum)
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::sethaveSpecialSymbols(const ATMAstring& platform, const ATMAstring& account, ATMbool haveSpecialSymbols)
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::sethaveUppercaseLowercase(const ATMAstring& platform, const ATMAstring& account, ATMbool haveUppercaseLowercase)
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::setEncrpyIsIrreversible(const ATMAstring& platform, const ATMAstring& account, ATMbool EncrpyIsIrreversible)
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::save()
{
    if (m_doc.save_file(m_filePath.c_str())) {
        return ErrorAccountTableModule::No_ERROR;
    }
    else {
        return ErrorAccountTableModule::SaveData_ERROR;
    }
}

ErrorAccountTableModule AccountTableXML::setAccount(const ATMAstring& platform, const ATMAstring& orginalAccount, const ATMAstring& newAccount)
{   
    if (orginalAccount== newAccount) {return ErrorAccountTableModule::No_ERROR;}
    pugi::xml_node AccountNode;
    auto findAccountSrc = findAccountNode(platform,orginalAccount,AccountNode);
    if (findAccountSrc!=ErrorAccountTableModule::AccountAlreadyExist) {
        return findAccountSrc;
    }

    auto findAccountTarge = findAccountNode(platform,newAccount);

    if (findAccountTarge!=ErrorAccountTableModule::NoAccountNode) {
        return findAccountTarge; 
    }

    if (!AccountNode.attribute("USERNAME").set_value(newAccount.c_str())) {
        return ErrorAccountTableModule::setAccount_ERROR;
    }
    
    return ErrorAccountTableModule::No_ERROR;
}

ErrorAccountTableModule AccountTableXML::deletePlatform(const ATMAstring& platform)
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::deletePlatform(const ATMAstring& platform, const ATMAstring& account)
{
    return ErrorAccountTableModule();
}


ErrorAccountTableModule AccountTableXML::findPlatformNode(const ATMAstring& platform, pugi::xml_node& platformNode)
{
    auto AccountTableNode = m_doc.child("AccountTable");
    if (!AccountTableNode) { return ErrorAccountTableModule::NoAccounTable; }
    auto PlatformNode = AccountTableNode.find_child_by_attribute("NAME", platform.c_str());
    if (PlatformNode) {
        platformNode = PlatformNode;
        return ErrorAccountTableModule::PlatformAlreadyExist;
    }
    return ErrorAccountTableModule::NoPlatformNode;
    
}

ErrorAccountTableModule AccountTableXML::findAccountNode(const ATMAstring& platform, const ATMAstring& account, pugi::xml_node& accountNode)
{
    pugi::xml_node platformNode;
    auto findPlatform = findPlatformNode(platform, platformNode);
    if (findPlatform != ErrorAccountTableModule::PlatformAlreadyExist) {
        return findPlatform;
    }
  
    auto findAccount= platformNode.find_child_by_attribute("USERNAME",account.c_str());
    if (findAccount) { 
        accountNode = findAccount;
        return ErrorAccountTableModule::AccountAlreadyExist; 
    }
    return ErrorAccountTableModule::NoAccountNode;
}

ErrorAccountTableModule AccountTableXML::findPlatformNode(const ATMAstring& platform)
{
    auto AccountTableNode = m_doc.child("AccountTable");
    if (!AccountTableNode) { return ErrorAccountTableModule::NoAccounTable; }
    auto PlatformNode = AccountTableNode.find_child_by_attribute("NAME", platform.c_str());
    if (PlatformNode) {
        return ErrorAccountTableModule::PlatformAlreadyExist;
    }
    return ErrorAccountTableModule::NoPlatformNode;
}

ErrorAccountTableModule AccountTableXML::findAccountNode(const ATMAstring& platform, const ATMAstring& account)
{
    pugi::xml_node platformNode;
    auto findPlatform = findPlatformNode(platform, platformNode);
    if (findPlatform != ErrorAccountTableModule::PlatformAlreadyExist) {
        return findPlatform;
    }

    auto findAccount = platformNode.find_child_by_attribute("USERNAME", account.c_str());
    if (findAccount) {
        return ErrorAccountTableModule::AccountAlreadyExist;
    }
    return ErrorAccountTableModule::NoAccountNode;
}



ErrorAccountTableModule AccountTableXML::NewAccount(const ATMAstring& platform, const ATMAstring& account)
{
    /*查询是否含有目标平台的节点若没有则返回错误代码*/
    pugi::xml_node PlatformNode;
    auto findPlatform = findPlatformNode(platform, PlatformNode);
    if (findPlatform != ErrorAccountTableModule::PlatformAlreadyExist) { return findPlatform; }

    /*查询是否已经含有同名账户节点，有的话返回错误代码，没有则新建一个*/
    auto findAccount=findAccountNode(platform,account);
    if (findAccount==ErrorAccountTableModule::AccountAlreadyExist) {
        return findAccount;
    }
    auto newAccountNode=PlatformNode.append_child("Account");
    if (!newAccountNode) { return ErrorAccountTableModule::NewAccount_ERROR; }
    if (!newAccountNode.append_attribute("USERNAME").set_value(account.c_str())) { return ErrorAccountTableModule::NewPlatform_ERROR; }
   /*以下在Account添加新的子节点*/
    auto newPasswordNode = newAccountNode.append_child("Password");
    if (!newPasswordNode) { return ErrorAccountTableModule::NewPassword_ERROR; }

    auto newPhoneNumberNode = newAccountNode.append_child("PhoneNumber");
    if (!newPhoneNumberNode) { return ErrorAccountTableModule::NewPhoneNumber_ERROR; }
    
    auto newUserNode = newAccountNode.append_child("User");
    if (!newUserNode) { return ErrorAccountTableModule::NewUser_ERROR; }

    auto newEncryProperty = newAccountNode.append_child("EncrypyProperty");
    if (!newEncryProperty) { return ErrorAccountTableModule::NewEncrpyProperty_ERROR; }
    
    /*以下在EncrpyProperty节点下添加新的子节点*/
    auto newPasswordLength = newEncryProperty.append_child("PasswordLength");
    if (!newPasswordLength) { return ErrorAccountTableModule::NewPasswordLength_ERROR; }
    if (!newPasswordLength.append_attribute("Minimum")) {
        return ErrorAccountTableModule::NewPasswordLength_ERROR;
    }
    if (!newPasswordLength.append_attribute("Maximum")) {
        return ErrorAccountTableModule::NewPasswordLength_ERROR;
    }

    auto newhaveSpecialSymbolsNode = newEncryProperty.append_child("haveSpecialSymbols");
    if (!newhaveSpecialSymbolsNode) { return ErrorAccountTableModule::NewhaveSpecialSymbols_ERROR; }
    auto newhaveUppercaseLowercaseNode = newEncryProperty.append_child("haveUppercaseLowercase");
    if (!newhaveUppercaseLowercaseNode) { return ErrorAccountTableModule::NewhaveUppercaseLowercase_ERROR; }

    auto newEncrpyIsIrreversible = newEncryProperty.append_child("EncrpyIsIrreversible");
    if (!newEncrpyIsIrreversible) { return ErrorAccountTableModule::NewEncrpyIsIrreversible_ERROR; }


    return ErrorAccountTableModule::No_ERROR;
}

