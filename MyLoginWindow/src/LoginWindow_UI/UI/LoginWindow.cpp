#include "LoginWindow.h"

#include <QMessageBox>

#include<QCloseEvent>
#include<QString>
#include<QPainter>
#include<QDir>

#include<string>

#include"loginTransmit.h"
#include"DialogRegist.h"
#include"PasswordGenerator.h"
#include"LocalizationStringLoader-XML.h"
#include"ConfigurationLoader-XML.h"
#include"config.h"
#include"accountStoreSaveInXML.h"

LoginWindow::LoginWindow(QWidget* parent)
    : m_locStCom(LocalizationStringLoaderXML::getInstance()), m_cfgLoCom(ConfigurationLoaderXML::getInstance()), QMainWindow(parent)
    , ui(new Ui::LoginWindowClass()),m_accountStore(AccountStoreSaveInXML::getInstance())
{
    ui->setupUi(this);
    ini_GlobaComponet();
    check_configFile();
    prepareForRun();
    build_icon();
    build_ui();
    build_connect();
    this->setLanguageString(m_locStCom);
    this->setWindowFlag(Qt::WindowMinimizeButtonHint,true);
    this->setWindowFlag(Qt::WindowMaximizeButtonHint, false);
    this->setWindowFlag(Qt::CustomizeWindowHint, false);
    if (ui->cBox_LoginAuto->isChecked()) {
        this->pbtn_login_clicked();
    }

}

LoginWindow::~LoginWindow()
{
    delete ui;
    delete generatorWindow;
    //delete m_accountStore;
    //delete m_cfgLoCom;
    //delete m_locStCom;
}

void LoginWindow::setLanguageString(LocalizationStringLoaderXML* locStCom)
{
    ui->pbtn_login->setText(localizationString("1"));
    ui->pbtn_regist->setText(localizationString("2"));
    ui->label_password->setText(localizationString("6"));
    ui->label_account->setText(localizationString("5"));
    ui->cBox_LoginAuto->setText(localizationString("4"));
    ui->cBox_savePassword->setText(localizationString("3"));
    this->setWindowTitle(localizationString("1"));
    ui->label_accountPassError->setText(localizationString("7"));
    
}

void LoginWindow::ini_GlobaComponet()
{
    LocalizationStringLoaderXML::getInstance();
    ConfigurationLoaderXML::getInstance();
    AccountStoreSaveInXML::getInstance();
}

void LoginWindow::check_configFile()
{
    QString configPath = PROGRAMMEDATAPATH;
    QDir config;
    config.setPath(configPath);
    if (!config.exists()) {
        config.mkpath(configPath);
        config.mkdir("config");
        QFile fileConfig(CONFIGPATH);
        if (fileConfig.open(QFile::ReadWrite)) {
            fileConfig.close();
        }
        m_cfgLoCom->setNewfile(CONFIGPATH);

        QFile fileAccountTable(ACCOUNTTABLEPATH);
        if (fileAccountTable.open(QFile::ReadWrite)) {
            fileAccountTable.close();
        }
        auto accountSave=AccountStoreSaveInXML::getInstance();
        accountSave->setNewFile(ACCOUNTTABLEPATH);

        config.mkdir("database");
    }
}

void LoginWindow::prepareForRun()
{
    m_cfgLoCom->setFilePath(CONFIGPATH);
    m_cfgLoCom->loadConfig();
    auto curPath = QDir::currentPath();
    auto localizationString = curPath + "/localizationString.xml";
    m_locStCom->setFilePath(localizationString.toStdString());
    m_locStCom->setLanguage(m_cfgLoCom->Language());
    m_locStCom->loadData();

    auto accountSave = AccountStoreSaveInXML::getInstance();
    accountSave->setFilePath(ACCOUNTTABLEPATH);
    accountSave->ini_accountTable();
}

inline QString LoginWindow::localizationString(const std::string stringId)
{
    return QString(QString::fromStdString(m_locStCom->getString(stringId)));
}

void LoginWindow::setlocStCom(LocalizationStringLoaderXML* locStCom)
{
    m_locStCom = locStCom;
}

void LoginWindow::setConfigLoadCom(ConfigurationLoaderXML* cfgLoCom)
{
    m_cfgLoCom = cfgLoCom;
}

void LoginWindow::build_ui()
{
    set_WindowBackground();
    set_label_accountPassError();
    set_loginGroup();
    auto language = m_cfgLoCom->Language();
    if (language == "CHN") {
        ui->cBox_languageChange->setCurrentIndex(0);
    }
    else if (language == "USA") {
        ui->cBox_languageChange->setCurrentIndex(1);
    }
    ui->cBox_savePassword->setChecked(m_cfgLoCom->isRememberPassword());
    if (ui->cBox_savePassword->isChecked()) {
        ui->cBox_LoginAuto->setChecked(m_cfgLoCom->isAutoLogin());
        ui->cBox_LoginAuto->setEnabled(true);
    }
    else {
        ui->cBox_LoginAuto->setEnabled(false);
    }
    ui->ledit_account->setText(QString::fromStdString(m_cfgLoCom->LastLoginAccount().first));
    if (m_cfgLoCom->isRememberPassword()) {
        ui->lEdit_password->setText(QString::fromStdString(m_cfgLoCom->LastLoginAccount().second));
    }
    
}

