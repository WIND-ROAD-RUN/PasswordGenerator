#include "RegistTransmit.h"
#include"regist.h"

RegistTransmit::RegistTransmit(const std::string& account, const std::string& password)
    :m_regist(new Regist(account,password))
{
}

bool RegistTransmit::isRegistSuccessful()
{
    if (m_regist->regist()) { return true; }
    else { return false; }
}
