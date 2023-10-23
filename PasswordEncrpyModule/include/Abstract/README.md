# PasswordEncrpyModuleAbstract

# 目录

- [简介](#简介)
- [PasswordEncrpyModuleAbstract简介](#PasswordEncrpyModuleAbstract简介)
- [NameDefineForPEMA](#NameDefineForPEMA)

# 简介
PasswordEncrpyModuleAbstract是PasswordEncrpyModule类族的抽象基类，定义了统一的接口标准。

# PasswordEncrpyModuleAbstract简介

PasswordEncrpyModuleAbstract定义如下：

```cpp
class PasswordEncrpyModuleAbstract {
public:
    AccountInfo encrpyForUser(AccountInfo & accountInfo);
    virtual AccountInfo  encrpyForSave(const AccountInfo& accountInfo)=0;
    virtual AccountInfo decrptForUser(const AccountInfo& accountInfo)=0;
protected:
    virtual void encrpy_PasswordLength(AccountInfo& accountInfo)=0;
    virtual void encrpy_haveSpecialSymbols(AccountInfo& accountInfo)=0;
    virtual void encrpy_haveUppercaseLowercase(AccountInfo& accountInfo)=0;
    virtual void encrpy_EncrpyIsIrreversible(AccountInfo& accountInfo)=0;

};
```
其中接口`AccountInfo encrpyForUser(AccountInfo & accountInfo)`：是一个模板算法。其定义如下：
```cpp
AccountInfo PasswordEncrpyModuleAbstract::encrpyForUser(AccountInfo& accountInfo)
{
    encrpy_haveSpecialSymbols(accountInfo);
    encrpy_haveUppercaseLowercase(accountInfo);
    encrpy_EncrpyIsIrreversible(accountInfo);
    encrpy_PasswordLength(accountInfo);

    return accountInfo;
}   
```
- `virtual AccountInfo  encrpyForSave(const AccountInfo& accountInfo)=0;`:将密码加密（提供给保存的模块，这个加密应该为可逆）
- `virtual AccountInfo decrptForUser(const AccountInfo& accountInfo)=0;`
将密码解密（提供给保存的模块，这个加密应该为可逆）

# NameDefineForPEMA

类内统一了数据类型别名。方便后期更改底层数据实现。

```cpp
using PEMAstring = ATMAstring;
using PEMAint = ATMAint;
using PEMAbool = ATMAbool;
using PEMApair = ATMApair;
```
