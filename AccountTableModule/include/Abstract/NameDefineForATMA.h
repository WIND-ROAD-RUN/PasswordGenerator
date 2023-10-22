#ifndef NAMEDEFINEFORABSTRACT_H_
#define NAMEDEFINEFORABSTRACT_H_

#include<string>
#include<vector>
#include<unordered_map>


using ATMAstring = std::string;
using ATMAint = int;
using ATMAbool = bool;
using ATMApair = std::pair<ATMAint, ATMAint>;

using ATMAStringList = std::vector<std::string>;



struct AccountInfo {
    ATMAstring accountName{};
    ATMAstring password{};
    ATMAstring phoneNumber{};
    ATMAstring User{};
    ATMApair passwordLength{};
    ATMAbool haveSpecialSymbols{false};
    ATMAbool haveUppercaseLowercase{ false };
    ATMAbool EncrpyIsIrreversible{ false };
};

using ATMAAccountList = std::vector<AccountInfo>;
using PATmap = std::unordered_map<ATMAstring, ATMAAccountList>;

enum ErrorAccountTableModule
{
    No_ERROR = 1,
    NewAccount_ERROR,
    NewPassword_ERROR,
    NewPhoneNumber_ERROR,
    NewUser_ERROR,
    NewEncrpyProperty_ERROR,
    NewPasswordLength_ERROR,
    NewhaveSpecialSymbols_ERROR,
    NewhaveUppercaseLowercase_ERROR,
    NewEncrpyIsIrreversible_ERROR,
    setAccount_ERROR,
    setPassword_ERROR,
    setPhoneNumber_ERROR,
    setUser_ERROR,
    setEncrpyProperty_ERROR,
    setPasswordLength_ERROR,
    sethaveSpecialSymbols_ERROR,
    sethaveUppercaseLowercase_ERROR,
    setEncrpyIsIrreversible_ERROR,
    NewPlatform_ERROR,
    NewAccountTable_ERROR,
    Initialization_ERROR,
    SaveData_ERROR,
    PlatformAlreadyExist,
    AccountAlreadyExist,
    NoPlatformNode,
    NoAccountNode,
    NoAccounTable,
    deletePlatform_ERROR,
    deleteAccount_ERROR
};



#endif // !NAMEDEFINEFORABSTRACT_H_

