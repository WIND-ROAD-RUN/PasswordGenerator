#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LoginWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindowClass; };
QT_END_NAMESPACE

class LoginTransmit;

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget* parent = nullptr);
    ~LoginWindow();

private:
    Ui::LoginWindowClass* ui;
    LoginTransmit* m_login;


private slots:
    void pbtn_login_clicked();
    void label_AccountPassError_cancel();
    void pbtn_regist_clicked();
private:
    inline void build_ui();
    inline void build_connect();
    void closeEvent(QCloseEvent* event);
    inline void  set_label_accountPassError();
    inline void set_loginGroup();
    inline void set_WindowBackground();
};
