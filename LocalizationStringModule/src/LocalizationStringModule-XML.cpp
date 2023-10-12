#include "LocalizationStringModule-XML.h"

std::string LocalizationStringXML::localString(const std::string& id, const std::string & local)
{
    std::string result{};
    localString(result,id,local);
    return result;
}

bool LocalizationStringXML::storeLocalString(const std::string& id, const std::string& local, const std::string& src)
{
    return false;
}

bool LocalizationStringXML::loadFile()
{
    if (m_doc.load_file(m_filePath.c_str())) { return true; }
    else { return false; }
}

bool LocalizationStringXML::localString(std::string& target, const std::string& id, const std::string& local)
{
    auto LocalStringNode = m_doc.child("MyLocalizationStringModele_strings");
    auto stringNode = LocalStringNode.find_child_by_attribute("id",id.c_str());
    if (stringNode.empty()) { return false; }
    
    auto languageNode = stringNode.find_child_by_attribute("local",local.c_str());
    if (languageNode.empty()) { return false; }
    target = move(std::string(languageNode.text().get()));
    
    return true;
}
