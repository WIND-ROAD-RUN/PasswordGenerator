#ifndef CONFIGURATIONLOADER_XML_H_
#define CONFIGURATIONLOADER_XML_H_

#include"ConfigurationLoaderAbstract.h"

#include<string>
#include<pugixml.hpp>

/*实现为单例类*/
class ConfigurationLoaderXML 
    :public ConfigurationLoaderAbstract {

private:
    static ConfigurationLoaderXML* m_instance;
    ConfigurationLoaderXML(const std::string& configFilePath)
        :m_configFilePath(configFilePath) {}
    ConfigurationLoaderXML() {}

private:
    std::string m_configFilePath{};
    pugi::xml_document m_doc;
private:
    std::string m_localLanguage{};
    std::pair<std::string, std::string> m_lastLoginAccount{};
    bool m_isRememberPassword{};
    bool m_isAutoLogin{};
public:
    static ConfigurationLoaderXML* 
        getInstance(const std::string& configFilePath) {
        if (!m_instance) {
            m_instance = new ConfigurationLoaderXML(configFilePath);
        }
        return m_instance;
    }
    static ConfigurationLoaderXML*
        getInstance() {
        if (!m_instance) {
            m_instance = new ConfigurationLoaderXML();
        }
        return m_instance;
    }
    ~ConfigurationLoaderXML() { delete m_instance; }


public:
    void setFilePath(const std::string& configFilePath) { m_configFilePath = configFilePath; }
    const std::string Language() const { return m_localLanguage; }
    void setLocalLanguage(const std::string& language) { m_localLanguage = language; }
    void setLastLoginAccount(const std::string& account, const std::string password) { m_lastLoginAccount=std::move(std::pair<std::string, std::string>(account, password)); }
    const std::pair<std::string, std::string>& LastLoginAccount()const { return m_lastLoginAccount; }
    void set_isRememberPassword(bool is) { m_isRememberPassword = is; }
    bool isRememberPassword() const{ return m_isRememberPassword; }
    void set_isAutoLogin(bool is) { m_isAutoLogin = is; }
    bool isAutoLogin() { return m_isAutoLogin; }
public:
    void setNewfile(const std::string & path);
public:
    // 通过 ConfigurationLoaderAbstract 继承
    bool loadConfig() override;
    bool storeConfig() override;

};



#endif // !CONFIGURATIONLOADER_XML_H_

