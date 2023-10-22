#ifndef PASSWORDENCRPYMODULEABSTRACT_H_
#define PASSWORDENCRPYMODULEABSTRACT_H_

#include"NameDefineForPEMA.h"

class PasswordEncrpyModuleAbstract {
public:
    AccountInfo encrpyForUser(AccountInfo & accountInfo);
    virtual AccountInfo & encrpyForSave(AccountInfo& accountInfo)=0;
    virtual AccountInfo& decrptForUser(AccountInfo& accountInfo)=0;
protected:
    virtual void encrpy_PasswordLength(AccountInfo& accountInfo)=0;
    virtual void encrpy_haveSpecialSymbols(AccountInfo& accountInfo)=0;
    virtual void encrpy_haveUppercaseLowercase(AccountInfo& accountInfo)=0;
    virtual void encrpy_EncrpyIsIrreversible(AccountInfo& accountInfo)=0;

};




#endif // !PASSWORDENCRPYMODULE_H_

