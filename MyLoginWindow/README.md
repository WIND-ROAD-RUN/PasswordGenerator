# MyLoginWindow

 这是一个登录窗口的项目其中完成了基本的互动界面（还未做美化）目前拥有良好的设计模式,  对于登录以及注册有着抽象的接口，后期替换为数据库操作更为方便 

-----------------------------------------


# 目录
- [项目的功能模块](#项目的功能模块)
   - [登录](#登录)
   - [注册](#注册)
- [ 项目的类层次](# 项目的类层次)
   - [界面层次类](#界面层次类)
      - [LoginWindow 类](#LoginWindow-类)
      - [DialogRegist 类](#DialogRegist-类)
      - [AccountStoreTranmist 类](#AccountStoreTranmist-类)
      - [LoginTranmist 类](#LoginTranmist-类)
   - [界面逻辑功能实现类](#界面逻辑功能实现类)
      -[AccountStore 类](#AccountStore-类)
      -[LoginAbstract 类](#LoginAbstract-类)
      -[Login 类](#Login-类)

-------------------------------------------

# 项目的功能模块

## 登录

登录功能的实现首先由虚基类`LoginAbstract`定义了登录接口，该基类使用了模板模式，每一个子类都实现了不同的登录算法。其中`LoginAbstract`的类定义如下：
``` cpp
class LoginAbstract {
private:
    std::string m_account;
    std::string m_password;
public:
    LoginAbstract(const std::string& account, const std::string& password)
        : m_account(account), m_password(password) {}
    ~LoginAbstract() {}
public:
    virtual bool login();
    virtual bool check_Account() = 0;
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

该模板类的一个子类`Login`覆写的虚函数`check_Account()`由 类`accountStoreTranmist`实现检查密码的操作。其代码如下。
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

- [x] 定义了良好的接口
- [x] 纯本机存储文本账号（基于类`accountStore`）
- [ ] 远程存储账户
- [ ] 加密用户密码

## 注册

该区域还未施工使其使用抽象的接口，但完成了基本的功能,直接使用`accountStoreTranmist`类的接口。

--------------------------------------------------------

# 项目业务逻辑的实现

## AccountStoreTranmist 类 

`AccountStoreTranmist`类作为账户存储功能的各类的转发。其中定义了账户各类的操作。将账户实际的访问过程抽象了出来。其类定义如下：
``` cpp
class AccountStore;

class AccountStoreTranmsit {
private:
    AccountStore* m_accountStore;
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
```
其接口的作用通过其接口名字可以显而看出。

>注意检测接口的返回值一定要是使用枚举变量 `AccountStoreTranmsitResult`其中各个枚举量的含义如下：
> - `EmptyAccount` 查询时如果没有提供的用户名返回此枚举量
> - `ExistingAccount` 查询时如果有提供的用户名返回此枚举量
> - `ErrorPassword` 对比密码的时候如果与存储的密码不一致返回此枚举量
> - `RightPassword` 对比密码的时候如果与存储的密码一致返回此枚举量
> - `SavedAccountFailed` 保存密码的时候如果保存失败返回此枚举量
> - `SavedAccountSucceed` 保存密码的时候如果保存成功返回此枚举量

>目前采用了直接内置`AccountStroe * m_accountStore`的方式，后面将会使其施工未模板模式，这样每一个子类都将对应一个实际的账户操作类

对该类实行的重构操作：

- [x] 定义了良好的接口
- [x] 规定了返回值的枚举变量
- [ ] 定义为模板模式，将其提升为抽象基类 

## AccountStore 类

`AccountStore` 以将账户数据存储到本机的password.txt文件中实现了账户的存储访问操作。其类定义如下：
``` cpp
class AccountStore {
private:
    struct Account {
        std::string account;
        std::string password;
    };
    std::string m_fileName{ "G:\\project\\code_place\\vs_code_place\\game_project\\password.txt" };
    std::vector<Account> m_accountTable;
public:
    void ini_file();
    AccountStore() { ini_file(); }
    ~AccountStore() {}
    void clear_registTable();
    bool search_account(const std::string& account);
    void save_account(const std::string & account,const std::string& password);
    bool save_account_exceptExist(const std::string& account, const std::string& password);
    bool check_password(const std::string& account, const std::string& password);
};
```
该类实现账户存储访问操作的实现逻辑：将账户以及密码依次存储到txt文件中，例如将账户名account密码为password的账户存储到文件中。在文件中它的存储布局如下：
```txt文件中
account
password
```
账户名和密码分行存储，同时读取时也是一行一行的读取。读取账户数据使用接口`ini_file()()`，使用类`AccountStore`需要注意在使用前先使用该函数进行读取操作。它会将数据以中间数据`Account`的数据存储到类内成员`m_accountTable`中。

对该类实行的重构操作：

- [ ] 实现为单例模式，只能存在这一个类实例，防止造成多个类实例，账户表单不一致的情况
- [ ] 避免实现为硬编码的txt账户本的存储路径
- [ ] 密码的加密的功能操作

--------------------------------------------------------

# 项目的类层次


## 界面层次类

这些类主要用于实现程序的交互界面逻辑

###	LoginWindow 类

LoginWindow类是登录器的主界面，其中背景图片还未实现

### DialogRegist 类

DialogRegist类是注册界面的实现

### AccountStoreTranmist 类

accountStoreTranmist类作为账户存储查询的转发类，保持稳定的接口提供给DialogRegist类以及LoginWindow类，他由accountStore类作为委托类实现相关功能，后期将会替换accountStore的实现，使得账户数据保存在数据库或是远程服务器上

### LoginTranmist 类

LoginTranmist类作为登录功能的转发类，保持稳定的接口提供给LoginWindow类，他由accountStore类作为委托类实现相关功能，后期将会替换accountStore的实现，使得登录功能实现在数据库或是远程服务器上

---------------------------------------------------------------------------------

## 界面逻辑功能实现类

这些类主要实现界面功能的具体功能，即业务逻辑的实现，目前accountStore还未重构

### AccountStore 类

这个类将账户数据保存在指定目录下，目前采用的是硬编码的方式存于accountStore类定义中，下一次重构将使其实现未单例类，以消除当前类中的各种操作前均要初始化的问题。后期这个类将会被替换

### LoginAbstract 类

这个类使用了模板算法类模式，作为login功能的算法模板，定义了登录的基本流程

### Login 类

这个类继承了LoginAbstract类重新实现了LoginAvstract中的虚函数，其中登录的功能由accountStore类实现，后期将会替换具体实现，采用数据库的技术。



