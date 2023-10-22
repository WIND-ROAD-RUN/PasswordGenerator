#include "PasswordEncrpyModuleAbstract.h"

AccountInfo PasswordEncrpyModuleAbstract::encrpyForUser(AccountInfo& accountInfo)
{
    encrpy_haveSpecialSymbols(accountInfo);
    encrpy_haveUppercaseLowercase(accountInfo);
    encrpy_EncrpyIsIrreversible(accountInfo);
    encrpy_PasswordLength(accountInfo);

    return accountInfo;
}   
