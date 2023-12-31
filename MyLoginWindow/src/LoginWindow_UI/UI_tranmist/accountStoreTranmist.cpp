#include "accountStoreTranmist.h"

#include"accountStoreSaveInTxt.h"
#include"accountStoreSaveInXML.h"

#include"config.h"

AccountStoreTranmsit::AccountStoreTranmsit()
{
    m_accountStoreAbstract = AccountStoreSaveInXML::getInstance();
}

AccountStoreTranmsit::~AccountStoreTranmsit()
{
    delete m_accountStoreAbstract;
}

AccountStoreTranmsitResult
AccountStoreTranmsit::searchAccount
(const std::string& account)
{
    if (m_accountStoreAbstract->search_account(account)) {
        return AccountStoreTranmsitResult::ExistingAccount;
    }
    else {
        return AccountStoreTranmsitResult::EmptyAccount;
    }
}

AccountStoreTranmsitResult 
AccountStoreTranmsit::checkPassword
(const std::string& account, const std::string& password)
{
    if (m_accountStoreAbstract->check_password(account, password)) {
        return AccountStoreTranmsitResult::RightPassword;
    }
    else {
        return AccountStoreTranmsitResult::ErrorPassword;
    }
}

AccountStoreTranmsitResult
AccountStoreTranmsit::saveAccountInfo
(const std::string& account, const std::string& password)
{
    if (m_accountStoreAbstract->save_account_exceptExist(account, password)) {
        return AccountStoreTranmsitResult
            ::SavedAccountSucceed;
    }
    else {
        AccountStoreTranmsitResult::SavedAccountFailed;
    }
}
