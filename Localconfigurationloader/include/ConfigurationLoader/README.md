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

# 如何进行新的实现

通过继承抽象基类`LocalizationStringLoaderAbstract`然后按照满足其[接口标准](# LocalizationStringLoaderAbstract抽象基类的介绍)即可，见链接中的接口标准内容。