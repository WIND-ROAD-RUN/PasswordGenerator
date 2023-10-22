#ifndef PASSWORDENCRPYSIMPLYACH_H_
#define PASSWORDENCRPYSIMPLYACH_H_

#include"PasswordEncrpyModuleAbstract.h"

class PasswordEncrpySimplyAch
    :public PasswordEncrpyModuleAbstract {

public:
    // Í¨¹ý PasswordEncrpyModuleAbstract ¼Ì³Ð
    AccountInfo& encrpyForSave(AccountInfo& accountInfo) override;

    AccountInfo& decrptForUser(AccountInfo& accountInfo) override;

    void encrpy_PasswordLength(AccountInfo& accountInfo) override;

    void encrpy_haveSpecialSymbols(AccountInfo& accountInfo) override;

    void encrpy_haveUppercaseLowercase(AccountInfo& accountInfo) override;

    void encrpy_EncrpyIsIrreversible(AccountInfo& accountInfo) override;

};




#endif // !PASSWORDENCRPYSIMPLYACH_H_

