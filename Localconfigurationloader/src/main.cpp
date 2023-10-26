#include"ConfigurationLoader-XML.h"
#include"LocalizationStringLoader-XML.h"
#include<string>
#include<iostream>

using namespace std;
#define CONFIGPATHTEST R"(database\configuration.xml)"
#define STRINGPATH R"(database\string.xml)"


int main() {

    ConfigurationLoaderXML * configLoader=ConfigurationLoaderXML::getInstance();
    configLoader->setFilePath(CONFIGPATHTEST);
    cout << configLoader->loadConfig() << endl;
    configLoader->setLocalLanguage("CHN");
    cout << configLoader->storeConfig() << endl;

    LocalizationStringLoaderXML *  stringLoader= LocalizationStringLoaderXML::getInstance();
    stringLoader->setFilePath(STRINGPATH);
    stringLoader->setLanguage(configLoader->Language());
    cout<< stringLoader->loadData()<<endl;
    cout << stringLoader->getString("1") << endl;
    cout << stringLoader->getString("2") << endl;
    cout << stringLoader->getString("3") << endl;
    cout << stringLoader->getString("4") << endl;
    cout << stringLoader->getString("5") << endl;
    cout << stringLoader->getString("6") << endl;
    cout << stringLoader->getString("7") << endl;
    cout << stringLoader->getString("8") << endl;
    return 0;
}