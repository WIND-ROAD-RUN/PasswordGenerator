#include "DialogRegist.h"

#include <QMessageBox>

#include "RegistTransmit.h"
#include"LocalizationStringLoader-XML.h"

DialogRegist::DialogRegist( QWidget* parent )
    : m_locStCom(LocalizationStringLoaderXML::getInstance()), QDialog(parent)
    , ui(new Ui::DialogRegistClass())
{
    ui->setupUi(this);
    build_languageString();
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
    ui->ledit_password->setEchoMode(QLineEdit::Password);
    ui->ledit_passwordAgin->setEchoMode(QLineEdit::Password);
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

QString DialogRegist::localizationString(const std::string stringId)
{
    return QString(QString::fromStdString(m_locStCom->getString(stringId)));
}

void DialogRegist::on_pbtn_ok_clicked() {
    if (ui->ledit_account->text().isEmpty()) {
        ui->label_error->setText(localizationString("17"));
        return;
    }
    else if (ui->ledit_password->text().isEmpty()) {
        ui->label_error->setText(localizationString("18"));
        return;
    }
    else if (ui->ledit_password->text() != ui->ledit_passwordAgin->text()) {
        ui->label_error->setText(localizationString("19"));
        return;
    }
    else {
        if (registAccount()) {
            this->accept();
        }
        else {
            QMessageBox::warning(this, localizationString("21"), localizationString("20"));
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

void DialogRegist::build_languageString()
{
    this->setWindowTitle(localizationString("2"));
    ui->label_account->setText(localizationString("5"));
    ui->label_accountRegist->setText(localizationString("8"));
    ui->label_error->setText(localizationString("10"));
    ui->label_password->setText(localizationString("6"));
    ui->label_passwordAgain->setText(localizationString("9"));
    ui->pbtn_cancel->setText(localizationString("12"));
    ui->pbtn_ok->setText(localizationString("11"));
}
