#include<iostream>
#include"TestFunctionForModule.h"

using namespace std;
#define PATH R"(database\AccountTable.xml)"

#include"AccountTableXML.h"

int main() {
    AccountTableXML a(PATH,"root");
    a.ini_module();
    AccountInfo sad{"test","1","1","jklj",std::pair<int,int>(0,90),false,true ,false };
    cout << ERRORINFORMATION(a.setAccount("qq", sad)) ;
    a.save();
    
    return 0;
}