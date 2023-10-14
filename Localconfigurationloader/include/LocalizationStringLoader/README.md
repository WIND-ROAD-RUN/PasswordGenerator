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

# 如何进行新的实现

通过继承抽象基类`ConfigurationLoaderAbstract`然后按照满足其[接口标准](# ConfigurationLoaderAbstract抽象基类的介绍)即可，见链接中的接口标准内容。