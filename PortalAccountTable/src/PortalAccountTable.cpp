#include "PortalAccountTable.h"

#include"AccountTableXML.h"
#include"PasswordEncrpySimplyAch.h"

#include<algorithm>
#include <fstream>
#include<sstream>
#include <iomanip>
#include <openssl/sha.h>

PortalAccountTable* PortalAccountTable::m_instance = nullptr;

PortalAccountTable::PortalAccountTable
(const ATMAstring& filePath, const ATMAstring& UID)
    :m_filePath(filePath),
    m_UID(UID),
    m_accountTableXML(new AccountTableXML),
    m_EncrpyCom(new PasswordEncrpySimplyAch)
{
}

PortalAccountTable::PortalAccountTable()
    :PortalAccountTable("","")
{
}

PortalAccountTable::~PortalAccountTable()
{
    delete m_accountTableXML;
    delete m_EncrpyCom;
}

std::string PortalAccountTable::getKey()
{
    const auto& data = m_UID;
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data.c_str(), data.length());

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    ss << std::hex << std::uppercase;

    for (int i = 0; i < 32; i++) {
        ss << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}

ErrorPortalAccountTable 
PortalAccountTable::ini_portal()
{
    if (m_filePath.empty()) { return ErrorPortalAccountTable::PATH_ERROR; }
    
    m_accountTableXML->setFilePath(m_filePath);
    m_accountTableXML->setUID(m_UID);
    m_EncrpyCom->setKey(getKey());
    
    auto iniResult=m_accountTableXML->ini_module();
    if (iniResult!=ErrorAccountTableModule::No_ERROR) {
        return ErrorPortalAccountTable::initialization_ERROR;
    }
    auto Platformlist = m_accountTableXML->getPlatformList();
    for (auto & platform:Platformlist) {
        auto accountList = m_accountTableXML->getAccountList(platform);
        for (auto & account:accountList) {
            m_EncrpyCom->decrptForUser(account);
        }
        m_map[platform] = accountList;
    }
    return ErrorPortalAccountTable::NO_ERROR;
}

ErrorAccountTableModule 
PortalAccountTable::save_change()
{
   return m_accountTableXML->save();
}

AccountInfo 
PortalAccountTable::search_account
(const ATMAstring& platform, const ATMAstring& accountName)
{
    AccountInfo result;
    auto accountListPair = m_map.find(platform);
    if (accountListPair ==m_map.end()) {
        result.accountName = "";
        return result;
    }
    const auto  & accountList = accountListPair->second; 
    
    auto accountInfo=find_if
    (accountList.begin(),
        accountList.end(),
        [accountName](const AccountInfo & account) {
            return account.accountName == accountName;
        });
    if (accountInfo==accountList.end()) {
        result.accountName = "";
        return result;
    }
    result = *accountInfo;

    return result;
}

ErrorAccountTableModule 
PortalAccountTable::set_account
(const ATMAstring& platform, const AccountInfo& accountInfo)
{
    AccountInfo result;
    auto accountListPair = m_map.find(platform);
    if (accountListPair == m_map.end()) {
        return ErrorAccountTableModule::NoPlatformNode;
    }
    auto& accountList = accountListPair->second;

    auto findAccountInfo = find_if
    (accountList.begin(),
        accountList.end(),
        [accountInfo](const AccountInfo& account) {
            return account.accountName == accountInfo.accountName;
        });
    if (findAccountInfo == accountList.end()) {
        return ErrorAccountTableModule::NoAccountNode;
    }


    auto saveFileResult=m_accountTableXML->setAccount(platform, m_EncrpyCom->encrpyForSave(accountInfo));
    if (saveFileResult!=ErrorAccountTableModule::No_ERROR) {
        return saveFileResult;
    }

    *findAccountInfo = accountInfo;

    return ErrorAccountTableModule::No_ERROR;
}

ErrorAccountTableModule 
PortalAccountTable::newAccount
(const ATMAstring& platform, const AccountInfo& accountInfo)
{
    auto accountListPair = m_map.find(platform);
    if (accountListPair == m_map.end()) {
        return ErrorAccountTableModule::NoPlatformNode;
    }
    auto& accountList = accountListPair->second;

    auto findAccountInfo = find_if
    (accountList.begin(),
        accountList.end(),
        [accountInfo](const AccountInfo& account) {
            return account.accountName == accountInfo.accountName;
        });
    if (findAccountInfo != accountList.end()) {
        return ErrorAccountTableModule::AccountAlreadyExist;
    }

    auto saveFileResult= m_accountTableXML->NewAccount(platform, m_EncrpyCom->encrpyForSave(accountInfo));
    if (saveFileResult != ErrorAccountTableModule::No_ERROR) { return saveFileResult; }

    accountList.push_back(accountInfo);
    m_map[platform] = accountList;

    return ErrorAccountTableModule::No_ERROR;
}

ErrorAccountTableModule 
PortalAccountTable::newPlatform
(const ATMAstring& platform)
{
    auto accountListPair = m_map.find(platform);
    if (accountListPair != m_map.end()) {
        return ErrorAccountTableModule::PlatformAlreadyExist;
    }
    m_map[platform] = ATMAAccountList();

    m_accountTableXML->NewPlatform(platform);

    return ErrorAccountTableModule::No_ERROR;
}

ErrorAccountTableModule 
PortalAccountTable::deletePlatform
(const ATMAstring& platform)
{
    auto accountListPair = m_map.find(platform);
    if (accountListPair == m_map.end()) {
        return ErrorAccountTableModule::NoPlatformNode;
    }

    m_map.erase(platform);
    auto deleteResult=m_accountTableXML->deletePlatform(platform);
    return deleteResult;
}

ErrorAccountTableModule 
PortalAccountTable::deleteAccount
(const ATMAstring& platform, const ATMAstring& accountName)
{
    auto accountListPair = m_map.find(platform);
    if (accountListPair == m_map.end()) {
        return ErrorAccountTableModule::NoPlatformNode;
    }
    auto& accountList = accountListPair->second;

    auto accountInfo = find_if
    (accountList.begin(),
        accountList.end(),
        [accountName](const AccountInfo& account) {
            return account.accountName == accountName;
        });
    if (accountInfo == accountList.end()) {
        return ErrorAccountTableModule::NoAccountNode;
    }

    auto deleteResult = m_accountTableXML->deleteAccount(platform,accountName);
    accountList.erase(accountInfo);

    return deleteResult;
}

ATMAStringList  
PortalAccountTable::PlatformList()
{
    return std::move(m_accountTableXML->getPlatformList());
}

ATMAAccountList 
PortalAccountTable::AccountList
(const ATMAstring& platform)
{
    auto accountList = m_accountTableXML->getAccountList(platform);
    for (auto & account:accountList) {
        m_EncrpyCom->decrptForUser(account);
    }
    return std::move(accountList);
}

ATMAint PortalAccountTable::AccountNumber() {
    ATMAint result{ 0 };

    for (const auto & platform:m_map) {
        result+=platform.second.size();
    }
    return result;
}

ATMAstring 
PortalAccountTable::encrpyForUser
(const AccountInfo& account) {
   auto result= m_EncrpyCom->encrpyForSave(account);
   return result.password;
}

void 
PortalAccountTable::setNewFile
(const std::string& filePath, const std::string& UID)
{
    m_accountTableXML->setNewFile(filePath,UID);
}
