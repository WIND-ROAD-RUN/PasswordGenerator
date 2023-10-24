#include "PasswordEncrpySimplyAch.h"

AccountInfo PasswordEncrpySimplyAch::encrpyForSave(const AccountInfo& accountInfo)
{
    AccountInfo result = accountInfo;
    result.password = result.accountName;
    return result;
}

AccountInfo PasswordEncrpySimplyAch::decrptForUser(const AccountInfo& accountInfo)
{
    return accountInfo;
}

void PasswordEncrpySimplyAch::encrpy_PasswordLength(AccountInfo& accountInfo)
{
}

void PasswordEncrpySimplyAch::encrpy_haveSpecialSymbols(AccountInfo& accountInfo)
{
}

void PasswordEncrpySimplyAch::encrpy_haveUppercaseLowercase(AccountInfo& accountInfo)
{
}

void PasswordEncrpySimplyAch::encrpy_EncrpyIsIrreversible(AccountInfo& accountInfo)
{
    accountInfo.password = accountInfo.accountName;
}
