# 项目配置

里面包含了本地配置加载器的实现具体实现在include分级目录下

# 常规

> 所有配置 & 所有平台

- 输出目录：`$(ProjectDir)\bin\$(Platform)\$(Configuration)\`
- 中间目录:  `$(ProjectDir)\build\$(Platform)\$(Configuration)\`

# c/c++

## 常规

> 所有配置 & 所有平台

- 附加包含目录：`$(solutionDir)\LocalizationStringModule\include;$(ProjectDir)\include\ConfigurationLoader;$(ProjectDir)\include\LocalizationStringLoader;%(AdditionalIncludeDirectories)`

# 链接器

- 附加库目录：`$(SolutionDir)\LocalizationStringModule\build\x64\Debug`
- 输入-附加依赖项：`LocalizationStringModule-XML.obj`