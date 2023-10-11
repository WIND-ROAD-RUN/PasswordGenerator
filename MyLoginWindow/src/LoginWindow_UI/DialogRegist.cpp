#include "DialogRegist.h"
#include "accountStoreTranmist.h"
#include <QMessageBox>

DialogRegist::DialogRegist(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::DialogRegistClass())
{
    ui->setupUi(this);
    build_ui();
    build_connect();
    m_accountStoreTranmsit = new AccountStoreTranmsit;
}

DialogRegist::~DialogRegist()
{
    delete ui;
    delete m_accountStoreTranmsit;
}

void DialogRegist::build_ui()
{
    ui->label_error->setText("");
    QPalette plet = ui->label_error->palette();
    plet.setColor(QPalette::WindowText, Qt::red);
    ui->label_error->setPalette(plet);
}

void DialogRegist::build_connect()
{
    QObject::connect(ui->pbtn_cancel, &QPushButton::clicked, this, &DialogRegist::close);
    QObject::connect(ui->ledit_account, &QLineEdit::textChanged, this, &DialogRegist::on_ledit_account_changed);
    QObject::connect(ui->ledit_password, &QLineEdit::textChanged, this, &DialogRegist::on_ledit_password_changed);
    QObject::connect(ui->ledit_passwordAgin, &QLineEdit::textChanged, this, &DialogRegist::on_ledit_password_again_changed);
}

bool DialogRegist::registAccount()
{
    AccountStoreTranmsit::AccountStoreTranmsitResult result =m_accountStoreTranmsit->saveAccountInfo(ui->ledit_account->text().toStdString(),
                                            ui->ledit_password->text().toStdString());
    return result == AccountStoreTranmsit::
        AccountStoreTranmsitResult::SavedAccountSucceed
        ? true : false;
}

void DialogRegist::on_pbtn_ok_clicked() {
    if (ui->ledit_account->text().isEmpty()) {
        ui->label_error->setText("用户名不合法或为空");
        return;
    }
    else if (ui->ledit_password->text().isEmpty()) {
        ui->label_error->setText("密码不能为空");
        return;
    }
    else if (ui->ledit_password->text() != ui->ledit_passwordAgin->text()) {
        ui->label_error->setText("两次密码输入不一致");
        return;
    }
    else {
        if (registAccount()) {
            this->accept();
        }
        else {
            QMessageBox::warning(this, "警告", "已经注册过该账户");
        }

    }
}
void DialogRegist::on_ledit_account_changed() {
    ui->label_error->setText("");
}
void DialogRegist::on_ledit_password_changed() {
    ui->label_error->setText("");
}
void DialogRegist::on_ledit_password_again_changed() {
    ui->label_error->setText("");
}
