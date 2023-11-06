#include "login.h"

#include"accountStoreTranmist.h"
#include <openssl/sha.h>
#include<sstream>
#include <iomanip>

Login::Login
(const std::string& account, const std::string& password)
    : LoginAbstract(account, password),
    m_accountStoreTranmsit(new AccountStoreTranmsit) {}

Login::~Login()
{
    delete m_accountStoreTranmsit;
}

std::string Login::encrpt_bySha256(const std::string& data)
{
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data.c_str(), data.length());

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    ss << std::hex << std::uppercase;

    for (int i = 0; i < 32; i++) {
        ss << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}

bool Login::check_Account()
{
    if (m_accountStoreTranmsit->checkPassword(account(), encrpt(password()))
        ==AccountStoreTranmsitResult::RightPassword) {
        return true; 
    }
    else { 
        return false; 
    }
}

std::string Login::encrpt(const std::string & password)
{
    return encrpt_bySha256(password);
}
