#include "DialogAddExistAccount.h"
#include"PortalAccountTable.h"
#include"LocalizationStringLoader-XML.h"

#include<QMessageBox>
#include<QDir>

DialogAddExistAccount::DialogAddExistAccount(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogAddExistAccountClass())
{
    ui->setupUi(this);
    ini_GlobaComponet();

    build_languageString();
    build_connect();
    build_ui();
    build_icon();

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
    QObject::connect(ui->pbtn_cancel,&QPushButton::clicked,
        this,&DialogAddExistAccount::pbtn_cancel_clicked);

    QObject::connect(ui->pbtn_ok, &QPushButton::clicked, 
        this, &DialogAddExistAccount::pbtn_ok_clicked);
}

void DialogAddExistAccount::build_languageString()
{
    ui->label_platform->setText(localizationString("53")+":");
    ui->label_account->setText(localizationString("54") + ":");
    ui->label_password->setText(localizationString("59") + ":");

    ui->pbtn_ok->setText(localizationString("11"));
    ui->pbtn_cancel->setText(localizationString("12"));

    this->setWindowTitle(localizationString("40"));
}

void DialogAddExistAccount::build_icon()
{
    this->setWindowIcon(getIcon("edit-name.png"));
}

QIcon DialogAddExistAccount::getIcon(const QString& fileName)
{
    auto cutDir = QDir::currentPath();
    auto filePath = cutDir + "/icon/" + fileName;
    return QIcon(filePath);
}

void DialogAddExistAccount::ini_GlobaComponet()
{
    m_locstringLoader = LocalizationStringLoaderXML::getInstance();
}

QString DialogAddExistAccount::localizationString(const std::string stringId)
{
    return QString(QString::fromStdString(m_locstringLoader->getString(stringId)));
}

void DialogAddExistAccount::pbtn_ok_clicked()
{
    if (ui->ledit_platform->text().isEmpty()) {
        QMessageBox::warning(this, localizationString("28"), localizationString("55"));
        return;
    }

    if (ui->ledit_account->text().isEmpty()) {
        QMessageBox::warning(this, localizationString("28"), localizationString("56"));
        return;
    }
    
    auto portal = PortalAccountTable::getInstance();

    auto AccountName = portal->search_account(Platform().toStdString(), Account().toStdString());
    if (!AccountName.accountName.empty()) {
        QMessageBox::warning(this, localizationString("21"), localizationString("58"));
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