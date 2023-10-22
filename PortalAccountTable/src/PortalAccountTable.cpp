#include "PortalAccountTable.h"

#include"AccountTableXML.h"
#include"PasswordEncrpySimplyAch.h"

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
        for (auto & account:accountList) {
            m_EncrpyCom->decrptForUser(account);
        }
        m_map[platform] = accountList;
    }
    return ErrorPortalAccountTable::NO_ERROR;
}
