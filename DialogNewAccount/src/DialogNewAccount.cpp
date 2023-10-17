#include "DialogNewAccount.h"

DialogNewAccount::DialogNewAccount(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogNewAccountClass())
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
}

DialogNewAccount::~DialogNewAccount()
{
    delete ui;
}
