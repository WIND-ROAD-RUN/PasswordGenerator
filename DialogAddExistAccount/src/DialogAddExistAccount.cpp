#include "DialogAddExistAccount.h"

DialogAddExistAccount::DialogAddExistAccount(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogAddExistAccountClass())
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
}

DialogAddExistAccount::~DialogAddExistAccount()
{
    delete ui;
}
