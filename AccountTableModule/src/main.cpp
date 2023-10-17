#include<iostream>
#include"TestFunctionForModule.h"

using namespace std;
#define PATH R"(G:\project\code_place\vs_code_place\MyPasswordGenerator1\1.xml)"

#include"AccountTableXML.h"

int main() {
    AccountTableXML a(PATH,"root");

    cout << ERRORINFORMATION(a.ini_module())<<endl;
    auto result = a.ini_module();
    if (result!=ErrorAccountTableModule::No_ERROR) {
        std::cout << ERRORINFORMATION(a.NewAccountTable(PATH)) << endl;
    }
    
    std::cout << ERRORINFORMATION(a.ini_module());
    return 0;
}