#include "PasswordEncrpySimplyAch.h"

AccountInfo& PasswordEncrpySimplyAch::encrpyForSave(AccountInfo& accountInfo)
{
    return accountInfo;
}

AccountInfo& PasswordEncrpySimplyAch::decrptForUser(AccountInfo& accountInfo)
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
