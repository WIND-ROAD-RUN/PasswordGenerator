#include "LoginWindow.h"
#include <QtWidgets/QApplication>
#include"LocalizationStringLoader-XML.h"
#include"ConfigurationLoader-XML.h"
#include"config.h"

ConfigurationLoaderXML* configCom;
LocalizationStringLoaderXML* loStrCom;

void preparate_for_run();
void preparate_for_exit();

int main(int argc, char *argv[])
{
    preparate_for_run();
    QApplication a(argc, argv);
    LoginWindow w;
    w.show();
    return a.exec();
}

void preparate_for_run() {
    configCom = ConfigurationLoaderXML::getInstance();
    loStrCom = LocalizationStringLoaderXML::getInstance();

    configCom->setFilePath(CONFIGPATH);
    configCom->loadConfig();
    loStrCom->setFilePath(LOCALIZATIONSTRINGPATH);
    loStrCom->setLanguage(configCom->Language());
    loStrCom->loadData();
}
void preparate_for_exit() {
    delete loStrCom;
    delete configCom;
}
