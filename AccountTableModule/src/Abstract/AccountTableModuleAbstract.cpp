#include "AccountTableModuleAbstract.h"

ErrorAccountTableModule AccountTableModuleAbstract::NewAccountInfo(const ATMAstring& platform, const ATMAstring& account)
{
    if (!NewAccount(platform, account)) 
    { 
        return ErrorAccountTableModule::NewAccount_ERROR; 
    }

    if (!NewPassword()) {
        return ErrorAccountTableModule::NewPassword_ERROR;
    }
    if (!NewPhoneNumber()) 
    { 
        return ErrorAccountTableModule::NewPoheNumber_ERROR; 
    }
    if (!NewUser()) 
    { 
        return ErrorAccountTableModule::NewUser_ERROR; 
    }
    
    if (!NewEncrpyProperty()) 
    { 
        return ErrorAccountTableModule::NewEncrpyProperty_ERROR; 
    }

    if (!NewPasswordLength()) 
    { 
        return ErrorAccountTableModule::NewPasswordLength_ERROR; 
    }
    if (!NewhaveSpecialSymbols()) 
    { 
        return ErrorAccountTableModule::NewhaveSpecialSymbols_ERROR;
    }
    if (!NewhaveUppercaseLowercase()) 
    { 
        return ErrorAccountTableModule::NewhaveUppercaseLowercase_ERROR; 
    }
    if (!NewEncrpyIsIrreversible()) 
    { 
        return ErrorAccountTableModule::NewEncrpyIsIrreversible_ERROR;
    }
    
    return ErrorAccountTableModule::No_ERROR;
}