inline void LoginWindow::build_connect()
{
    QObject::connect(ui->pbtn_login, SIGNAL(clicked()), this, SLOT(pbtn_login_clicked()));
    QObject::connect(ui->pbtn_regist, SIGNAL(clicked()), this, SLOT(pbtn_regist_clicked()));
    QObject::connect(ui->ledit_account, &QLineEdit::textChanged, this, &LoginWindow::label_AccountPassError_cancel);
    QObject::connect(ui->lEdit_password, &QLineEdit::textChanged, this, &LoginWindow::label_AccountPassError_cancel);
    QObject::connect(ui->cBox_languageChange,&QComboBox::currentIndexChanged,this,&LoginWindow::cBox_languageChanged_indexChanged);
    QObject::connect(ui->cBox_savePassword,&QCheckBox::stateChanged,this,&LoginWindow::cBox_savePassword_checkd);
    QObject::connect(ui->cBox_LoginAuto, &QCheckBox::stateChanged, this, &LoginWindow::cBox_LoginAuto_checked);
}

void LoginWindow::build_icon()
{
    this->setWindowIcon(QIcon(":/LoginWindow/icon/key.png"));
}

void LoginWindow::closeEvent(QCloseEvent* event)
{
    if (m_isMessageForClose) {
        QMessageBox::StandardButton result =
            QMessageBox::question(this,
                QString::fromStdString(m_locStCom->getString("14")),
                QString::fromStdString(m_locStCom->getString("15")));
        if (result == QMessageBox::Yes) {
            event->accept();
        }
        else {
            event->ignore();
        }
    }
}

inline void LoginWindow::set_label_accountPassError()
{
    QPalette plet = ui->label_accountPassError->palette();
    plet.setColor(QPalette::WindowText, Qt::red);
    ui->label_accountPassError->setPalette(plet);
    ui->label_accountPassError->setVisible(false);
}

inline void LoginWindow::set_loginGroup()
{
    QFont font = ui->label_account->font();
    font.setBold(true);
    ui->label_account->setFont(font);
    ui->label_password->setFont(font);
    ui->pbtn_login->setFont(font);
    ui->pbtn_regist->setFont(font);
    ui->cBox_LoginAuto->setFont(font);
    ui->cBox_savePassword->setFont(font);
    ui->ledit_account->setText("");
    ui->lEdit_password->setText("");
}

inline void LoginWindow::set_WindowBackground()
{
    ui->ptEdit_picture->appendPlainText(QDir::currentPath());
    ui->ptEdit_accountIcon->appendPlainText("这里显示用户图标");

    QFont textFont = ui->ptEdit_picture->font();
    textFont.setPointSize(20);
    ui->ptEdit_accountIcon->setFont(textFont);

    textFont.setPointSize(20);
    ui->ptEdit_picture->setFont(textFont);
    ui->ptEdit_accountIcon->setEnabled(false);
    ui->ptEdit_picture->setEnabled(false);
}

void LoginWindow::pbtn_login_clicked() {
    LoginTransmit* login = new LoginTransmit(ui->ledit_account->text().toStdString(),
        ui->lEdit_password->text().toStdString());

    if (login->isLoginSuccess()) {
        if (!generatorWindow) { generatorWindow = new PasswordGenerator(); }
        auto UID = ui->ledit_account->text();
        

        std::string filtPath = std::string(DATABASEPATH) + std::string(R"(\)") + UID.toStdString()+std::string(".xml");
        generatorWindow->set_UID(UID.toStdString());
        generatorWindow->build_icon(QIcon(":/LoginWindow/icon/data-display.png"));
        generatorWindow->set_filePath(filtPath);
        generatorWindow->ini_config();

        m_cfgLoCom->setLastLoginAccount(ui->ledit_account->text().toStdString(),
            ui->lEdit_password->text().toStdString());

        m_cfgLoCom->storeConfig();

        m_isMessageForClose = false;
        this->close();

        generatorWindow->show();
    }
    else {
        ui->label_accountPassError->setVisible(true);
    }


    delete login;


}

void LoginWindow::label_AccountPassError_cancel() {
    ui->label_accountPassError->setVisible(false);
}

void LoginWindow::pbtn_regist_clicked() {
    DialogRegist* dlgRegist = new DialogRegist(this);
    dlgRegist->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    int ret = dlgRegist->exec();
    if (ret == QDialog::Accepted) {
        QMessageBox::information(this, 
            localizationString("16"),
            localizationString("16"));
        return;
    }
    else {
        return;
    }
    delete dlgRegist;
}

void LoginWindow::cBox_languageChanged_indexChanged()
{
    auto index = ui->cBox_languageChange->currentIndex();
    switch (index) {
    case 0 :
        if (m_cfgLoCom->Language()==std::string("CHN")) {
            break;
        }
        else {
            m_cfgLoCom->setLocalLanguage("CHN");
            m_cfgLoCom->storeConfig();
            m_locStCom->setLanguage("CHN");
            m_locStCom->loadData();
            this->setLanguageString(m_locStCom);
            break;
        }
    case 1:
        if (m_cfgLoCom->Language() == std::string("USA")) {
            break;
        }
        else {
            m_cfgLoCom->setLocalLanguage("USA");
            m_cfgLoCom->storeConfig();
            m_locStCom->setLanguage("USA");
            m_locStCom->loadData();
            this->setLanguageString(m_locStCom);
            break;
        }
    }

}

void LoginWindow::cBox_savePassword_checkd()
{
    bool isSavePassword= ui->cBox_savePassword->isChecked();
    if (isSavePassword) {
        ui->cBox_LoginAuto->setEnabled(true);
    }
    else {
        ui->cBox_LoginAuto->setEnabled(false);
        ui->cBox_LoginAuto->setChecked(false);
        m_cfgLoCom->set_isAutoLogin(false);
    }
    m_cfgLoCom->set_isRememberPassword(isSavePassword);
    m_cfgLoCom->storeConfig();
    
}

void LoginWindow::cBox_LoginAuto_checked()
{
    m_cfgLoCom->set_isAutoLogin(ui->cBox_LoginAuto->isChecked());
    m_cfgLoCom->storeConfig();
}
