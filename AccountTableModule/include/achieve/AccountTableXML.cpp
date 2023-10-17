#include "AccountTableXML.h"

#include <fstream>

ErrorAccountTableModule AccountTableXML::NewAccount(const ATMAstring& platform, const ATMAstring& account)
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::NewPassword()
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::NewPhoneNumber()
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::NewUser()
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::NewEncrpyProperty()
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::NewPasswordLength()
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::NewhaveSpecialSymbols()
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::NewhaveUppercaseLowercase()
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::NewEncrpyIsIrreversible()
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::setAccount(const ATMAstring& platform, const ATMAstring& account)
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::setPassword(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& password)
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::setPhoneNumber(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& phoneNumber)
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::setUser(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& user)
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::setEncrpyProperty(const ATMAstring& platform, const ATMAstring& account)
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::setPasswordLength(const ATMAstring& platform, const ATMAstring& account, ATMAint minimum, ATMAint Maximum)
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::sethaveSpecialSymbols(const ATMAstring& platform, const ATMAstring& account, ATMbool haveSpecialSymbols)
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::sethaveUppercaseLowercase(const ATMAstring& platform, const ATMAstring& account, ATMbool haveUppercaseLowercase)
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::setEncrpyIsIrreversible(const ATMAstring& platform, const ATMAstring& account, ATMbool EncrpyIsIrreversible)
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::NewAccountTable(const ATMAstring& fileName)
{
    std::ofstream file(fileName);
    if (file.is_open()) {
        file.close();
        auto NewAccountTableNode=m_doc.append_child("AccountTable");
        if (!NewAccountTableNode) 
        { 
            return ErrorAccountTableModule::NewAccountTable_ERROR; 
        }
        if (!NewAccountTableNode.append_attribute("UID").set_value(m_UID.c_str())) 
        { 
            return ErrorAccountTableModule::NewAccountTable_ERROR; 
        }
        if (!m_doc.save_file(fileName.c_str())) {
            return ErrorAccountTableModule::NewAccountTable_ERROR; 
        }
        return ErrorAccountTableModule::No_ERROR;
    }
    else {
        return ErrorAccountTableModule::NewAccountTable_ERROR;
    }
}

ErrorAccountTableModule AccountTableXML::NewPlatform(const ATMAstring& fileName)
{
    return ErrorAccountTableModule();
}

ErrorAccountTableModule AccountTableXML::ini_module()
{
    if (!m_doc.load_file(m_filePath.c_str())) { return ErrorAccountTableModule::Initialization_ERROR; }
    else { return ErrorAccountTableModule::No_ERROR; }
}
