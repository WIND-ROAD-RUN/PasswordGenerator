#include "regist.h"

#include"accountStoreTranmist.h"
#include <openssl/sha.h>

std::string Regist::sha256(const std::string& data)
{
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data.c_str(), data.length());

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);

    std::string hashString;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        hashString += hash[i];
    }

    return hashString;
}

Regist::Regist
(const std::string& account, const std::string& password)
    :RegistAbstract(account,password),
    m_accountStoreTranmsit(new AccountStoreTranmsit())
{
}
Regist::~Regist()
{
    delete m_accountStoreTranmsit;
}
bool Regist::have_account_if()
{
    if (m_accountStoreTranmsit->searchAccount(account())
        ==AccountStoreTranmsitResult::ExistingAccount) { return true; }
    else { return false; }
}

bool Regist::save_account()
{
    if (m_accountStoreTranmsit->saveAccountInfo(account(), password())
        ==AccountStoreTranmsitResult::SavedAccountSucceed) 
    { 
        return true; 
    }
    else
    {
        return false; 
    }
}

std::string Regist::encrpt(const std::string& password)
{
    return sha256(password);
}
