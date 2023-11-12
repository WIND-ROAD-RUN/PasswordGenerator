#pragma once

#include "ui_LoginWindow.h"
#include <QtWidgets/QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindowClass; };
QT_END_NAMESPACE

class PasswordGenerator;
class LocalizationStringLoaderXML;
class ConfigurationLoaderXML;
class AccountStoreSaveInXML;

class LoginWindow 
    : public QMainWindow
{
    Q_OBJECT
private:
    Ui::LoginWindowClass* ui;

private:
    PasswordGenerator* generatorWindow{ nullptr };

private:
    LocalizationStringLoaderXML* m_locStCom{ nullptr };

    ConfigurationLoaderXML* m_cfgLoCom{ nullptr };

    AccountStoreSaveInXML* m_accountStore{ nullptr };

private:
    bool m_isMessageForClose{true};

public:
    LoginWindow(QWidget* parent = nullptr);

    ~LoginWindow();

private:
    /*ui使用前准备*//*应该找这个接口顺序使用确保ui使用前的正确准备的工作的进行*/
    void ini_GlobaComponet();

    void check_configFile();

    void prepareForRun();

private:
    /*重载父类接口*/
    virtual void closeEvent(QCloseEvent* event)override;

private:
    /*生成ui*/
    void build_ui();

    void build_connect();

    void build_icon();

    QIcon getIcon(const QString & fileName);

    void build_languageString();

    /*设置ui*/
    void set_label_accountPassError();

    void set_loginGroup();

    void set_WindowBackground();

private:
    /*提炼函数如下*/
    QString localizationString(const std::string stringId);

private slots:
    void pbtn_login_clicked();

    void pbtn_regist_clicked();

    void cBox_languageChanged_indexChanged();

    void cBox_savePassword_checkd();

    void cBox_LoginAuto_checked();

    void label_AccountPassError_cancel();

};
