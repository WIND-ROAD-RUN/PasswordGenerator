#ifndef REGISTTRANSMIT_H_
#define REGISTTRANSMIT_H_

#include<string>

class Regist;

class RegistTransmit {
private:
    std::string m_account;
    std::string m_password;
private:
    Regist* m_regist;
public:
    RegistTransmit(const std::string& account, const std::string& password);
    ~RegistTransmit() {};
public:
    void setAccount(const std::string& account, const std::string& password) 
    {
        m_account = account;
        m_password = password;
    }
    bool isRegistSuccessful();
};


#endif // !REGISTTRANSMIT_H_
