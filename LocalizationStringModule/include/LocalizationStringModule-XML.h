#ifndef LOCALIZATIONSTRINGMODULE_XML_H_
#define LOCALIZATIONSTRINGMODULE_XML_H_

/*
LocalizationStringXML是LocalizationStringModuleAbstract的子类，通过XML作为数据文件存储本地化字符串，
遵循抽象基类的接口。
*/

/*
    注意！！！
    这个类的实现依赖第三方库pugixml，若项目没有安装第三方库，请在项目的NuGet程序包管理器中
    为项目安装第三库pugixml或者自己下载源文件添加到项目中，自行构建
*/

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
    void setFilePath(const std::string& filePath) { m_filePath = filePath; }
public:
    // 通过 LocalizationStringModuleAbstract 继承
    std::string localString(const std::string& id, const std::string &local) override;

    bool storeLocalString(const std::string& id, const std::string& local, const std::string& src) override;
   
    bool localString(std::string& target, const std::string& id, const std::string& local) override;
    
    bool loadFile()override;
};


#endif // !LOCALIZATIONSTRINGMODULE_XML_H_

