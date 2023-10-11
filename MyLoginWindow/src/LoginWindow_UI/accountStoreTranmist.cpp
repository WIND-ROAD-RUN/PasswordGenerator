#include "accountStoreTranmist.h"
#include"accountStore.h"

AccountStoreTranmsit::AccountStoreTranmsit()
{
    m_accountStore = new AccountStore();
}

AccountStoreTranmsit::~AccountStoreTranmsit()
{
    delete m_accountStore;
}

AccountStoreTranmsit::AccountStoreTranmsitResult
AccountStoreTranmsit::searchAccount(const std::string& account)
{
    if (m_accountStore->search_account(account)) { 
        return AccountStoreTranmsitResult::ExistingAccount; 
    }
    else { 
        return AccountStoreTranmsitResult::EmptyAccount; 
    }
}

AccountStoreTranmsit::AccountStoreTranmsitResult 
AccountStoreTranmsit::checkPassword(const std::string& account, const std::string& password)
{
    if (m_accountStore->check_password(account, password)) {
        return AccountStoreTranmsitResult::RightPassword; 
    }
    else { 
        return AccountStoreTranmsitResult::ErrorPassword; 
    }
}

AccountStoreTranmsit::AccountStoreTranmsitResult
AccountStoreTranmsit::saveAccountInfo(const std::string& account, const std::string& password)
{
    if (m_accountStore->save_account_exceptExist(account, password)) {
        return AccountStoreTranmsitResult
            ::SavedAccountSucceed;
    }
    else { 
        AccountStoreTranmsitResult::SavedAccountFailed;
    }
}
