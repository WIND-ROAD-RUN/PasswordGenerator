#ifndef PASSWORDENCRPYMODULEABSTRACT_H_
#define PASSWORDENCRPYMODULEABSTRACT_H_

#include"NameDefineForPEMA.h"

class PasswordEncrpyModuleAbstract {
public:
    AccountInfo encrpyForGeneratePassoword(const AccountInfo & accountInfo);

    virtual AccountInfo  encrptForSave(const AccountInfo& accountInfo)=0;

    virtual void  encrptForSave(AccountInfo& accountInfo) = 0;

    virtual AccountInfo decrptForUser(const AccountInfo& accountInfo)=0;
    
    virtual void decrptForUser(AccountInfo& accountInfo) = 0;

protected:
    virtual void encrpt_build_hash(AccountInfo & accountInfo)=0;
    virtual void encrpt_PasswordLength(AccountInfo& accountInfo)=0;

    virtual void encrpt_haveSpecialSymbols(AccountInfo& accountInfo)=0;

    virtual void encrpt_haveUppercaseLowercase(AccountInfo& accountInfo)=0;

    virtual void encrpt_EncrpyIsIrreversible(AccountInfo& accountInfo)=0;
};




#endif // !PASSWORDENCRPYMODULE_H_

