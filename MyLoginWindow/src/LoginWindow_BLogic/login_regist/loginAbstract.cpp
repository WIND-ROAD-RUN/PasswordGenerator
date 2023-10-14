#include "loginAbstract.h"

bool LoginAbstract::login()
{
    if (check_Account()) {
        return true;
    }
    else {
        return false;
    }
}

void LoginAbstract::setAccount(const std::string& account, const std::string& password)
{
    set_account(account);
    set_password(password);
}
