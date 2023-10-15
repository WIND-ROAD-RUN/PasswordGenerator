#include "ConfigurationLoader-XML.h"
#include<pugixml.hpp>

ConfigurationLoaderXML* ConfigurationLoaderXML::m_instance = nullptr;

bool ConfigurationLoaderXML::loadConfig()
{
    auto Loadresult=m_doc.load_file(m_configFilePath.c_str());
    if (!Loadresult) { return false; }
    auto LocalizationNode = m_doc.child("Localization");
    if (!LocalizationNode) { return false; }

    auto stringLanguageNode = LocalizationNode.child("stringLanguage");
    if (!stringLanguageNode) { return false; }
    setLocalLanguage(stringLanguageNode.text().get());



    auto LastRunInformationNode = LocalizationNode.child("LastRunInformation");
    
    if (!LastRunInformationNode) { return false; }
    auto LastRunAccountNode = LastRunInformationNode.child("LastRunAccount");
    if (!LastRunAccountNode) { return false; }
    setLastLoginAccount
    (std::string(LastRunAccountNode.child("Account").text().get()),
        std::string(LastRunAccountNode.child("Password").text().get()));

    auto IsRememberPasswordNode = LastRunInformationNode.child("IsRemerberPassword");
    if (!IsRememberPasswordNode) { return false; }
    set_isRememberPassword(IsRememberPasswordNode.text().as_bool());
    
    auto IsAutoLoginNode = LastRunInformationNode.child("IsAutoLogin");
    if (!IsAutoLoginNode) { return false; }
    set_isAutoLogin(IsAutoLoginNode.text().as_bool());

    return true;
}

bool ConfigurationLoaderXML::storeConfig()
{
    auto LocalizationNode = m_doc.child("Localization");
    if (!LocalizationNode) { return false; }

    auto stringLanguageNode = LocalizationNode.child("stringLanguage");
    if (!stringLanguageNode) { return false; }
    if (!stringLanguageNode.text().set(m_localLanguage.c_str())) { return false; }



    auto LastRunInformationNode = LocalizationNode.child("LastRunInformation");

    if (!LastRunInformationNode) { return false; }
    auto LastRunAccountNode = LastRunInformationNode.child("LastRunAccount");
    if (!LastRunAccountNode) { return false; }
    LastRunAccountNode.child("Account").text().set(m_lastLoginAccount.first.c_str());
    LastRunAccountNode.child("Password").text().set(m_lastLoginAccount.second.c_str());

    auto IsRememberPasswordNode = LastRunInformationNode.child("IsRemerberPassword");
    if (!IsRememberPasswordNode) { return false; }
    IsRememberPasswordNode.text().set(m_isRememberPassword);

    auto IsAutoLoginNode = LastRunInformationNode.child("IsAutoLogin");
    if (!IsAutoLoginNode) { return false; }
    IsAutoLoginNode.text().set(m_isAutoLogin);

    return m_doc.save_file(m_configFilePath.c_str());
}
