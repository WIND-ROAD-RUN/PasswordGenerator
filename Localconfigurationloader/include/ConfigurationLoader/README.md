# LocalizationStringLoader

------

# 目录

- [LocalizationStringLoader类体系简介](#LocalizationStringLoader类体系简介)
- [LocalizationStringLoader功能介绍](#LocalizationStringLoader功能介绍)
- [LocalizationStringLoaderAbstract抽象基类的介绍](#LocalizationStringLoaderAbstract抽象基类的介绍)
   - [LocalizationStringLoaderXML的实现](#LocalizationStringLoaderXML的实现)
- [如何进行新的实现](#如何进行新的实现)

# LocalizationStringLoader类体系简介

LocalizationStringLoader类族用于实现本地化字符串文件加载的功能，通过统一的标准接口，来定义程序运行开始时的加载本地化字符串文件的行为。

# LocalizationStringLoader功能介绍

主要的功能有如下：

- 加载本地化字符串文件
- 读取本地化字符串

# LocalizationStringLoaderAbstract抽象基类的介绍

`LocalizationStringLoaderAbstract`抽象基类定义了LocalizationStringLoader类族必须定义的接口。

> `virtual bool loadData()=0`：用于将本地化字符串文件中的信息加载到内存中去
> `virtual const std::string & getString(const std::string id) = 0 `：用于通过字符串id查询对应的字符串。

`LocalizationStringLoaderAbstrac`的子类应该都实现为单例类，这样确保了在程序中只含有一个加载器对象，防止因为对象内数据不同步而造成的问题。同时也节省了内存。子类标准应该如下：

- 满足抽象基类的接口
- 实现为单例类

## LocalizationStringLoaderXML的实现

`LocalizationStringLoaderXML`的实现为字符串存储于XML文件中，目前这个实现没有验证XML的数据格式，应该手动确保XML数据格式的正确。具体的XML数据格式应该依赖于`LocalizationStringModule`的实现方式。
加载到内存中的数据形式是stl中的`std::unordered_map<std::string,std::string>`,通过使用模块`LocalizationStringModule`来读取数据，然后读到自己文件中

> 后期会实现一个通用的`LocalizationStringLoaderXML`

`LocalizationStringLoaderXML`类的定义如下：
```cpp

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
    // 通过 ConfigurationLoaderAbstract 继承
    bool loadConfig() override;
    bool storeConfig() override;

};

```

如上所示`ConfigurationLoaderXML`实现为单例类，其中使用`ConfigurationLoaderXML`必须通过接口`getInstance()`这个接口有两个重载，一个在初始化类时直接设定`configFilePath`(XML数据文件的路径)，一个是默认初始化`configFilePath`(XML数据文件的路径)。

> 如何正确使用`ConfigurationLoaderXML`？

- 在使用前确保使用接口`getInstance()`初始化一个实例
- 保证在调用其他函数之前使用`loadConfig()`接口读取过配置文件
- 在更改过配置后，数据只会保存至内存中，若要写入数据文件中请使用接口`storeConfig()`

> 如何了解接口的具体作用？

由于个人开发精力有限，暂时还未补充每一个接口的介绍。
但是通过接口的函数名字，可以较容易看出每一个接口的作用。

目前XML数据格式时限定的，格式如下：
```xml
<?xml version="1.0"?>
<Localization>
	<stringLanguage>USA</stringLanguage>
	<LastRunInformation>
		<LastRunAccount>
			<Account>1</Account>
			<Password>1</Password>
		</LastRunAccount>
		<IsRemerberPassword>false</IsRemerberPassword>
		<IsAutoLogin>false</IsAutoLogin>
	</LastRunInformation>
</Localization>

```
在使用数据时一定要确保含有节点`<Localization>`、`<stringLanguage>`、`<LastRunInformation>`、`<LastRunAccount>`、`<IsRemerberPassword>`和`<IsAutoLogin>`。这样能确保加载函数的正确读取。

# 如何进行新的实现

通过继承抽象基类`LocalizationStringLoaderAbstract`然后按照满足其[接口标准](# LocalizationStringLoaderAbstract抽象基类的介绍)即可，见链接中的接口标准内容。