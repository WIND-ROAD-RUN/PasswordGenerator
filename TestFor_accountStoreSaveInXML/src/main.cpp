#include"accountStoreSaveInXML.h"
#include<string>
#include<iostream>

#define PATH R"(E:\vs_project_work_place\PasswordGenerator\TestFor_accountStoreSaveInXML\database\accountTable.xml)"

using namespace std;

int main() {

    AccountStoreSaveInXML * accountCom=AccountStoreSaveInXML::getInstance();
    accountCom->setFilePath(PATH);
    accountCom->ini_accountTable();
    cout << accountCom->search_account("root")<<endl;
    cout << accountCom->save_account_exceptExist("user1","user1")<<endl;
    cout << accountCom->search_account("user1")<<endl;
    accountCom->clear_registTable();
    cout << accountCom->search_account("root") << endl;
    cout << accountCom->save_account_exceptExist("user1", "user1") << endl;
    cout << accountCom->search_account("user1");
    

    return 0;
}