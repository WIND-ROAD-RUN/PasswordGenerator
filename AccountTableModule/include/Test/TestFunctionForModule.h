#ifndef TESTFUNCTIONFORMODULE_H_
#define TESTFUNCTIONFORMODULE_H_

#include<string>
#include"NameDefineForAbstract.h"

std::string ERRORINFORMATION(ErrorAccountTableModule error) {
    switch (error) {
    case No_ERROR:
        return std::move(std::string("NoError"));
    case NewAccount_ERROR:
        return std::move(std::string("NewAccount_ERROR"));
    case NewPassword_ERROR:
        return std::move(std::string("NewPassword_ERROR"));
    case NewPhoneNumber_ERROR:
        return std::move(std::string("NewPoheNumber_ERROR"));
    case NewUser_ERROR:
        return std::move(std::string("NewUser_ERROR"));
    case NewEncrpyProperty_ERROR:
        return std::move(std::string("NewEncrpyProperty_ERROR"));
    case NewPasswordLength_ERROR:
        return std::move(std::string("NewPasswordLength_ERROR"));
    case NewhaveSpecialSymbols_ERROR:
        return std::move(std::string("NewhaveSpecialSymbols_ERROR"));
    case NewhaveUppercaseLowercase_ERROR:
        return std::move(std::string("NewhaveUppercaseLowercase_ERROR"));
    case NewEncrpyIsIrreversible_ERROR:
        return std::move(std::string("NewEncrpyIsIrreversible_ERROR"));
    case setAccount_ERROR:
        return std::move(std::string("setAccount_ERROR"));
    case setPassword_ERROR:
        return std::move(std::string("setPassword_ERROR"));
    case setPhoneNumber_ERROR:
        return std::move(std::string("setPhoneNumber_ERROR"));
    case setUser_ERROR:
        return std::move(std::string("setUser_ERROR"));
    case setEncrpyProperty_ERROR:
        return std::move(std::string("setEncrpyProperty_ERROR"));
    case setPasswordLength_ERROR:
        return std::move(std::string("setPasswordLength_ERROR"));
    case sethaveSpecialSymbols_ERROR:
        return std::move(std::string("sethaveSpecialSymbols_ERROR"));
    case sethaveUppercaseLowercase_ERROR:
        return std::move(std::string("sethaveUppercaseLowercase_ERROR"));
    case setEncrpyIsIrreversible_ERROR:
        return std::move(std::string("setEncrpyIsIrreversible_ERROR"));
    case NewPlatform_ERROR:
        return std::move(std::string("NewPlatform_ERROR"));
    case NewAccountTable_ERROR:
        return std::move(std::string("NewAccountTable_ERROR"));
    case Initialization_ERROR:
        return std::move(std::string("Initialization_ERROR"));
    case SaveData_ERROR:
        return std::move(std::string("SaveData_ERROR"));
    case PlatformAlreadyExist:
        return std::move(std::string("PlatformAlreadyExist"));
    case AccountAlreadyExist:
        return std::move(std::string("AccountAlreadyExist"));
    case NoPlatformNode:
        return std::move(std::string("NoPlatformNode"));
    case NoAccountNode:
        return std::move(std::string("NoAccountNode"));
    case NoAccounTable:
        return std::move(std::string("NoAccounTable"));
    }


}

#endif // !TESTFUNCTIONFORMODULE_H_
