# AccountTableModuleAbstract 抽象基类

## 目录

- [简介](#简介)
- [AccountTableModuleAbstract](#AccountTableModuleAbstract)
- [NameDefineForATMA](#NameDefineForATMA)

## 简介

这是`AccountTableModuleAbstract`类族的抽象基类，定义了必须满足的接口，该类族完成了账户信息存储的功能。

## AccountTableModuleAbstract

`AccountTableModuleAbstract`抽象基类的定义如下：

```cpp
class AccountTableModuleAbstract {
public:
    virtual ErrorAccountTableModule
        NewAccountTable(const ATMAstring& fileName) = 0;

    virtual ErrorAccountTableModule
        NewPlatform(const ATMAstring& platform) = 0;

    virtual ErrorAccountTableModule
        ini_module()=0;//初始化模块
    virtual ErrorAccountTableModule
        save() = 0;
public:
    /*新增节点*/
    virtual ErrorAccountTableModule 
        NewAccount(const ATMAstring& platform, const ATMAstring& account) = 0;

    virtual ErrorAccountTableModule
        NewAccount(const ATMAstring& platform, const AccountInfo& account) = 0;

    /*设置节点信息*/
    virtual ErrorAccountTableModule
        setAccount(const ATMAstring& platform, const AccountInfo& account) = 0;

    virtual ErrorAccountTableModule 
        setAccount(const ATMAstring& platform, const ATMAstring& orginalAccount,const ATMAstring & newAccount)=0;

    virtual ErrorAccountTableModule 
        setPassword(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& password)=0;

    virtual ErrorAccountTableModule 
        setPhoneNumber(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& phoneNumber)=0;

    virtual ErrorAccountTableModule 
        setUser(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& user)=0;


    virtual ErrorAccountTableModule 
        setPasswordLength(const ATMAstring& platform, const ATMAstring& account, ATMAint minimum, ATMAint maximum)=0;

    virtual ErrorAccountTableModule 
        sethaveSpecialSymbols(const ATMAstring& platform, const ATMAstring& account, ATMAbool haveSpecialSymbols)=0;

    virtual ErrorAccountTableModule 
        sethaveUppercaseLowercase(const ATMAstring& platform, const ATMAstring& account, ATMAbool haveUppercaseLowercase)=0;

    virtual ErrorAccountTableModule 
        setEncrpyIsIrreversible(const ATMAstring& platform, const ATMAstring& account, ATMAbool EncrpyIsIrreversible)=0;
    
    /*删除节点信息*/
    virtual ErrorAccountTableModule
        deletePlatform(const ATMAstring & platform)=0;
    virtual ErrorAccountTableModule
        deleteAccount(const ATMAstring & platform,const ATMAstring & account) = 0;
    /*返回节点信息*/
    virtual AccountInfo
        Account(const ATMAstring& platform, const ATMAstring& account) = 0;
    
    virtual ATMAstring
        Password(const ATMAstring& platform, const ATMAstring& account) = 0;

    virtual ATMAstring
        PhoneNumber(const ATMAstring& platform, const ATMAstring& account) = 0;

    virtual ATMAstring
        User(const ATMAstring& platform, const ATMAstring& account) = 0;

    virtual ATMApair
        PasswordLength(const ATMAstring& platform, const ATMAstring& account) = 0;

    virtual ATMAbool
        haveSpecialSymbols(const ATMAstring& platform, const ATMAstring& account) = 0;

    virtual ATMAbool
        haveUppercaseLowercase(const ATMAstring& platform, const ATMAstring& account) = 0;

    virtual ATMAbool
        EncrpyIsIrreversible(const ATMAstring& platform, const ATMAstring& account) = 0;
    virtual ATMAStringList
        getPlatformList()=0;
    virtual ATMAAccountList
        getAccountList(const ATMAstring& platform) = 0;
};
```
> 如何正确的实现子类

- 使用`ini_module()`接口对模块进行初始化，同时在确保返回值为`ErrorAccountTableModule：：NO_ERROR`的时候数据加载成功
- 使用`save()`保存数据，同时在确保返回值为`ErrorAccountTableModule：：NO_ERROR`的时候保存数据成功；

### 各个接口的含义

- ` virtual ErrorAccountTableModuleNewAccountTable(const ATMAstring& fileName) = 0;` : 在文件没有根节点的时候应该使用这个函数添加一个根节点。
- `virtual ErrorAccountTableModuleNewPlatform(const ATMAstring& platform) = 0;`:添加一个新的平台节点。
- `virtual ErrorAccountTableModuleini_module()=0;`：初始化模块（加载数据文件到内存中）

> 新增节点

- `virtual ErrorAccountTableModule NewAccount(const ATMAstring& platform, const ATMAstring& account) = 0;`:新增一个账户节点，并将账户节点下的所有节点设为空值。
- `virtual ErrorAccountTableModuleNewAccount(const ATMAstring& platform, const AccountInfo& account) = 0;`:通过形参`account`的信息新增一个账户节点，并将内容设置与`account`同值。

> 设置节点信息 

- `virtual ErrorAccountTableModulesetAccount(const ATMAstring& platform, const AccountInfo& account) = 0;`:根据形参`account`设置对应节点的信息，在没有这个节点的情况下应该返回正确的枚举值，这个接口设置account除账户名以外的数据成员。
- `virtual ErrorAccountTableModule setAccount(const ATMAstring& platform, const ATMAstring& orginalAccount,const ATMAstring & newAccount)=0;`：这个接口设置account节点的账户名，在没有这个节点的情况下应该返回正确的枚举值。
- `virtual ErrorAccountTableModule setPassword(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& password)=0;`：这个接口设置account节点的密码，在没有这个节点的情况下应该返回正确的枚举值。
- `virtual ErrorAccountTableModule setPhoneNumber(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& phoneNumber)=0;`：这个接口设置account节点的电话号码，在没有这个节点的情况下应该返回正确的枚举值。
- `virtual ErrorAccountTableModule setUser(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& user)=0;`:这个接口设置account节点的使用者信息，在没有这个节点的情况下应该返回正确的枚举值。
- `virtual ErrorAccountTableModule setPasswordLength(const ATMAstring& platform, const ATMAstring& account, ATMAint minimum, ATMAint maximum)=0;`:这个接口设置account节点的密码的长度（最大值以及最小值），在没有这个节点的情况下应该返回正确的枚举值。
- `virtual ErrorAccountTableModule sethaveSpecialSymbols(const ATMAstring& platform, const ATMAstring& account, ATMAbool haveSpecialSymbols)=0;`:这个接口设置account节点的是否含有特殊符号，在没有这个节点的情况下应该返回正确的枚举值。
- `virtual ErrorAccountTableModule sethaveUppercaseLowercase(const ATMAstring& platform, const ATMAstring& account, ATMAbool haveUppercaseLowercase)=0;`:这个接口设置account节点的是否含有大小写，在没有这个节点的情况下应该返回正确的枚举值。
- `virtual ErrorAccountTableModule setEncrpyIsIrreversible(const ATMAstring& platform, const ATMAstring& account, ATMAbool EncrpyIsIrreversible)=0;`:这个接口设置account节点的是否是不可逆加密，在没有这个节点的情况下应该返回正确的枚举值。

> 删除节点信息

- `virtual ErrorAccountTableModule deletePlatform(const ATMAstring & platform)=0;`：删除对应平台的节点，同时其下的所有账户节点也全部删除。
- `virtual ErrorAccountTableModuledeleteAccount(const ATMAstring & platform,const ATMAstring & account) = 0;`：删除对应账户的节点。

> 返回节点信息

- `virtual AccountInfo Account(const ATMAstring& platform, const ATMAstring& account) = 0;`：以`AccountInfo`的数据形式返回对应account节点信息.
- `virtual ATMAstring Password(const ATMAstring& platform, const ATMAstring& account) = 0;`:返回对应account节点的密码。
- `virtual ATMAstringPhoneNumber(const ATMAstring& platform, const ATMAstring& account) = 0;`:返回对应account节点的电话号码。
- `virtual ATMAstring User(const ATMAstring& platform, const ATMAstring& account) = 0;`:返回对应account节点的使用者信息。
- `virtual ATMApair PasswordLength(const ATMAstring& platform, const ATMAstring& account) = 0;`:返回对应account节点密码长度。
- `virtual ATMAbool haveSpecialSymbols(const ATMAstring& platform, const ATMAstring& account) = 0;`:返回对应节点是否含有特殊符号。
- `virtual ATMAboolhaveUppercaseLowercase(const ATMAstring& platform, const ATMAstring& account) = 0;`:返回对应节点是否含有大小写。
- `virtual ATMAbool EncrpyIsIrreversible(const ATMAstring& platform, const ATMAstring& account) = 0;`:返回对应节点是否是不可逆加密。
-  `virtual ATMAStringList getPlatformList()=0;`:返回所有的平台名（应该返回一个list）。
-  `virtual ATMAAccountList getAccountList(const ATMAstring& platform) = 0;`:返回对应平台下的所有账户节点（应该返回一个list）

## NameDefineForATMA

### AccountInfo

Account 作为模块传出账户节点信息的中间数据结构。对数据进行了简单的封装。其定义如下：

```cpp
struct AccountInfo {
    ATMAstring accountName{};
    ATMAstring password{};
    ATMAstring phoneNumber{};
    ATMAstring User{};
    ATMApair passwordLength{};
    ATMAbool haveSpecialSymbols{false};
    ATMAbool haveUppercaseLowercase{ false };
    ATMAbool EncrpyIsIrreversible{ false };
};
```
其成员值的作用显而易见。

### 变量别名

```cpp
using ATMAstring = std::string;
using ATMAint = int;
using ATMAbool = bool;
using ATMApair = std::pair<ATMAint, ATMAint>;
using ATMAStringList = std::vector<std::string>;
using ATMAAccountList = std::vector<AccountInfo>;
using PATmap = std::unordered_map<ATMAstring, ATMAAccountList>;
```
在模块内使用同一的变量别名，便于以后更改底层数据实现。

### ErrorAccountTableModule 枚举变量

作为模块内大部分接口的返回值，其枚举变量标识了每一种错误类型，方便调试以及测试的工作，提高代码可读性。

定义如下：
```cpp
enum ErrorAccountTableModule
{
    No_ERROR = 1,					//没有错误返回
    NewAccount_ERROR,				//新建账户错误
    NewPassword_ERROR,				//新建密码错误
    NewPhoneNumber_ERROR,			//新建手机号错误
    NewUser_ERROR,					//新建使用者错误
    NewEncrpyProperty_ERROR,		//新建加密属性错误
    NewPasswordLength_ERROR,		//新建密码长度错误
    NewhaveSpecialSymbols_ERROR,	//新建是否含有特殊符号错误
    NewhaveUppercaseLowercase_ERROR,//新建是否含有大小写错误
    NewEncrpyIsIrreversible_ERROR,	//新建是否为可逆加密错误
    setAccount_ERROR,				//设置用户名错误
    setPassword_ERROR,				//设置密码错误
    setPhoneNumber_ERROR,			//设置电话号码错误
    setUser_ERROR,					//设置用户名错误
    setEncrpyProperty_ERROR,		//设置加密属性错误
    setPasswordLength_ERROR,		//设置密码长度错误
    sethaveSpecialSymbols_ERROR,	//设置是否含有特殊符号错误
    sethaveUppercaseLowercase_ERROR,//设置是否含有大小写错误
    setEncrpyIsIrreversible_ERROR,	//设置是否为可逆加密错误
    NewPlatform_ERROR,				//新建平台节点错误
    NewAccountTable_ERROR,			//新建根节点错误
    Initialization_ERROR,			//初始化错误
    SaveData_ERROR,					//保存数据错误
    PlatformAlreadyExist,			//平台已经存在
    AccountAlreadyExist,			//账户已经存在
    NoPlatformNode,					//没有该平台节点
    NoAccountNode,					//没有该用户节点
    NoAccounTable,					//没有根节点
    deletePlatform_ERROR,			//删除平台节点错误
    deleteAccount_ERROR				//删除用户节点错误
};
```