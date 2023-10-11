#ifndef LOGINABSTRACT_H_
#define LOGINABSTRACT_H_
#include<string>
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
#endif // !LOGIN___

