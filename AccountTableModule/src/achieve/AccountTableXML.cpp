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
    pugi::xml_node accountNode;
    auto findAccount = findAccountNode(platform,account,accountNode);
    if (findAccount!=ErrorAccountTableModule::AccountAlreadyExist) {
        return findAccount;
    }

    auto passwordNode=accountNode.child("Password");
    if (!passwordNode.text().set(password.c_str())) {
        return ErrorAccountTableModule::setPassword_ERROR;
    }
    return ErrorAccountTableModule::No_ERROR;
}

ErrorAccountTableModule AccountTableXML::setPhoneNumber(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& phoneNumber)
{
    pugi::xml_node accountNode;
    auto findAccount = findAccountNode(platform, account, accountNode);
    if (findAccount != ErrorAccountTableModule::AccountAlreadyExist) {
        return findAccount;
    }

    auto PhoneNumberNode = accountNode.child("PhoneNumber");
    if (!PhoneNumberNode.text().set(phoneNumber.c_str())) {
        return ErrorAccountTableModule::setPhoneNumber_ERROR;
    }
    return ErrorAccountTableModule::No_ERROR;
}

ErrorAccountTableModule AccountTableXML::setUser(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& user)
{
    pugi::xml_node accountNode;
    auto findAccount = findAccountNode(platform, account, accountNode);
    if (findAccount != ErrorAccountTableModule::AccountAlreadyExist) {
        return findAccount;
    }

    auto UserNode = accountNode.child("User");
    if (!UserNode.text().set(user.c_str())) {
        return ErrorAccountTableModule::setUser_ERROR;
    }
    return ErrorAccountTableModule::No_ERROR;
}


ErrorAccountTableModule AccountTableXML::setPasswordLength(const ATMAstring& platform, const ATMAstring& account, ATMAint minimum, ATMAint maximum)
{
    pugi::xml_node accountNode;
    auto findAccount = findAccountNode(platform, account, accountNode);
    if (findAccount != ErrorAccountTableModule::AccountAlreadyExist) {
        return findAccount;
    }

    auto EncrypyPropertyNode=accountNode.child("EncrypyProperty");

    auto PasswordLengthNode = EncrypyPropertyNode.child("PasswordLength");
    if (!PasswordLengthNode.attribute("Minimum").set_value(minimum)) {
        return ErrorAccountTableModule::setPasswordLength_ERROR;
    }
    if (!PasswordLengthNode.attribute("Maximum").set_value(maximum)) {
        return ErrorAccountTableModule::setPasswordLength_ERROR;
    }
    return ErrorAccountTableModule::No_ERROR;
}

ErrorAccountTableModule AccountTableXML::sethaveSpecialSymbols(const ATMAstring& platform, const ATMAstring& account, ATMAbool haveSpecialSymbols)
{
    pugi::xml_node accountNode;
    auto findAccount = findAccountNode(platform, account, accountNode);
    if (findAccount != ErrorAccountTableModule::AccountAlreadyExist) {
        return findAccount;
    }

    auto EncrypyPropertyNode = accountNode.child("EncrypyProperty");

    auto haveSpecialSymbolsNode = EncrypyPropertyNode.child("haveSpecialSymbols");
    if (!haveSpecialSymbolsNode.text().set(haveSpecialSymbols)) {
        return ErrorAccountTableModule::sethaveSpecialSymbols_ERROR;
    }
    return ErrorAccountTableModule::No_ERROR;
}

ErrorAccountTableModule AccountTableXML::sethaveUppercaseLowercase(const ATMAstring& platform, const ATMAstring& account, ATMAbool haveUppercaseLowercase)
{
    pugi::xml_node accountNode;
    auto findAccount = findAccountNode(platform, account, accountNode);
    if (findAccount != ErrorAccountTableModule::AccountAlreadyExist) {
        return findAccount;
    }

    auto EncrypyPropertyNode = accountNode.child("EncrypyProperty");

    auto haveUppercaseLowercaseNode = EncrypyPropertyNode.child("haveUppercaseLowercase");
    if (!haveUppercaseLowercaseNode.text().set(haveUppercaseLowercase)) {
        return ErrorAccountTableModule::sethaveUppercaseLowercase_ERROR;
    }
    return ErrorAccountTableModule::No_ERROR;
}

