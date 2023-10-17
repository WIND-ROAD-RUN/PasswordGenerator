# LocalizationStringModule

------

# 目录

- [LocalizationStringModule类体系简介](#LocalizationStringModule类体系简介)
- [LocalizationStringModule功能介绍](#LocalizationStringModule功能介绍)
- [LocalizationStringModuleAbstract抽象基类的介绍](#LocalizationStringModuleAbstract抽象基类的介绍)
   - [LocalizationStringXML的实现](#LocalizationStringXML的实现)
- [如何进行新的实现](#如何进行新的实现)

# LocalizationStringModule类体系简介

LocalizationStringModule类族实现了本地化字符串的存储以及读取的功能，是操作数据文件或是远程服务器的一层

# LocalizationStringModule功能介绍

主要的功能有如下：

- 加载本地化字符串文件或是远程数据
- 读取本地化字符串
- 更改本地化字符串

# LocalizationStringModuleAbstract抽象基类的介绍

`LocalizationStringModuleAbstract`抽象基类定义了LocalizationStringLoader类族必须定义的接口。

> 接口的定义以及需要满足的功能

- `virtual std::string localString(const std::string & id,const std::string & local="CHN") = 0`:这个接口根据id和local来查询对应的本地化字符串，若查询到了应该返回一个string若没有查询到则返回空的string这个接口应该由`virtual bool localString(std::string & target ,const std::string & id,const std::string & local="CHN")=0`实现
- `virtual bool localString(std::string & target ,const std::string & id,const std::string & local="CHN")=0`:这个接口根据id，local查询对应的本地化字符串，若查询到了将其赋值给target并返回`true`，若没有查询到则返回`false`，且target不应该改变。
- `virtual bool storeLocalString(const std::string & id, const std::string& language,const std::string & src) = 0`:保存本地化字符串，形参对应id（字符串id），language（存储的语言），src（存储的字符串），在找不到对应节点的情况下保存，并且返回`true`，如果已有对应节点则返回`false`
- `virtual bool changeLocalString(const std::string& id, const std::string& language, const std::string& src)=0`:更改本地化字符串，形参对应id（字符串id），language（存储的语言），src（要更改为的字符串）在找到对应节点的情况下更改，并且返回`true`，如果没有对应节点则返回`false`
- `virtual bool saveFile() = 0`:保存所有更改的数据到文件中如果保存成功返回`true`,如果保存失败返回`false`
- `virtual bool loadFile()=0`:这个接口用于加载数据文件，如果加载成功返回`true`,如果加载失败返回`false`

`LocalizationStringModuleAbstract`的子类的标准应该如下：

- 满足抽象基类的接口

## LocalizationStringXML的实现

`LocalizationStringXML`的实现为字符串存储于XML文件中，目前这个实现没有验证XML的数据格式，应该手动确保XML数据格式的正确。这个实现保证了对于本地化字符串数据的保存以及更改的功能。
> 这个实现基于第三方库pugixml ！！！！

具体的接口实现使用了第三方库，对于每一种功能都进行了实现，方便上层的调用。

`LocalizationStringXML`类的定义如下：
```cpp

/*实现为单例类*/
class LocalizationStringXML 
    :public LocalizationStringModuleAbstract {
private:
    std::string m_filePath{};
    pugi::xml_document  m_doc;
public:
    LocalizationStringXML(const std::string& filePath) :m_filePath(filePath) {}//最好使用这个方式初始化类
    LocalizationStringXML() {}
    ~LocalizationStringXML() {}
public:
    void setFilePath(const std::string& filePath) { m_filePath = filePath; }//设置文件路径
    bool getMap(std::unordered_map<std::string,std::string> & map,const std::string & language);
public:
    // 通过 LocalizationStringModuleAbstract 继承
    std::string localString(const std::string& id, const std::string & language) override;

    bool localString(std::string& target, const std::string& id, const std::string& language) override;

    bool storeLocalString(const std::string& id, const std::string& language, const std::string& src) override;
   
    bool loadFile()override;

    // 通过 LocalizationStringModuleAbstract 继承
    bool saveFile() override;

    // 通过 LocalizationStringModuleAbstract 继承
    bool changeLocalString(const std::string& id, const std::string& language, const std::string& src) override;
};

```

如上所示`LocalizationStringXML`的类定义。

> 如何正确使用`ConfigurationLoaderXML`？

- 在功能接口前去报设定了XML数据文件的路径
- 在前者的前提下使用`loadFile()`接口加载了数据文件
- 在更改了数据时，只会保存到内存中，要使数据的更改保存到数据文件中请使用接口`saveFile()`

> 如何了解接口的具体作用？

由于个人开发精力有限，暂时还未补充每一个接口的介绍。
但是通过接口的函数名字，可以较容易看出每一个接口的作用。

目前XML数据格式时限定的，格式如下：
```xml
<?xml version="1.0"?>
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
	<string id="4">
		<language language="CHN">自动登录</language>
		<language language="USA">automatic logon</language>
	</string>
	<string id="5">
		<language language="CHN">账户</language>
		<language language="USA">account</language>
	</string>
	<string id="6">
		<language language="CHN">密码</language>
		<language language="USA">password</language>
	</string>
```
在使用数据时一定要确保含有节点`<MyLocalizationStringModele_strings>`。这样能确保加载函数的正确读取。

# 如何进行新的实现

通过继承抽象基类`LocalizationStringModuleAbstract`然后按照满足其[接口标准](# LocalizationStringModuleAbstract抽象基类的介绍)即可，见链接中的接口标准内容。