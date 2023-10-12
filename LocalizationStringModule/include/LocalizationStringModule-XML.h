#ifndef LOCALIZATIONSTRINGMODULE_XML_H_
#define LOCALIZATIONSTRINGMODULE_XML_H_

#include"LocalizationStringModuleAbstact.h"
#include<pugixml.hpp>
#include<string>

class LocalizationStringXML 
    :public LocalizationStringModuleAbstract {
private:
    std::string m_filePath{};
    pugi::xml_document  m_doc;
public:
    LocalizationStringXML(const std::string& filePath) :m_filePath(filePath) {}
    LocalizationStringXML() {}
    ~LocalizationStringXML() {}
public:
    // 通过 LocalizationStringModuleAbstract 继承
    std::string localString(const std::string& id, const std::string &local) override;

    bool storeLocalString(const std::string& id, const std::string& local, const std::string& src) override;
public:
    bool loadFile();
    void setFilePath(const std::string& filePath) { m_filePath = filePath; }

    // 通过 LocalizationStringModuleAbstract 继承
    bool localString(std::string& target, const std::string& id, const std::string& local) override;
};


#endif // !LOCALIZATIONSTRINGMODULE_XML_H_

