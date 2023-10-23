#include "DialogNewAccount.h"
#include"NameDefineForATMA.h"
#include"PortalAccountTable.h"

DialogNewAccount::DialogNewAccount(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogNewAccountClass())
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    build_ui();
    build_connect();
}

DialogNewAccount::~DialogNewAccount()
{
    delete ui;
}

void DialogNewAccount::build_ui()
{
    ui->cbox_phoneNumber->setChecked(false);
    ui->cbox_user->setChecked(false);
    ui->ledit_phoneNumber->setEnabled(false);
    ui->ledit_phoneNumber->clear();
    ui->ledit_user->setEnabled(false);
    ui->ledit_user->clear();
    ui->sBox_passwordLengthMinimum->setValue(0);
    ui->sBox_passwordLengthMaximum->setValue(0);
    ui->cBox_haveSpecalSymbols->setChecked(false);
    ui->cBox_haveUpperAndLowerCase->setChecked(false);
    ui->cBox_isIrreversible->setChecked(false);
}

void DialogNewAccount::build_connect()
{
    QObject::connect(ui->cbox_phoneNumber,&QCheckBox::stateChanged,this,&DialogNewAccount::cbox_phoneNumber_checked_change);
    QObject::connect(ui->cbox_user, &QCheckBox::stateChanged, this, &DialogNewAccount::cbox_user_checked_change);
}
void DialogNewAccount::cbox_user_checked_change()
{
    ui->ledit_user->clear();
    ui->ledit_user->setEnabled(ui->cbox_user->isChecked());
}
QString DialogNewAccount::Platform()
{
    return ui->ledit_accountPlatform->text();
}
QString DialogNewAccount::Account()
{
    return ui->ledit_account->text();
}
QString DialogNewAccount::Phonenumber()
{
    return ui->ledit_phoneNumber->text();
}
QString DialogNewAccount::User()
{
    return ui->ledit_user->text();
}
std::pair<int, int> DialogNewAccount::PasswordLength()
{
    return std::pair<int, int>(ui->sBox_passwordLengthMinimum->value(),ui->sBox_passwordLengthMaximum->value());
}
bool DialogNewAccount::haveSpecialSymbols()
{
    return ui->cBox_haveSpecalSymbols->isChecked();
}
bool DialogNewAccount::haveUpperLowerCase()
{
    return ui->cBox_haveUpperAndLowerCase->isChecked();
}
bool DialogNewAccount::isIrreversibleEncrpy()
{
    return ui->cBox_isIrreversible->isChecked();
}
AccountInfo DialogNewAccount::accountInfo()
{
    AccountInfo result;
    result.accountName = this->Account().toStdString();
    result.EncrpyIsIrreversible = this->isIrreversibleEncrpy();
    result.haveSpecialSymbols = this->haveSpecialSymbols();
    result.haveUppercaseLowercase = this->haveUpperLowerCase();
    result.passwordLength = this->PasswordLength();
    result.phoneNumber = this->Phonenumber().toStdString();
    result.User = this->User().toStdString();

    return result;
}
void DialogNewAccount::cbox_phoneNumber_checked_change() {
    ui->ledit_phoneNumber->clear();
    ui->ledit_phoneNumber->setEnabled(ui->cbox_phoneNumber->isChecked());
}

