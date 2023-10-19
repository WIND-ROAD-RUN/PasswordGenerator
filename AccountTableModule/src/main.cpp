#include<iostream>
#include"TestFunctionForModule.h"

using namespace std;
#define PATH R"(database\AccountTable.xml)"

#include"AccountTableXML.h"

int main() {
    AccountTableXML a(PATH,"root");
    a.ini_module();
    cout << ERRORINFORMATION(a.setAccount("qq", "root1", "root1"));
    a.save();
    
    return 0;
}