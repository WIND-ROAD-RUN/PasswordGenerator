#include "LoginWindow.h"
#include <QtWidgets/QApplication>
#include"LocalizationStringLoader-XML.h"
#include"ConfigurationLoader-XML.h"

#define CONFIGPATH R"(G:\project\code_place\vs_code_place\MyPasswordGenerator\PasswordGeneratorProject\MyLoginWindow\config\config.xml)"
#define LOCALIZATIONSTRINGPATH R"(G:\project\code_place\vs_code_place\MyPasswordGenerator\PasswordGeneratorProject\MyLoginWindow\config\localizationString.xml)"

ConfigurationLoaderXML* configCom = ConfigurationLoaderXML::getInstance();
LocalizationStringLoaderXML* loStrCom = LocalizationStringLoaderXML::getInstance();


void preparate_for_run();
void preparate_for_exit();

int main(int argc, char *argv[])
{
    preparate_for_run();
    QApplication a(argc, argv);
    LoginWindow w(loStrCom,configCom);
    w.show();
    return a.exec();
}

void preparate_for_run()
{
    configCom->setFilePath(CONFIGPATH);
    configCom->loadConfig();
    loStrCom->setFilePath(LOCALIZATIONSTRINGPATH);
    loStrCom->setLanguage(configCom->Language());
    loStrCom->loadData();
}

void preparate_for_exit()
{
    delete loStrCom;
    delete configCom;
}
