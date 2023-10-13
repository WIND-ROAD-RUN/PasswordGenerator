#include "LocalizationStringManager.h"

LocalizationStringManager::LocalizationStringManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LocalizationStringManagerClass())
{
    ui->setupUi(this);
}

LocalizationStringManager::~LocalizationStringManager()
{
    delete ui;
}

