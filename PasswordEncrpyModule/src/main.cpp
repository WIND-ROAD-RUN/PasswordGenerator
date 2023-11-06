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
    PESAtest.setKey(PESAtest.getHash("root"));
    AccountInfo test;
    test.accountName = "root";
    test.EncrpyIsIrreversible = false;
    test.haveSpecialSymbols = true;
    test.haveUppercaseLowercase = true;
    test.phoneNumber = "";
    test.User = "";

    PESAtest.encrpyForGeneratePassoword(test);
    cout << PESAtest.m_passwordHash << endl;
    printAll(PESAtest.m_passwordSrc);
    

    return 0;
}