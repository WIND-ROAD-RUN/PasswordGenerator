#include "PortalAccountTable.h"

#include"AccountTableXML.h"
#include"PasswordEncrpySimplyAch.h"

#include<algorithm>

PortalAccountTable* PortalAccountTable::m_instance = nullptr;

PortalAccountTable::PortalAccountTable
(const ATMAstring& filePath, const ATMAstring& UID)
    :m_filePath(filePath),m_UID(UID),m_accountTableXML(new AccountTableXML),m_EncrpyCom(new PasswordEncrpySimplyAch)
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

ErrorPortalAccountTable PortalAccountTable::ini_portal()
{
    if (m_filePath.empty()) { return ErrorPortalAccountTable::PATH_ERROR; }
    
    m_accountTableXML->setFilePath(m_filePath);
    m_accountTableXML->setUID(m_UID);
    
    auto iniResult=m_accountTableXML->ini_module();
    if (iniResult!=ErrorAccountTableModule::No_ERROR) {
        return ErrorPortalAccountTable::initialization_ERROR;
    }
    auto Platformlist = m_accountTableXML->getPlatformList();
    for (const auto & platform:Platformlist) {
        auto accountList = m_accountTableXML->getAccountList(platform);
        for (const auto & account:accountList) {
            m_EncrpyCom->decrptForUser(account);
        }
        m_map[platform] = accountList;
    }
    return ErrorPortalAccountTable::NO_ERROR;
}

ErrorAccountTableModule PortalAccountTable::save_change()
{
   return m_accountTableXML->save();
}

AccountInfo PortalAccountTable::search_account(const ATMAstring& platform, const ATMAstring& accountName)
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

ErrorAccountTableModule PortalAccountTable::set_account(const ATMAstring& platform, const AccountInfo& accountInfo)
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

ErrorAccountTableModule PortalAccountTable::newAccount(const ATMAstring& platform, const AccountInfo& accountInfo)
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
    if (findAccountInfo == accountList.end()) {
        return ErrorAccountTableModule::AccountAlreadyExist;
    }

    auto saveFileResult= m_accountTableXML->NewAccount(platform, m_EncrpyCom->encrpyForSave(accountInfo));
    if (saveFileResult != ErrorAccountTableModule::No_ERROR) { return saveFileResult; }

    accountList.push_back(accountInfo);

    return ErrorAccountTableModule::No_ERROR;
}

ErrorAccountTableModule PortalAccountTable::deletePlatform(const ATMAstring& platform)
{
    auto accountListPair = m_map.find(platform);
    if (accountListPair == m_map.end()) {
        return ErrorAccountTableModule::NoPlatformNode;
    }

    m_map.erase(platform);
    auto deleteResult=m_accountTableXML->deletePlatform(platform);
    return deleteResult;
}

ErrorAccountTableModule PortalAccountTable::deleteAccount(const ATMAstring& platform, const ATMAstring& accountName)
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

ATMAStringList  PortalAccountTable::PlatformList()
{
    return std::move(m_accountTableXML->getPlatformList());
}

ATMAAccountList PortalAccountTable::AccountList(const ATMAstring& platform)
{
    return std::move(m_accountTableXML->getAccountList(platform));
}
