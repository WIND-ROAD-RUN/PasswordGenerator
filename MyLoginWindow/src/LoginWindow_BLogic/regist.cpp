#include "regist.h"
#include"accountStoreTranmist.h"
Regist::Regist(const std::string& account, const std::string& password)
    :RegistAbstract(account,password),m_accountStoreTranmsit(new AccountStoreTranmsit())
{
}
Regist::~Regist()
{
    delete m_accountStoreTranmsit;
}
bool Regist::have_account_if()
{
    if (m_accountStoreTranmsit->searchAccount(account())) { return true; }
    else { return false; }
}

bool Regist::save_account()
{
    if (m_accountStoreTranmsit->saveAccountInfo(account(), password())
        ==AccountStoreTranmsit::AccountStoreTranmsitResult::SavedAccountSucceed) 
    { 
        return true; 
    }
    else
    {
        return false; 
    }
}
