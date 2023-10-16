# LocalizationStringModule 模块

---------

# 目录

- [简介](#简介)
- [设计说明](#设计说明)
- [抽象基类接口说明](#抽象基类接口说明)
- [如何实现新的LocalizationStringModule（子类）](#如何实现新的LocalizationStringModule（子类）)
- [项目配置](#项目配置)

# 简介

LocalizationStringModule 模块使用与软件中所使用的字符串的本地化管理，通过设定的字符串标识符（字符串的唯一id）来管理一个字符串集合（包含多国语言的字符串集合）。这样避免了在软件中硬编码字符串，只需要设定相关的配置文件就可快速更改软件显示的字符串。本模块应该专注于读取存储于字符串集数据库中的所需字符串（用于软件显示）以及写入新的字符串（用于本地化工具当中写入新的翻译）这一功能。

# 设计说明

通过抽象基类`LocalizationStringModuleAbstract`定义了类体系的接口标准，然后子类实现不同的本地化字符串的管理模块。

# 抽象基类接口说明

- `virtual std::string localString(const std::string & id,const std::string & local="CHN") = 0`:这个接口根据id和local来查询对应的本地化字符串，若查询到了应该返回一个string若没有查询到则返回空的string这个接口应该由`virtual bool localString(std::string & target ,const std::string & id,const std::string & local="CHN")=0`实现
- `virtual bool localString(std::string & target ,const std::string & id,const std::string & local="CHN")=0`:这个接口根据id，local查询对应的本地化字符串，若查询到了将其赋值给target并返回`true`，若没有查询到则返回`false`，且target不应该改变。
- `virtual bool storeLocalString(const std::string & id, const std::string& language,const std::string & src) = 0`:保存本地化字符串，形参对应id（字符串id），language（存储的语言），src（存储的字符串），在找不到对应节点的情况下保存，并且返回`true`，如果已有对应节点则返回`false`
- `virtual bool changeLocalString(const std::string& id, const std::string& language, const std::string& src)=0`:更改本地化字符串，形参对应id（字符串id），language（存储的语言），src（要更改为的字符串）在找到对应节点的情况下更改，并且返回`true`，如果没有对应节点则返回`false`
- `virtual bool saveFile() = 0`:保存所有更改的数据到文件中如果保存成功返回`true`,如果保存失败返回`false`
- `virtual bool loadFile()=0`:这个接口用于加载数据文件，如果加载成功返回`true`,如果加载失败返回`false`

# 如何实现新的LocalizationStringModule（子类）

通过继承`LocalizationStringModuleAbstract`抽象基类，满足其对应的接口标准即可写新的实现。

> 新的实现的头文件名应该为LocalizationStringModule-XXX.h，类名为LocalizationStringXXX，XXX为分类名，宏定义为LOCALIZATIONSTRINGMODULE_XXX_H_，XXX为具体的分类名。

# 项目配置

## 常规 

> 所有配置-所有属性

- 输出目录：$(ProjectDir)\bin\$(Platform)\$(Configuration)\
- 中间目录：$(ProjectDir)\build\$(Platform)\$(Configuration)\

## c/c++

> 所有配置-所有属性

- 附加包含目录：$(ProjectDir)\include;%(AdditionalIncludeDirectories)
