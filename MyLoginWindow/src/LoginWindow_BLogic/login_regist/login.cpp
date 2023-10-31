#include "login.h"

#include"accountStoreTranmist.h"
#include <openssl/sha.h>

Login::Login
(const std::string& account, const std::string& password)
    : LoginAbstract(account, password),
    m_accountStoreTranmsit(new AccountStoreTranmsit) {}

Login::~Login()
{
    delete m_accountStoreTranmsit;
}

std::string Login::sha256(const std::string& data)
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

bool Login::check_Account()
{
    if (m_accountStoreTranmsit->checkPassword(account(), encrpy(password()))
        ==AccountStoreTranmsitResult::RightPassword) {
        return true; 
    }
    else { 
        return false; 
    }
}

std::string Login::encrpy(const std::string & password)
{
    return sha256(password);
}
