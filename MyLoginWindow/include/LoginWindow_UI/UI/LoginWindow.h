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
    LocalizationStringLoaderXML* m_locStCom{ nullptr };
    ConfigurationLoaderXML* m_cfgLoCom{ nullptr };
    AccountStoreSaveInXML* m_accountStore{ nullptr };
private:
    bool m_isMessageForClose{true};
public:
    LoginWindow(QWidget* parent = nullptr);
    ~LoginWindow();
private:
    virtual void closeEvent(QCloseEvent* event)override;
private:
    inline void build_ui();
    inline void build_connect();
    void build_icon();
    inline void set_label_accountPassError();
    inline void set_loginGroup();
    inline void set_WindowBackground();
    void setLanguageString(LocalizationStringLoaderXML* locStCom);
private:
    void ini_GlobaComponet();
    void check_configFile();
    void prepareForRun();
private:
    inline QString localizationString(const std::string stringId);
public:
    void setlocStCom(LocalizationStringLoaderXML* locStCom);
    void setConfigLoadCom(ConfigurationLoaderXML* cfgLoCom);
private slots:
    void pbtn_login_clicked();
    void label_AccountPassError_cancel();
    void pbtn_regist_clicked();
    void cBox_languageChanged_indexChanged();
    void cBox_savePassword_checkd();
    void cBox_LoginAuto_checked();
};
