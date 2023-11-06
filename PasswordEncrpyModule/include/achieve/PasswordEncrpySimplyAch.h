#ifndef PASSWORDENCRPYSIMPLYACH_H_
#define PASSWORDENCRPYSIMPLYACH_H_

#include<string>
#include<vector>
#include"PasswordEncrpyModuleAbstract.h"

class PasswordEncrpySimplyAch
    :public PasswordEncrpyModuleAbstract {
public:
    std::string m_key;
public:
    std::string m_platform;
    std::string m_passwordHash;
    std::vector<std::string> m_passwordSrc;
private:
    std::string encryptAES(const std::string& plaintext, const std::string& key);

    std::string decryptAES(const std::string& ciphertext, const std::string& key);

    std::string toHex_forString(const std::string& input);

    std::string fromHex_forString(const std::string& input);

    std::string getCurrentTime();

private:
    std::string getHash(const std::string& data);

    std::string combineHash(const std::string& first, const std::string second);

    std::vector<uint32_t> hashToVector(const std::string& hexString);

    std::string getPasswordPart(uint32_t value, const std::string& characterSet);

    std::string getSpecialSymbols(uint32_t value);

    std::string getNumber(uint32_t value);

    std::string getSmallLetter(uint32_t value);

    std::string getBigLetter(uint32_t value);

    std::string getBigAndSmallLetter(uint32_t forSmall, uint32_t forBig);

public:
    void setPlatform(const std::string platform) { m_platform = platform; }

    void clearPasswordData() { m_passwordSrc.clear(); }

    void setKey(const std::string& key) { m_key = key; }

    AccountInfo encrptForSave(const AccountInfo& accountInfo) override;

    void encrptForSave(AccountInfo& accountInfo) override;

    AccountInfo decrptForUser(const AccountInfo& accountInfo) override;

    void decrptForUser(AccountInfo& accountInfo) override;

    void encrpt_PasswordLength(AccountInfo& accountInfo) override;

    void encrpt_haveSpecialSymbols(AccountInfo& accountInfo) override;

    void encrpt_haveUppercaseLowercase(AccountInfo& accountInfo) override;

    void encrpt_EncrpyIsIrreversible(AccountInfo& accountInfo) override;


    // 通过 PasswordEncrpyModuleAbstract 继承
    void encrpt_build_hash(AccountInfo& accountInfo) override;

};




#endif // !PASSWORDENCRPYSIMPLYACH_H_

