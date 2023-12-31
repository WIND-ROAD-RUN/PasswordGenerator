# LocalizationStringManager
-------------
# 目录

- [项目简介](#项目简介)
- [项目功能](#项目功能)
- [使用事项](#使用事项)
- [项目配置](#项目配置)

# 项目简介
项目LocalizationStringManager是一个基于LocalizationStringModule模块的可视化本地化字符串（XML资源文件）的一个微型管理器，注意使用该项目，依赖于LocalizationStringModule模块。在拷贝这个项目的时候，务必添加依赖项，或者将LocalizationStringModule模块的源代码添加到这个项目中

# 项目功能
这是一个微型管理器，目前只提供了查询以及存储的功能。对于某一个结点的更改的功能暂时还没有实现。

> 这只是一个方便开发的小工具，只满足了最常用的功能方便开发而已，若有其他需求后期可能会添加

> 如何进行查询？

在查询可视化板块，输入要查询的字符串标识符（唯一id，可以使用哈希表进行生成，具体的算法还未实现，目前采用自命名的方式）同时选择对应的国家语言或者地区（目前由CHN中国和USA美国，其他国家个性化添加的功能还未实现）,点击查询按钮即可完成操作,若没有对应信息会弹出对话框提示没有该信息条目.

> 如何进行存储?

在存储可视化板块,输入要查询的字符串标识符（唯一id，可以使用哈希表进行生成，具体的算法还未实现，目前采用自命名的方式）同时选择对应的国家语言或者地区（目前由CHN中国和USA美国，其他国家个性化添加的功能还未实现）,点击存储按钮即可完成操作,若已经有了对应的信息会弹出对话框提示已有对应条目的信息,存储失败.

> 如何进行保存

在存储模块进行的操作只会保存到内存中,点击保存后才会保存到数据文件中,在退出窗口的时候也会有对话框提醒是否要保存并退出.


# 使用事项

> 注意!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
> 如何更改字符串节点信息

由于这个功能在目前的开发流程中,并不常用.现在给出更改方法.
找出对应的XML数据文件,然后将需要更改的字符串节点删除,然后保存文件在打开本管理器进行存储操作,避免编码问题产生的影响.

> 再次提醒,更改字符串的时候一定要使用管理器的存储功能,这保证了所使用的编码一致,避免中文乱码的问题,切勿直接在数据文件中更改.

# 项目配置

## 常规

> 所有配置-所有平台

- 输出目录：`$(ProjectDir)\bin\$(Platform)\$(Configuration)\`
- 中间目录: `$(ProjectDir)\build\$(Platform)\$(Configuration)\`

## c/c++

- 附加包含目录：`$(SolutionDir)\LocalizationStringModule\include;$(ProjectDir)\include;%(AdditionalIncludeDirectories)`

## 链接器

- 附加包含目录:`$(SolutionDir)\LocalizationStringModule\build\x64\Debug;%(AdditionalLibraryDirectories)`
- 输入-附加依赖项：`LocalizationStringModule-XML.obj;%(AdditionalDependencies)`
