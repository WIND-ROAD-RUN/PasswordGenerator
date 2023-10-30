#ifndef REGISTABSTRACT_H_
#define REGISTABSTRACT_H_

#include<string>

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
    /*模板算法*/
    bool regist();
public:
    void setAccount(const std::string& account, const std::string& password);
    void set_account(const std::string& account) { m_account = account; }
    void set_password(const std::string& password) { m_password = password; }
    std::string account() const { return m_account; }
    std::string password() const { return m_password; }

};






#endif // !REGISTABSTRACT_H_
