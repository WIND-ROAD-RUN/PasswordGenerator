#ifndef TESTFORPORTALACCOUNTTABLE_H_
#define TESTFORPORTALACCOUNTTABLE_H_

#include<string>
#include"NameDefineForPAT.h"

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

#endif // !TESTFORPORTALACCOUNTTABLE_H_
