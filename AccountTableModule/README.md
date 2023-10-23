# AccountTableModule 

------

# 目录

- [简介](#简介)
- [项目配置](#项目配置)

# 简介

这是一个账户存储模块，提供了账户信息的存储功能。此模块包含CRUD的基本操作，为账户保存的具体的实现提供了一致的对外接口。

# 项目配置

## 常规

> 所有配置-所有平台

- 输出目录：$(ProjectDir)\bin\$(Platform)\$(Configuration)\
- 中间目录：$(ProjectDir)\build\$(Platform)\$(Configuration)\

## c/c++

> 所有配置-所有平台

- 附加包含目录：$(ProjectDir)\include\achieve;$(ProjectDir)\include\Test;$(ProjectDir)\include\Abstract;%(AdditionalIncludeDirectories)
