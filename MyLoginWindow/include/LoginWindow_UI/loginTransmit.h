#ifndef LOGINTRANSMIT_H_
#define LOGINTRANSMIT_H_

#include<String>
#include"login.h"

using namespace std;
class LoginTransmit {
private:
    std::string m_account;
    std::string m_password;
    Login* m_login;
public:
    LoginTransmit(const string& account, const string& password)
        :m_login(new Login(account, password)) {}
    ~LoginTransmit() {};
    inline bool isLoginSuccess() { return m_login->login(); }
    void setAccount(const string& account, const string& password);
};





#endif // !LOGINENTRUST_H_
