#include"PortalAccountTable.h"
#include<iostream>
#include"TestForPortalAccountTable.h"

#define PATH R"(G:\project\code_place\vs_code_place\MyPasswordGenerator1\PortalAccountTable\database\accountTable.xml)"

using namespace std;

int main() {
    PortalAccountTable *  m_Prota=PortalAccountTable::getInstance();
    m_Prota->setFilePath(PATH);
    m_Prota->setUID("root");
    cout << ERRORINFORMATION(m_Prota->ini_portal());
    
    return 0;
}