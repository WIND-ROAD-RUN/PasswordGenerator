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

int main() {
    PasswordEncrpySimplyAch PESAtest;
    PESAtest.setKey(PESAtest.getHash("root"));
    AccountInfo test;
    test.accountName = "root";
    test.EncrpyIsIrreversible = false;
    test.haveSpecialSymbols = false;
    test.haveUppercaseLowercase = false;
    test.phoneNumber = "";
    test.User = "";

    PESAtest.encrpyForGeneratePassoword(test);
    cout << PESAtest.m_passwordHash << endl;

    test.phoneNumber = "13461360865";
    PESAtest.encrpyForGeneratePassoword(test);
    cout << PESAtest.m_passwordHash << endl;

    test.User = "user";
    PESAtest.encrpyForGeneratePassoword(test);
    cout << PESAtest.m_passwordHash << endl;

    return 0;
}