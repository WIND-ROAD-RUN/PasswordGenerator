# MyLoginWindow

 这是一个登录窗口的项目其中完成了基本的互动界面（还未做美化）目前拥有良好的设计模式,  对于登录以及注册有着抽象的接口，后期替换为数据库操作更为方便 

-----------------------------------------


# 目录
- [项目的功能模块](#项目的功能模块)
   - [登录](#登录)
      - [LoginAbstract 类](#LoginAbstract-类)
      - [Login 类](#Login-类)
   - [注册](#注册)
      - [RegistAbstract 类](#RegistAbstract-类)
      - [Regist 类](#Regist-类)
- [项目业务逻辑的实现](# 项目业务逻辑的实现)
   - [AccountStoreTranmist 类 ](#AccountStoreTranmist-类 )
   - [AccountStoreAbstract 类](#AccountStoreAbstract-类)
      - [AccountStoreSaveInTxt 类](#AccountStoreSaveInTxt-类)


-------------------------------------------

# 项目的功能模块

## 登录

### LoginAbstract 类

登录功能的实现首先由虚基类`LoginAbstract`定义了登录接口，该基类使用了模板模式，每一个子类都实现了不同的登录算法。其中`LoginAbstract`的类定义如下：
``` cpp
class LoginAbstract {
private:
    std::string m_account;
    std::string m_password;
private:
    virtual bool check_Account() = 0;
public:
    LoginAbstract(const std::string& account, const std::string& password)
        : m_account(account), m_password(password) {}
    ~LoginAbstract() {}
public:
    bool login();
    void setAccount(const std::string& account, const std::string& password);
    void set_account(const std::string& account) { m_account = account; }
    void set_password(const std::string& password) { m_password = password; }
    std::string account() const { return m_account; }
    std::string password() const { return m_password; }
};
```
每一个子类只需要覆写`check_Account()`，然后通过`login()`函数即可实现登录功能。
>注意：在使用`login()`之前一定要使用`setAccount()`或是`set_account`和`set_password`设置类中的`m_account`和`m_password`以确保使用正确账户和密码进行登录操作。


>注意：本手册均省略函数参数，在必要时会写上函数参数。

### Login 类

`LoginAbstract`类的一个子类`Login`覆写的虚函数`check_Account()`由 类`accountStoreTranmist`实现检查密码的操作。其类定义，以及覆写函数代码如下。

```cpp
class AccountStoreTranmsit;
class Login :public LoginAbstract {
private:
    AccountStoreTranmsit* m_accountStoreTranmsit;
public:
    Login(const std::string& account, const std::string& password);
    ~Login();

    // 通过 loginAbstract 继承
    bool check_Account() override;
};
```
```cpp
bool Login::check_Account()
{
    if (m_accountStoreTranmsit->checkPassword(account(), password())
        ==AccountStoreTranmsit::AccountStoreTranmsitResult::RightPassword) {
        return true; 
    }
    else { 
        return false; 
    }
}
```

>要查看`AccountStoreTranmist`的类定义请[跳转](#AccountStoreTranmist-类)。

## 注册

### RegistAbstract 类

登录功能的实现首先由虚基类`RegistAbstract`定义了注册接口，该基类使用了模板模式，每一个子类都实现了不同的登录算法。其中`RegistAbstract`的类定义如下：

``` cpp
class RegistAbstract {
private:
    std::string m_account;
    std::string m_password;
public:
    RegistAbstract(const std::string & account,const std::string & password)
        :m_account(account),m_password(password) {}
    ~RegistAbstract() {}
private:
    virtual std::string encrpt(const std::string & password);
    virtual bool have_account_if() = 0;
    virtual bool save_account() = 0;
public:
    bool regist();
    void setAccount(const std::string& account, const std::string& password);
    void set_account(const std::string& account) { m_account = account; }
    void set_password(const std::string& password) { m_password = password; }
    std::string account() const { return m_account; }
    std::string password() const { return m_password; }

};
```

`RegistAbstract`类中模板算法为`regist()`用于注册账户以及密码。其中`regist()`的定义如下：
```cpp
bool RegistAbstract::regist()
{
    if (have_account_if()) { return false; }
    std::string encPassword = encrpt(m_password);
    if (save_account()) { return true; }
    else { return false; }
}
```
先通过`have_account_if()`检查存储的账户中是否含有要存储的账户数据，如果有那么返回`false`,否则通过`encrpt()`对要存储的密码进行加密。然后通过`save_account()`进行加密。最后通过`save_account()`存储数据。

>注意：子类应该要必须要复写`virtual bool have_account_if() = 0`和`virtual bool save_account() = 0`。`virtual std::string encrpt(const std::string & password)`为可选，如果不进行复写该函数将返回原值。

### Regist 类
`Regist`是`RegistAbstract`类的一个子类，它覆写了`have_account_if`和`save_account()`。其中类定义以及覆写函数定义如下:

```cpp
/*类定义*/
class AccountStoreTranmsit;

class Regist :public RegistAbstract{
private:
    AccountStoreTranmsit* m_accountStoreTranmsit;
    bool have_account_if() override;
    bool save_account() override;
public:
    Regist(const std::string& account, const std::string& password);
    ~Regist();
    // 通过 RegistAbstract 继承
};

/*覆写函数的定义*/
bool Regist::have_account_if()
{
    if (m_accountStoreTranmsit->searchAccount(account())) { return true; }
    else { return false; }
}

bool Regist::save_account()
{
    if (m_accountStoreTranmsit->saveAccountInfo(account(), password())
        ==AccountStoreTranmsit::AccountStoreTranmsitResult::SavedAccountSucceed) 
    { 
        return true; 
    }
    else
    {
        return false; 
    }
}
```

>该子类的加密函数`encrpt()` 还未覆写。后续将添加加密功能。
--------------------------------------------------------

# 项目业务逻辑的实现

## AccountStoreTranmist 类 

`AccountStoreTranmist`类作为账户存储功能的各类的转发。其中定义了账户各类的操作。将账户实际的访问过程抽象了出来。其类定义如下：
``` cpp
class AccountStoreAbstract;

class AccountStoreTranmsit {
private:
    AccountStoreAbstract* m_accountStoreAbstract;
public:
    enum AccountStoreTranmsitResult {
        EmptyAccount = 0, ExistingAccount = 1,
        ErrorPassword = 2, RightPassword = 4,
        SavedAccountFailed = 5, SavedAccountSucceed = 6
    };
    AccountStoreTranmsit();
    ~AccountStoreTranmsit();
    AccountStoreTranmsitResult searchAccount(const std::string& account);
    AccountStoreTranmsitResult checkPassword(const std::string& account, const std::string& password);
    AccountStoreTranmsitResult saveAccountInfo(const std::string& account, const std::string& password);
};
};
```
其接口的作用通过其接口名字可以显而看出。

注意检测接口的返回值一定要是使用枚举变量 `AccountStoreTranmsitResult`其中各个枚举量的含义如下：
- `EmptyAccount` 查询时如果没有提供的用户名返回此枚举量
- `ExistingAccount` 查询时如果有提供的用户名返回此枚举量
- `ErrorPassword` 对比密码的时候如果与存储的密码不一致返回此枚举量
- `RightPassword` 对比密码的时候如果与存储的密码一致返回此枚举量
- `SavedAccountFailed` 保存密码的时候如果保存失败返回此枚举量
- `SavedAccountSucceed` 保存密码的时候如果保存成功返回此枚举量

>其中内置了`AccountStoreAbstract`指针，这是账户继承体系的抽象基类，定义了账户存储的的基本接口。

>要查看`AccountStoreAbstract`的类定义请[跳转](#AccountStoreAbstract-类)。

对该类实行的重构操作：

- [x] 定义了良好的接口
- [x] 规定了返回值的枚举变量
- [x] 定义为模板模式，将其提升为抽象基类 

## AccountStoreAbstract 类

`AccountStoreAbstract` 定义了账户存储的基本接口，他规范了继承体系中的各个存储算法的接口标准。其定义如下：

``` cpp
class AccountStoreAbstract {
protected:
    struct Account {
        std::string account;
        std::string password;
    };
public:
    AccountStoreAbstract() {}
    ~AccountStoreAbstract() {}
public:
    virtual void ini_accountTable() = 0;
    virtual void clear_registTable()=0;
    virtual bool search_account(const std::string& account) = 0;
    virtual void save_account(const std::string& account, const std::string& password)=0;
    virtual bool save_account_exceptExist(const std::string& account, const std::string& password)=0;
    virtual bool check_password(const std::string& account, const std::string& password)=0;
};
```
在`AccountStoreAbstract`中先规范了读取时以及保存前的数据在内存中的数据结构`Account`，它将作为程序的数据条目作为程序的中间数据结构。

下面介绍各个接口的作用：

- `ini_accountTable()`:用于在使用账户数据存储的时候将数据初始化进你所保存的数据结构中。例如在`AccountStoreSaveInTxt`中的`std::vector<Account> m_accountTable;`类内成员。在写`AccountStoreAvstract`的子类时必须实现该算法。
-  `clear_registTable()`:用于清除你所在子类中定义存储数据的类内成员。例如清除`AccountStoreSaveInTxt`中的`std::vector<Account> m_accountTable;`类内成员。
-  `search_account(const std::string& account)`: 传入一个`std::string`变量用于查找是否含有同值数据。查询结果应该返回`bool`变量
-  `save_account(const std::string& account, const std::string& password)`:用于保存数据条目。注意：应该将数据同时保存在类内成员和实际的数据存储中。
-  `save_account_exceptExist(const std::string& account, const std::string& password)`:该接口在存储前先检查是否含有同名成员，这个接口的实现应该基于`save_account(const std::string& account, const std::string& password)`（调用这个接口）
-  `check_password(const std::string& account, const std::string& password)` :该接口用于检查传入的`account`与`password`与存储的账户的密码是否对应。

>要使用新的存储账户或是访问存储的账户的方式请直接公有继承`AccountStoreAbstract`类。

> 这个继承体系原则上不应该对密码进行加密，加密功能应由上层类实现，本继承体系只负责存储以及访问功能，或者说只负责存储或是查询加密之后的数据形式。要查阅加密的类请[跳转](#RegistAbstract-类)。

### AccountStoreSaveInTxt 类

`AccountStoreSaveInTxt`类公有继承了`AccountStoreAbstract`抽象基类的接口。`AccountStoreSaveInTxt`类以纯文本的方式存储账户以及密码。定义如下:
``` cpp

/*实现为单例类*/
class AccountStoreSaveInTxt:public AccountStoreAbstract {
private:
    static AccountStoreSaveInTxt* my_instance;
    AccountStoreSaveInTxt() {}
public:
    static AccountStoreSaveInTxt* getInstance() {
        if (!my_instance) {
            my_instance = new AccountStoreSaveInTxt();
            my_instance->ini_accountTable();
        }
        return my_instance;
    }
    ~AccountStoreSaveInTxt() { delete my_instance; }
private:
    std::vector<Account> m_accountTable;
    std::string m_fileName{ "E:\\game_project\\GameMake\\password.txt" };
public:
    // 通过 AccountStoreAbstract 继承
    void ini_accountTable() override;
    void clear_registTable() override;
    bool search_account(const std::string& account) override;
    void save_account(const std::string& account, const std::string& password) override;
    bool save_account_exceptExist(const std::string& account, const std::string& password) override;
    bool check_password(const std::string& account, const std::string& password) override;
};
```

该类实现账户存储访问操作的实现逻辑：将账户以及密码依次存储到txt文件中，例如将账户名account密码为password的账户存储到文件中。在文件中它的存储布局如下：
```txt文件中
account
password
```
账户名和密码分行存储，同时读取时也是一行一行的读取。读取账户数据使用接口`ini_file()()`，使用类`AccountStoreSaveInTxt`需要注意在使用前先使用该函数进行读取操作。它会将数据以中间数据`Account`的数据存储到类内成员`m_accountTable`中。

该类使用了单例模式，有且只能存在一个实例，通过调用静态函数`AccountStoreSaveInTxt::getInstance()`获取一个该类一个实例的指针。具体实现参阅.cpp文件。

对该类实行的重构操作：

- [x] 实现为单例模式，只能存在这一个类实例，防止造成多个类实例，账户表单不一致的情况
- [ ] 避免实现为硬编码的txt账户本的存储路径


--------------------------------------------------------







