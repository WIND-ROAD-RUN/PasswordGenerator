#include<string>
#include<iostream>
#include"LocalizationStringModule-XML.h"
#define LOCAT R"(database\LocalizationStringDatabase.xml)"

using namespace std;

int main() {
    LocalizationStringXML l;
    l.setFilePath(LOCAT);
    cout << l.loadFile() << endl;
    string s{"NO"};
    cout <<l.localString(s,"11","USA")<<endl;
    cout << s << endl;
    cout << l.localString("1","CHN") << endl;

    string s1("你好");
    cout << l.storeLocalString("8","CHN",s1)<<endl;
    cout << l.changeLocalString("8","sCHN",s) << endl;
    cout << l.storeLocalString("18", "sCHN", s) << endl;
    return 0;
}

