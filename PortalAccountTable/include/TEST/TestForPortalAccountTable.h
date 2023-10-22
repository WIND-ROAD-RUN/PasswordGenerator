#ifndef TESTFORPORTALACCOUNTTABLE_H_
#define TESTFORPORTALACCOUNTTABLE_H_

#include<string>
#include"NameDefineForPAT.h"
#include"TestFunctionForModule.h"
#include<iostream>

std::string ERRORINFORMATION(ErrorPortalAccountTable error) {
    switch (error) {
    case PATH_ERROR:
        return std::move(std::string("PATH_ERROR"));
    case initialization_ERROR:
        return std::move(std::string("initialization_ERROR"));
    case NO_ERROR:
        return std::move(std::string("NO_ERROR"));
    }
}

void PRINTACCOUNTINFO(const AccountInfo & account) {
    using std::cout;
    using std::endl;

    cout <<"AccountName:" << account.accountName << endl;
    cout <<"Password:" << account.password << endl;
    cout << "PasswordLength:" << endl
        << "    Minimum:"<<account.passwordLength.first<<endl 
        <<"    Maximum:"<< account.passwordLength.second << endl;
    cout <<"PhoneNumber:" << account.phoneNumber << endl;
    cout <<"User:" << account.User << endl;
    cout <<"EncrpyIsIrreversible:" << account.EncrpyIsIrreversible << endl;
    cout <<"haveSpecialSymbols:" << account.haveSpecialSymbols << endl;
    cout <<"haveUppercaseLowercase:" << account.haveUppercaseLowercase << endl << endl;
}

#endif // !TESTFORPORTALACCOUNTTABLE_H_
