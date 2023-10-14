#include"ConfigurationLoader-XML.h"
#include<string>
#include<iostream>

using namespace std;
#define PATH R"(database\configuration.xml)"


int main() {

    ConfigurationLoaderXML * configLoader=ConfigurationLoaderXML::getInstacnce();
    configLoader->setFilePath(PATH);
    cout << configLoader->loadConfig() << endl;
    configLoader->setLocalLanguage("CHN");
    cout << configLoader->storeConfig() << endl;

    return 0;
}