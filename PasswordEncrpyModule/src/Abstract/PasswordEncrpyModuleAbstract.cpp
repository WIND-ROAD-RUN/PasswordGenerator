#include "PasswordEncrpyModuleAbstract.h"

AccountInfo PasswordEncrpyModuleAbstract::encrpyForUser(AccountInfo& accountInfo)
{
    encrpt_haveSpecialSymbols(accountInfo);
    encrpt_haveUppercaseLowercase(accountInfo);
    encrpt_EncrpyIsIrreversible(accountInfo);
    encrpt_PasswordLength(accountInfo);

    return accountInfo;
}   
