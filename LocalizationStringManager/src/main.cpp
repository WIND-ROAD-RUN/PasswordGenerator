#include "LocalizationStringManager.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LocalizationStringManager w;
    w.show();
    return a.exec();
}
