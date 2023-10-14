#include "login.h"
#include"accountStoreTranmist.h"

Login::Login(const std::string& account, const std::string& password)
    : LoginAbstract(account, password),m_accountStoreTranmsit(new AccountStoreTranmsit) {}

Login::~Login()
{
    delete m_accountStoreTranmsit;
}

bool Login::check_Account()
{
    if (m_accountStoreTranmsit->checkPassword(account(), password())
        ==AccountStoreTranmsit::AccountStoreTranmsitResult::RightPassword) {
        return true; 
    }
    else { 
        return false; 
    }
}