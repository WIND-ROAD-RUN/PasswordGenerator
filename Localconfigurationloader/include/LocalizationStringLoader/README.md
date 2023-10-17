# LocalConfigurationLoader

------

# 目录

- [LocalConfigurationLoader类体系简介](#LocalConfigurationLoader类体系简介)
- [LocalConfigurationLoader功能介绍](#LocalConfigurationLoader功能介绍)
- [ConfigurationLoaderAbstract抽象基类的介绍](#ConfigurationLoaderAbstract抽象基类的介绍)
   - [ConfigurationLoaderXML的实现](#ConfigurationLoaderXML的实现)
- [如何进行新的实现](#如何进行新的实现)

# LocalConfigurationLoader类体系简介

LocalConfigurationLoader类族用于实现配置文件加载的功能，通过统一的标准接口，来定义程序运行开始时的加载配置文件的行为。

# LocalConfigurationLoader功能介绍

主要的功能有如下：

- 加载配置文件
- 保存配置文件（方便下一次使用）
- 更改配置文件（）
- 将配置文件信息提供给主程序使用

# ConfigurationLoaderAbstract抽象基类的介绍

`ConfigurationLoaderAbstract`抽象基类定义了LocalConfigurationLoader类族必须定义的接口。

> `virtual bool loadConfig() = 0`：用于将配置文件中的信息加载到内存中去
> `virtual bool storeConfig() = 0`：用于将内存中的配置文件中的信息保存到内存中去。

`ConfigurationLoaderAbstract`的子类应该都实现为单例类，这样确保了在程序中只含有一个加载器对象，防止因为对象内数据不同步而造成的问题。同时也节省了内存。子类标准应该如下：

- 满足抽象基类的接口
- 实现为单例类
- 都含有每一种配置对应的信息
- 均能返回每一种配置信息
- 均能修改每一种配置信息 

## ConfigurationLoaderXML的实现

`ConfigurationLoaderXML`的实现为将配置存储于XML文件中，目前这个实现没有验证XML的数据格式，应该手动确保XML数据格式的正确。具体的XML数据格式应该依赖于`ConfigurationLoaderXML`的实现方式。

> 后期会实现一个通用的`ConfigurationLoaderXML`

这个实现依赖于项目LocalizationStringModule中的类`LocalizationStringXML`,这个类只是对`LocalizationStringXML`的封装。保证上层的统一接口。


`ConfigurationLoaderXML`类的定义：

```cpp
/*实现为单例类*/
class LocalizationStringXML;

class LocalizationStringLoaderXML
    :public LocalizationStringLoaderAbstract {
private:
    static LocalizationStringLoaderXML* m_instance;
    LocalizationStringLoaderXML();
    LocalizationStringLoaderXML(const std::string& filePath, const std::string& language);
private:
    std::string m_XMLFilePath{};
private:
    std::unordered_map<std::string,std::string> m_map;
    std::string m_language{};
    LocalizationStringXML* m_LocalStringComponet{nullptr};
public:
    static LocalizationStringLoaderXML*
        getInstance() {
        if (!m_instance) {
            m_instance = new LocalizationStringLoaderXML();
        }
        return m_instance;
    }
    static LocalizationStringLoaderXML*
        getInstance(const std::string& filePath, const std::string& language) {
        if (!m_instance) {
            m_instance = new LocalizationStringLoaderXML(filePath,language);
        }
        return m_instance;
    }
    ~LocalizationStringLoaderXML();

public:
    void setFilePath(const std::string& filePath) { m_XMLFilePath = filePath; }
    void setLanguage(const std::string& language) { m_language = language; }
public:
    // 通过 LocalizationStringLoaderAbstract 继承
    bool loadData() override;

    const std::string& getString(const std::string id) override;

};
```
如上所示`LocalizationStringLoaderXML`实现为单例类，其中使用`LocalizationStringLoaderXML`必须通过接口`getInstance()`这个接口有两个重载，一个在初始化类时直接设定`m_XMLFilePath`(XML数据文件的路径)，一个是默认初始化`m_XMLFilePath`(XML数据文件的路径)。

> 如何正确使用`LocalizationStringLoaderXML`？

- 在使用前确保使用接口`getInstance()`初始化一个实例
- 保证在调用其他函数之前使用`loadData`接口读取过本地化字符数据文件

> 如何了解接口的具体作用？

由于个人开发精力有限，暂时还未补充每一个接口的介绍。
但是通过接口的函数名字，可以较容易看出每一个接口的作用。

目前XML数据格式时限定（依赖于`LocalizationStringXML`的实现）的，格式如下：
```xml
<?xml version="1.0"?>
<MyLocalizationStringModele_strings>
	<string id="1">
		<language language="USA">login</language>
		<language language="CHN">登录</language>
	</string>
	<string id="2">
		<language language="CHN">注册</language>
		<language language="USA">regist</language>
	</string>
	<string id="3">
		<language language="CHN">保存密码</language>
		<language language="USA">Save Password</language>
	</string>
</MyLocalizationStringModele_strings>

```
在使用数据时一定要确保含有节点`<MyLocalizationStringModele_strings>`。这样能确保加载函数的正确读取。

# 如何进行新的实现

通过继承抽象基类`ConfigurationLoaderAbstract`然后按照满足其[接口标准](# ConfigurationLoaderAbstract抽象基类的介绍)即可，见链接中的接口标准内容。