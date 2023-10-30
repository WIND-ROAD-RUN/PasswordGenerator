#include "registAbstract.h"

bool RegistAbstract::regist()
{
    if (have_account_if()) { return false; }
    std::string encPassword = encrpt(m_password);
    if (save_account()) { return true; }
    else { return false; }
}

std::string RegistAbstract::encrpt
(const std::string& password)
{
    return std::string();
}

void RegistAbstract::setAccount
(const std::string& account, const std::string& password)
{
    m_account = account;
    m_password = password;
}
