#include "DialogAddExistAccount.h"
#include"PortalAccountTable.h"

#include<QMessageBox>

DialogAddExistAccount::DialogAddExistAccount(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogAddExistAccountClass())
{
    ui->setupUi(this);
    build_connect();
    build_ui();
    setFixedSize(this->width(), this->height());
}

DialogAddExistAccount::~DialogAddExistAccount()
{
    delete ui;
}

void DialogAddExistAccount::build_ui()
{

}

void DialogAddExistAccount::build_connect()
{
    QObject::connect(ui->pbtn_cancel,&QPushButton::clicked,this,&DialogAddExistAccount::pbtn_cancel_clicked);
    QObject::connect(ui->pbtn_ok, &QPushButton::clicked, this, &DialogAddExistAccount::pbtn_ok_clicked);
}

void DialogAddExistAccount::pbtn_ok_clicked()
{
    if (ui->ledit_platform->text().isEmpty()) {
        QMessageBox::warning(this, "错误", "平台名不能为空");
        return;
    }

    if (ui->ledit_account->text().isEmpty()) {
        QMessageBox::warning(this,"错误","用户名不能为空");
        return;
    }
    
    auto portal = PortalAccountTable::getInstance();

    auto AccountName = portal->search_account(Platform().toStdString(), Account().toStdString());
    if (!AccountName.accountName.empty()) {
        QMessageBox::warning(this, "警告", "已有该账户");
    }
    else {
        this->accept();
    }
}

AccountInfo DialogAddExistAccount::accountInfo()
{
    AccountInfo result;
    result.accountName = Account().toStdString();
    result.password = Password().toStdString();
    return result;
}

void DialogAddExistAccount::pbtn_cancel_clicked() {
    this->reject();
}