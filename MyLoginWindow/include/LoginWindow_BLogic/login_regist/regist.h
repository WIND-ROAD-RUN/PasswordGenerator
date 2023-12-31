#ifndef REGIST_H_
#define REGIST_H_

#include"registAbstract.h"

#include<string>

class AccountStoreTranmsit;

class Regist :public RegistAbstract{
private:
    AccountStoreTranmsit* m_accountStoreTranmsit;

    bool have_account_if() override;

    bool save_account() override;

    virtual std::string encrpt(const std::string& password)override;

    std::string sha256(const std::string& data);
public:
    Regist(const std::string& account, const std::string& password);

    ~Regist();

};



#endif // !REGIST_H_

