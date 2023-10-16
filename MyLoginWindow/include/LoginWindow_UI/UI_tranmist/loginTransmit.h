#ifndef LOGINTRANSMIT_H_
#define LOGINTRANSMIT_H_

#include<String>
#include"login.h"

class Login;

class LoginTransmit {
private:
    std::string m_account;
    std::string m_password;
    Login* m_login;
public:
    LoginTransmit(const std::string& account, const std::string& password);
    ~LoginTransmit() {};
public:
    bool isLoginSuccess();
    void setAccount(const std::string& account, const std::string& password);
};





#endif // !LOGINENTRUST_H_
