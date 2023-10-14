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

    return true;
}

bool ConfigurationLoaderXML::storeConfig()
{
    auto LocalizationNode = m_doc.child("Localization");
    if (!LocalizationNode) { return false; }

    auto stringLanguageNode = LocalizationNode.child("stringLanguage");
    if (!stringLanguageNode) { return false; }
    if (!stringLanguageNode.text().set(m_localLanguage.c_str())) { return false; }

    return m_doc.save_file(m_configFilePath.c_str());
}
