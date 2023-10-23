# AccountTableXML

## 目录
- [简介](#简介)
- [注意事项](#注意事项)
## 简介
AccountTableXML作为AccountTable类族中的一个成员，继承自`AccountTableAbstract`.这个实现基于第三方库pugixml。
## 注意事项
在抽象基类的基础上添加了以下成员。
```cpp
pugi::xml_document m_doc;
ATMAstring m_filePath{};
ATMAstring m_UID{};

void setFilePath(const std::string& filePath) { m_filePath = filePath; }
void setUID(const std::string& UID) { m_UID = UID; }

ErrorAccountTableModule findPlatformNode(const ATMAstring & platform,pugi::xml_node & platformNode);
ErrorAccountTableModule findAccountNode(const ATMAstring & platform,const ATMAstring & account, pugi::xml_node& accountNode);
ErrorAccountTableModule findPlatformNode(const ATMAstring& platform);
ErrorAccountTableModule findAccountNode(const ATMAstring& platform, const ATMAstring& account);
```
在使用这个实现之前确保成员`m_filePath`和`m_UID`被赋予了值（可以通过接口赋值）。田间的find开头的接口，为提高复用性而添加。可以使用，但其他接口不确保一定实现了这些接口。