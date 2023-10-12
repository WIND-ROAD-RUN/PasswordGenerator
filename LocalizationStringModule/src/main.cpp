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
    
    return 0;
}

