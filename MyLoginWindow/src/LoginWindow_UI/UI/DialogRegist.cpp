#include "DialogRegist.h"
#include <QMessageBox>
#include "RegistTransmit.h"
#include"LocalizationStringLoader-XML.h"

DialogRegist::DialogRegist( QWidget* parent )
    : m_locStCom(LocalizationStringLoaderXML::getInstance()), QDialog(parent)
    , ui(new Ui::DialogRegistClass())
{
    ui->setupUi(this);
    setLanguageString(m_locStCom);
    build_ui();
    build_connect();   
}

DialogRegist::~DialogRegist()
{
    delete ui;
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
    RegistTransmit* m_regist=new RegistTransmit(ui->ledit_account->text().toStdString(),
        ui->ledit_password->text().toStdString());
    bool result = m_regist->isRegistSuccessful();
    delete m_regist;
    return result;
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

void DialogRegist::setLanguageString(LocalizationStringLoaderXML* locStCom)
{
    this->setWindowTitle(QString::fromStdString(locStCom->getString("2")));
    ui->label_account->setText(QString::fromStdString(locStCom->getString("5")));
    ui->label_accountRegist->setText(QString::fromStdString(locStCom->getString("8")));
    ui->label_error->setText(QString::fromStdString(locStCom->getString("10")));
    ui->label_password->setText(QString::fromStdString(locStCom->getString("6")));
    ui->label_passwordAgain->setText(QString::fromStdString(locStCom->getString("9")));
    ui->pbtn_cancel->setText(QString::fromStdString(locStCom->getString("12")));
    ui->pbtn_ok->setText(QString::fromStdString(locStCom->getString("11")));
}
