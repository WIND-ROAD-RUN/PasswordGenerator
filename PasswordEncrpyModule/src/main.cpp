#include <iostream>
#include<algorithm>
#include <fstream>
#include<sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <bitset>
#include <vector>
#include"PasswordEncrpySimplyAch.h"

using namespace std;

void printAll(std::vector<std::string> passwordSrc) {
    for (const auto & item:passwordSrc) {
        cout << item << endl;
    }
}

int main() {
    PasswordEncrpySimplyAch PESAtest;
    AccountInfo test;
    test.accountName = "1root1231";
    test.EncrpyIsIrreversible = false;
    test.haveSpecialSymbols = false;
    test.haveUppercaseLowercase = true;
    test.phoneNumber = "";
    test.User = "";
    test.passwordLength = {6,6};

    auto result=PESAtest.encrpyForGeneratePassoword(test);
    cout << PESAtest.m_passwordHash << endl;
    printAll(PESAtest.m_passwordSrc);
    cout << result.password;
    
    return 0;
}