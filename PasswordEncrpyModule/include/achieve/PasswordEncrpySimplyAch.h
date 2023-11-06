#ifndef PASSWORDENCRPYSIMPLYACH_H_
#define PASSWORDENCRPYSIMPLYACH_H_

#include<string>
#include"PasswordEncrpyModuleAbstract.h"

class PasswordEncrpySimplyAch
    :public PasswordEncrpyModuleAbstract {
private:
    std::string m_key;
private:
    std::string encryptAES(const std::string& plaintext, const std::string& key);

    std::string decryptAES(const std::string& ciphertext, const std::string& key);

    std::string toHex_forString(const std::string& input);

    std::string fromHex_forString(const std::string& input);

public:
    void setKey(const std::string& key) { m_key = key; }

    AccountInfo encrptForSave(const AccountInfo& accountInfo) override;

    void encrptForSave(AccountInfo& accountInfo) override;

    AccountInfo decrptForUser(const AccountInfo& accountInfo) override;

    void decrptForUser(AccountInfo& accountInfo) override;

    void encrpt_PasswordLength(AccountInfo& accountInfo) override;

    void encrpt_haveSpecialSymbols(AccountInfo& accountInfo) override;

    void encrpt_haveUppercaseLowercase(AccountInfo& accountInfo) override;

    void encrpt_EncrpyIsIrreversible(AccountInfo& accountInfo) override;

};




#endif // !PASSWORDENCRPYSIMPLYACH_H_

