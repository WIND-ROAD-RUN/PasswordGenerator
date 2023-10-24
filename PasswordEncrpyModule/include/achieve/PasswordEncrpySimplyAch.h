#ifndef PASSWORDENCRPYSIMPLYACH_H_
#define PASSWORDENCRPYSIMPLYACH_H_

#include"PasswordEncrpyModuleAbstract.h"

class PasswordEncrpySimplyAch
    :public PasswordEncrpyModuleAbstract {

public:
    // ͨ�� PasswordEncrpyModuleAbstract �̳�
    AccountInfo encrpyForSave(const AccountInfo& accountInfo) override;

    AccountInfo decrptForUser(const AccountInfo& accountInfo) override;

    void encrpy_PasswordLength(AccountInfo& accountInfo) override;

    void encrpy_haveSpecialSymbols(AccountInfo& accountInfo) override;

    void encrpy_haveUppercaseLowercase(AccountInfo& accountInfo) override;

    void encrpy_EncrpyIsIrreversible(AccountInfo& accountInfo) override;

};




#endif // !PASSWORDENCRPYSIMPLYACH_H_

