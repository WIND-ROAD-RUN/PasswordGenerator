#include "DialogNewAccount.h"
#include"NameDefineForATMA.h"
#include"PortalAccountTable.h"
#include<QMessageBox>
#include"LocalizationStringLoader-XML.h"
#include<QDir>

DialogNewAccount::DialogNewAccount(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogNewAccountClass())
{
    ui->setupUi(this);
    ini_GlobaComponet();
    build_languageString();
    build_ui();
    build_connect();
    build_icon();
    
    setFixedSize(this->width(), this->height());
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

    ui->sBox_passwordLengthMinimum->setValue(6);
    ui->sBox_passwordLengthMaximum->setValue(20);

    ui->cBox_haveSpecalSymbols->setChecked(false);
    ui->cBox_haveUpperAndLowerCase->setChecked(false);
    ui->cBox_isIrreversible->setChecked(false);
}

void DialogNewAccount::build_connect()
{
    QObject::connect(ui->cbox_phoneNumber,&QCheckBox::stateChanged,
        this,&DialogNewAccount::cbox_phoneNumber_checked_change);

    QObject::connect(ui->cbox_user, &QCheckBox::stateChanged, 
        this, &DialogNewAccount::cbox_user_checked_change);

    QObject::connect(ui->pbtn_ok,&QPushButton::clicked,
        this,&DialogNewAccount::pbtn_ok_clicked);

    QObject::connect(ui->pbtn_cancel,&QPushButton::clicked,
        this,&DialogNewAccount::pbtn_cancel_clicked);
}

void DialogNewAccount::build_languageString()
{
    this->setWindowTitle(localizationString("39"));

    ui->label_AccountPlatform->setText(localizationString("53")+":");
    ui->labelAccount->setText(localizationString("54") + ":");
    ui->label_haveSpecialSymbols->setText(localizationString("50") + ":");
    ui->label_haveUpperAndLowerCase->setText(localizationString("51") + ":");
    ui->label_isIrreversible->setText(localizationString("52") + ":");
    ui->label_passwordLength->setText(localizationString("47") + ":");
    ui->label_passwordLengthMaximum->setText("       " + localizationString("49") + ":");
    ui->label_passwordLengthMinimum->setText("       " + localizationString("48") + ":");

    ui->gBox_extraInformation->setTitle(localizationString("43"));
    ui->gBox_thePasswordProperty->setTitle(localizationString("46"));
    
    ui->pbtn_ok->setText(localizationString("11"));
    ui->pbtn_cancel->setText(localizationString("12"));

    ui->cbox_phoneNumber->setText(localizationString("45"));
    ui->cbox_user->setText(localizationString("44"));
}

void DialogNewAccount::build_icon()
{
    this->setWindowIcon(getIcon("edit-name.png"));
}

QIcon DialogNewAccount::getIcon(const QString& fileName)
{
    auto cutDir = QDir::currentPath();
    auto filePath = cutDir + "/icon/" + fileName;
    return QIcon(filePath);
}

void DialogNewAccount::ini_GlobaComponet()
{
    m_locstringLoader = LocalizationStringLoaderXML::getInstance();
}

QString DialogNewAccount::localizationString(const std::string stringId)
{
    return QString(QString::fromStdString(m_locstringLoader->getString(stringId)));
}

void DialogNewAccount::cbox_user_checked_change()
{
    ui->ledit_user->clear();
    ui->ledit_user->setEnabled(ui->cbox_user->isChecked());
}

void DialogNewAccount::pbtn_ok_clicked()
{
    if (ui->ledit_accountPlatform->text().isEmpty()) {
        QMessageBox::warning(this, localizationString("28"), localizationString("55"));
        return;
    }

    if (ui->ledit_account->text().isEmpty()) {
        QMessageBox::warning(this, localizationString("28"), localizationString("56"));
        return;
    }
    
    if (ui->sBox_passwordLengthMinimum->value()>ui->sBox_passwordLengthMaximum->value()) {
        QMessageBox::warning(this, localizationString("28"), localizationString("57"));
        return;
    }

    if (ui->sBox_passwordLengthMinimum->value()<6) {
        QMessageBox::warning(this, localizationString("28"), localizationString("60"));
        return;
    }

    if (ui->sBox_passwordLengthMaximum->value() > 20) {
        QMessageBox::warning(this, localizationString("28"), localizationString("61"));
        return;
    }

    auto portal=PortalAccountTable::getInstance();
    
    auto AccountName=portal->search_account(Platform().toStdString(),Account().toStdString() );
    if (!AccountName.accountName.empty()) {
        QMessageBox::warning(this, localizationString("21"), localizationString("58"));
    }
    else {
        m_password= portal->encrpyForUser(accountInfo(),ui->ledit_accountPlatform->text().toStdString() ); 
        this->accept();
    }
}

void DialogNewAccount::pbtn_cancel_clicked()
{
    this->reject();
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

std::string DialogNewAccount::Password()
{
    return m_password;
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
    result.password = m_password;

    return result;
}

void DialogNewAccount::cbox_phoneNumber_checked_change() {
    ui->ledit_phoneNumber->clear();
    ui->ledit_phoneNumber->setEnabled(ui->cbox_phoneNumber->isChecked());
}

