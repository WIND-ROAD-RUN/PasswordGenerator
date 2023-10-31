#ifndef LOGIN_H_
#define LOGIN_H_

#include"loginAbstract.h"

#include<String>


class AccountStoreTranmsit;
class Login :public LoginAbstract {
private:
    AccountStoreTranmsit* m_accountStoreTranmsit;

public:
    Login(const std::string& account, const std::string& password);

    ~Login();
private:
    std::string sha256(const std::string& data);
public:
    // 通过 loginAbstract 继承
    bool check_Account() override;

    // 通过 LoginAbstract 继承
    std::string encrpy(const std::string& password) override;
};


#endif // !LOGIN_H_
