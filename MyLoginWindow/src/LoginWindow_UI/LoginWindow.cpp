#include "LoginWindow.h"
#include <QMessageBox>
#include<QCloseEvent>
#include"loginTransmit.h"
#include<QString>
#include"DialogRegist.h"
#include<QPainter>
#include"PasswordGenerator.h"

LoginWindow::LoginWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindowClass())
{
    ui->setupUi(this);
    build_ui();
    build_connect();
    this->setWindowFlag(Qt::WindowMinimizeButtonHint,true);
    this->setWindowFlag(Qt::WindowMaximizeButtonHint, false);
    this->setWindowFlag(Qt::CustomizeWindowHint, false);
    this->setWindowTitle(QString("登录"));
}

LoginWindow::~LoginWindow()
{
    delete ui;
    delete generatorWindow;
}

void LoginWindow::build_ui()
{
    set_WindowBackground();
    set_label_accountPassError();
    set_loginGroup();
}

inline void LoginWindow::build_connect()
{
    QObject::connect(ui->pbtn_login, SIGNAL(clicked()), this, SLOT(pbtn_login_clicked()));
    QObject::connect(ui->pbtn_regist, SIGNAL(clicked()), this, SLOT(pbtn_regist_clicked()));
    QObject::connect(ui->ledit_account, &QLineEdit::textChanged, this, &LoginWindow::label_AccountPassError_cancel);
    QObject::connect(ui->lEdit_password, &QLineEdit::textChanged, this, &LoginWindow::label_AccountPassError_cancel);

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
    DialogRegist* dlgRegist = new DialogRegist(this);
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