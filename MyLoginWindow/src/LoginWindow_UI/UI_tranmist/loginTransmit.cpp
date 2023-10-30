#include"loginTransmit.h"

#include"login.h"

LoginTransmit::LoginTransmit
(const std::string& account, const std::string& password)
    :m_login(new Login(account, password)) 
{
}

bool LoginTransmit::isLoginSuccess()
{
    return m_login->login();
}
void LoginTransmit::setAccount
(const std::string& account, const std::string& password)
{
    m_login->setAccount(account, password);
}
