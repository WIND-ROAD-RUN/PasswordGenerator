#include"PortalAccountTable.h"
#include<iostream>
#include"TestForPortalAccountTable.h"

#define PATH R"(G:\project\code_place\vs_code_place\MyPasswordGenerator1\PortalAccountTable\database\accountTable.xml)"

using namespace std;

int main() {
    PortalAccountTable m_Protal;
    m_Protal.setFilePath(PATH);
    m_Protal.setUID("root");
    cout << ERRORINFORMATION(m_Protal.ini_portal());
    
    return 0;
}