ErrorAccountTableModule AccountTableXML::setEncrpyIsIrreversible(const ATMAstring& platform, const ATMAstring& account, ATMAbool EncrpyIsIrreversible)
{
    pugi::xml_node accountNode;
    auto findAccount = findAccountNode(platform, account, accountNode);
    if (findAccount != ErrorAccountTableModule::AccountAlreadyExist) {
        return findAccount;
    }

    auto EncrypyPropertyNode = accountNode.child("EncrypyProperty");

    auto EncrpyIsIrreversibleNode = EncrypyPropertyNode.child("EncrpyIsIrreversible");
    if (!EncrpyIsIrreversibleNode.text().set(EncrpyIsIrreversible)) {
        return ErrorAccountTableModule::setEncrpyIsIrreversible_ERROR;
    }
    return ErrorAccountTableModule::No_ERROR;
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
    auto AccountTableNode=m_doc.child("AccountTable");
    auto platformNode = AccountTableNode.find_child_by_attribute("NAME", platform.c_str());
    if (!AccountTableNode.remove_child(platformNode)){
        return ErrorAccountTableModule::deletePlatform_ERROR;
    }
    return ErrorAccountTableModule::No_ERROR;
}

ErrorAccountTableModule AccountTableXML::deleteAccount(const ATMAstring& platform, const ATMAstring& account)
{
    pugi::xml_node platformNode; 
    findPlatformNode(platform, platformNode);
    auto accountNode = platformNode.find_child_by_attribute("USERNAME",account.c_str());
    if (!platformNode.remove_child(accountNode)) {
        return ErrorAccountTableModule::deletePlatform_ERROR;
    }
    return ErrorAccountTableModule::No_ERROR;
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

ATMAstring AccountTableXML::Password(const ATMAstring& platform, const ATMAstring& account)
{
    pugi::xml_node accountNode;
    findAccountNode(platform,account,accountNode);
    if (!accountNode) {
        return std::move(ATMAstring(""));
    }
    return std::move(ATMAstring(accountNode.child("Password").text().get()));
}

ATMAstring AccountTableXML::PhoneNumber(const ATMAstring& platform, const ATMAstring& account)
{
    pugi::xml_node accountNode;
    findAccountNode(platform, account, accountNode);
    if (!accountNode) {
        return std::move(ATMAstring(""));
    }
    return std::move(ATMAstring(accountNode.child("PhoneNumber").text().get()));
}

ATMAstring AccountTableXML::User(const ATMAstring& platform, const ATMAstring& account)
{
    pugi::xml_node accountNode;
    findAccountNode(platform, account, accountNode);
    if (!accountNode) {
        return std::move(ATMAstring(""));
    }
    return std::move(ATMAstring(accountNode.child("User").text().get()));
}

ATMApair AccountTableXML::PasswordLength(const ATMAstring& platform, const ATMAstring& account)
{
    pugi::xml_node accountNode;
    findAccountNode(platform, account, accountNode);
    if (!accountNode) {
        return std::move(ATMApair(0,0));
    }
    auto EncrypyPropertyNode = accountNode.child("EncrypyProperty");
    ATMApair Length(EncrypyPropertyNode.child("PasswordLength").attribute("Minimum").as_int(),
        EncrypyPropertyNode.child("PasswordLength").attribute("Maximum").as_int());
    return std::move(Length);
}

ATMAbool AccountTableXML::haveSpecialSymbols(const ATMAstring& platform, const ATMAstring& account)
{
    pugi::xml_node accountNode;
    findAccountNode(platform, account, accountNode);
    if (!accountNode) {
        return false;
    }
    auto haveSpecialSymbolsNode = accountNode.child("EncrypyProperty").child("haveSpecialSymbols");
    return haveSpecialSymbolsNode.text().as_bool();
}

ATMAbool AccountTableXML::haveUppercaseLowercase(const ATMAstring& platform, const ATMAstring& account)
{
    pugi::xml_node accountNode;
    findAccountNode(platform, account, accountNode);
    if (!accountNode) {
        return false;
    }
    auto haveUppercaseLowercaseNode = accountNode.child("EncrypyProperty").child("haveUppercaseLowercase");
    return haveUppercaseLowercaseNode.text().as_bool();
}

ATMAbool AccountTableXML::EncrpyIsIrreversible(const ATMAstring& platform, const ATMAstring& account)
{
    pugi::xml_node accountNode;
    findAccountNode(platform, account, accountNode);
    if (!accountNode) {
        return false;
    }
    auto EncrpyIsIrreversibleNode = accountNode.child("EncrypyProperty").child("EncrpyIsIrreversible");
    return EncrpyIsIrreversibleNode.text().as_bool();
}

AccountInfo AccountTableXML::Account(const ATMAstring& platform, const ATMAstring& account)
{
    AccountInfo result;

    result.accountName = account;
    result.EncrpyIsIrreversible = EncrpyIsIrreversible(platform,account);
    result.haveSpecialSymbols = haveSpecialSymbols(platform, account);
    result.haveUppercaseLowercase = haveUppercaseLowercase(platform, account);
    result.password = Password(platform, account);
    result.passwordLength = PasswordLength(platform, account);
    result.phoneNumber = PhoneNumber(platform, account);
    result.User = User(platform, account);

    return result;
}

ErrorAccountTableModule AccountTableXML::NewAccount(const ATMAstring& platform, const AccountInfo& account)
{
    /*��ѯ�Ƿ���Ŀ��ƽ̨�Ľڵ���û���򷵻ش������*/
    pugi::xml_node PlatformNode;
    auto findPlatform = findPlatformNode(platform, PlatformNode);
    if (findPlatform != ErrorAccountTableModule::PlatformAlreadyExist) { return findPlatform; }

    /*��ѯ�Ƿ��Ѿ�����ͬ���˻��ڵ㣬�еĻ����ش�����룬û�����½�һ��*/
    auto findAccount = findAccountNode(platform, account.accountName);
    if (findAccount == ErrorAccountTableModule::AccountAlreadyExist) {
        return findAccount;
    }
    auto newAccountNode = PlatformNode.append_child("Account");
    if (!newAccountNode) { return ErrorAccountTableModule::NewAccount_ERROR; }
    if (!newAccountNode.append_attribute("USERNAME").set_value(account.accountName.c_str())) { return ErrorAccountTableModule::NewPlatform_ERROR; }
    /*������Account����µ��ӽڵ�*/
    auto newPasswordNode = newAccountNode.append_child("Password");
    if (!newPasswordNode) { return ErrorAccountTableModule::NewPassword_ERROR; }
    newPasswordNode.text().set(account.password.c_str());

    auto newPhoneNumberNode = newAccountNode.append_child("PhoneNumber");
    if (!newPhoneNumberNode) { return ErrorAccountTableModule::NewPhoneNumber_ERROR; }
    newPhoneNumberNode.text().set(account.phoneNumber.c_str());

    auto newUserNode = newAccountNode.append_child("User");
    if (!newUserNode) { return ErrorAccountTableModule::NewUser_ERROR; }
    newUserNode.text().set(account.User.c_str());

    auto newEncryProperty = newAccountNode.append_child("EncrypyProperty");
    if (!newEncryProperty) { return ErrorAccountTableModule::NewEncrpyProperty_ERROR; }

    /*������EncrpyProperty�ڵ�������µ��ӽڵ�*/
    auto newPasswordLengthNode = newEncryProperty.append_child("PasswordLength");
    if (!newPasswordLengthNode) { return ErrorAccountTableModule::NewPasswordLength_ERROR; }
    if (!newPasswordLengthNode.append_attribute("Minimum").set_value(account.passwordLength.first)) {
        return ErrorAccountTableModule::NewPasswordLength_ERROR;
    }
    if (!newPasswordLengthNode.append_attribute("Maximum").set_value(account.passwordLength.second)) {
        return ErrorAccountTableModule::NewPasswordLength_ERROR;
    }

    auto newhaveSpecialSymbolsNode = newEncryProperty.append_child("haveSpecialSymbols");
    if (!newhaveSpecialSymbolsNode) { return ErrorAccountTableModule::NewhaveSpecialSymbols_ERROR; }
    newhaveSpecialSymbolsNode.text().set(account.haveSpecialSymbols);

    auto newhaveUppercaseLowercaseNode = newEncryProperty.append_child("haveUppercaseLowercase");
    if (!newhaveUppercaseLowercaseNode) { return ErrorAccountTableModule::NewhaveUppercaseLowercase_ERROR; }
    newhaveUppercaseLowercaseNode.text().set(account.haveUppercaseLowercase);

    auto newEncrpyIsIrreversible = newEncryProperty.append_child("EncrpyIsIrreversible");
    if (!newEncrpyIsIrreversible) { return ErrorAccountTableModule::NewEncrpyIsIrreversible_ERROR; }
    newEncrpyIsIrreversible.text().set(account.EncrpyIsIrreversible);


    return ErrorAccountTableModule::No_ERROR;

}

ErrorAccountTableModule AccountTableXML::setAccount(const ATMAstring& platform, const AccountInfo& account)
{
    pugi::xml_node accountNode;
    auto findAccount=findAccountNode(platform,account.accountName,accountNode);
    if (findAccount!=ErrorAccountTableModule::AccountAlreadyExist) {
        return findAccount;
    }
    ErrorAccountTableModule result;

    result=setPassword(platform,account.accountName,account.password);
    if (result != ErrorAccountTableModule::No_ERROR) { return result; }
    result=setPhoneNumber(platform, account.accountName, account.phoneNumber);
    if (result != ErrorAccountTableModule::No_ERROR) { return result; }
    result=setUser(platform,account.accountName,account.User);
    if (result != ErrorAccountTableModule::No_ERROR) { return result; }
    result=setPasswordLength(platform,account.accountName,account.passwordLength.first,account.passwordLength.second);
    if (result != ErrorAccountTableModule::No_ERROR) { return result; }
    result=sethaveSpecialSymbols(platform,account.accountName,account.haveSpecialSymbols);
    if (result != ErrorAccountTableModule::No_ERROR) { return result; }
    result=sethaveUppercaseLowercase(platform,account.accountName,account.haveUppercaseLowercase);
    if (result != ErrorAccountTableModule::No_ERROR) { return result; }
    result=setEncrpyIsIrreversible(platform,account.accountName,account.EncrpyIsIrreversible);
    
    return result;
}

ATMAStringList AccountTableXML::getPlatformList()
{
    ATMAStringList result;
    for (const auto & PlatformNode:m_doc.child("AccountTable").children()) {
        result.push_back(ATMAstring(PlatformNode.attribute("NAME").value()));
    }
    return std::move(result);
}

ATMAAccountList AccountTableXML::getAccountList(const ATMAstring& platform)
{
    ATMAAccountList result;
    pugi::xml_node platformNode;
    findPlatformNode(platform, platformNode);
    for (const auto & accountNode: platformNode.children()) {
        result.push_back(Account(platform, accountNode.attribute("USERNAME").value()));
    }
    return std::move(result);
}



ErrorAccountTableModule AccountTableXML::NewAccount(const ATMAstring& platform, const ATMAstring& account)
{
    /*��ѯ�Ƿ���Ŀ��ƽ̨�Ľڵ���û���򷵻ش������*/
    pugi::xml_node PlatformNode;
    auto findPlatform = findPlatformNode(platform, PlatformNode);
    if (findPlatform != ErrorAccountTableModule::PlatformAlreadyExist) { return findPlatform; }

    /*��ѯ�Ƿ��Ѿ�����ͬ���˻��ڵ㣬�еĻ����ش�����룬û�����½�һ��*/
    auto findAccount=findAccountNode(platform,account);
    if (findAccount==ErrorAccountTableModule::AccountAlreadyExist) {
        return findAccount;
    }
    auto newAccountNode=PlatformNode.append_child("Account");
    if (!newAccountNode) { return ErrorAccountTableModule::NewAccount_ERROR; }
    if (!newAccountNode.append_attribute("USERNAME").set_value(account.c_str())) { return ErrorAccountTableModule::NewPlatform_ERROR; }
   /*������Account����µ��ӽڵ�*/
    auto newPasswordNode = newAccountNode.append_child("Password");
    if (!newPasswordNode) { return ErrorAccountTableModule::NewPassword_ERROR; }

    auto newPhoneNumberNode = newAccountNode.append_child("PhoneNumber");
    if (!newPhoneNumberNode) { return ErrorAccountTableModule::NewPhoneNumber_ERROR; }
    
    auto newUserNode = newAccountNode.append_child("User");
    if (!newUserNode) { return ErrorAccountTableModule::NewUser_ERROR; }

    auto newEncryProperty = newAccountNode.append_child("EncrypyProperty");
    if (!newEncryProperty) { return ErrorAccountTableModule::NewEncrpyProperty_ERROR; }
    
    /*������EncrpyProperty�ڵ�������µ��ӽڵ�*/
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

