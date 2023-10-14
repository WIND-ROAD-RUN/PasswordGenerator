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
public:
    Regist(const std::string& account, const std::string& password);
    ~Regist();
    // 通过 RegistAbstract 继承
};



#endif // !REGIST_H_

