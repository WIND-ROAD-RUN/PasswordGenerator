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

    // 通过 loginAbstract 继承
    bool check_Account() override;
};


#endif // !LOGIN_H_
