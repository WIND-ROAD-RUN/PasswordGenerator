#include "LoginWindow.h"
#include <QMessageBox>
#include<QCloseEvent>
#include"loginTransmit.h"
#include<QString>
#include"DialogRegist.h"
#include<QPainter>
#include"PasswordGenerator.h"
#include"LocalizationStringLoader-XML.h"
#include"ConfigurationLoader-XML.h"
#include<string>

LoginWindow::LoginWindow(LocalizationStringLoaderXML* locStCom, ConfigurationLoaderXML* cfgLoCom,QWidget* parent)
    : m_locStCom(locStCom), m_cfgLoCom(cfgLoCom), QMainWindow(parent)
    , ui(new Ui::LoginWindowClass())
{
    ui->setupUi(this);
    build_ui();
    build_connect();
    this->setLanguageString(m_locStCom);
    this->setWindowFlag(Qt::WindowMinimizeButtonHint,true);
    this->setWindowFlag(Qt::WindowMaximizeButtonHint, false);
    this->setWindowFlag(Qt::CustomizeWindowHint, false);
}

LoginWindow::~LoginWindow()
{
    delete ui;
    delete generatorWindow;
}

void LoginWindow::setLanguageString(LocalizationStringLoaderXML* locStCom)
{
    ui->pbtn_login->setText(QString::fromStdString(locStCom->getString("1")));
    ui->pbtn_regist->setText(QString::fromStdString(locStCom->getString("2")));
    ui->label_password->setText(QString::fromStdString(locStCom->getString("6")));
    ui->label_account->setText(QString::fromStdString(locStCom->getString("5")));
    ui->cBox_LoginAuto->setText(QString::fromStdString(locStCom->getString("4")));
    ui->cBox_savePassword->setText(QString::fromStdString(locStCom->getString("3")));
    this->setWindowTitle(QString::fromStdString(locStCom->getString("1")));
    ui->label_accountPassError->setText(QString::fromStdString(locStCom->getString("7")));
    
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
}

inline void LoginWindow::build_connect()
{
    QObject::connect(ui->pbtn_login, SIGNAL(clicked()), this, SLOT(pbtn_login_clicked()));
    QObject::connect(ui->pbtn_regist, SIGNAL(clicked()), this, SLOT(pbtn_regist_clicked()));
    QObject::connect(ui->ledit_account, &QLineEdit::textChanged, this, &LoginWindow::label_AccountPassError_cancel);
    QObject::connect(ui->lEdit_password, &QLineEdit::textChanged, this, &LoginWindow::label_AccountPassError_cancel);
    QObject::connect(ui->cBox_languageChange,&QComboBox::currentIndexChanged,this,&LoginWindow::cBox_languageChanged_indexChanged);
}

void LoginWindow::closeEvent(QCloseEvent* event)
{
    QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "真的要退出登录器么？");
    if (result == QMessageBox::Yes) {
        event->accept();
    }
    else {
        event->ignore();
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
    ui->ptEdit_picture->appendPlainText("这里显示程序左侧图形界面");
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
    DialogRegist* dlgRegist = new DialogRegist(m_locStCom,this);
    dlgRegist->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    int ret = dlgRegist->exec();
    if (ret == QDialog::Accepted) {
        QMessageBox::information(this, "注册成功", "注册成功");
        return;
    }
    else {
        return;
    }
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