#include "PasswordEncrpyModuleAbstract.h"

AccountInfo PasswordEncrpyModuleAbstract::encrpyForGeneratePassoword(const AccountInfo & accountInfo)
{
    AccountInfo result = accountInfo;
    encrpt_build_hash(result);
    encrpt_haveSpecialSymbols(result);
    encrpt_haveUppercaseLowercase(result);
    encrpt_EncrpyIsIrreversible(result);
    encrpt_PasswordLength(result);

    return result;
}   
