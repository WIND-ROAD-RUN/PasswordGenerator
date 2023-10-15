#include <QtWidgets/QMainWindow>
#include "ui_LoginWindow.h"

class LocalizationStringLoaderXML;

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindowClass; };
QT_END_NAMESPACE

class PasswordGenerator;
class LocalizationStringLoaderXML;
class ConfigurationLoaderXML;

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(LocalizationStringLoaderXML* locStCom, ConfigurationLoaderXML* cfgLoCom,QWidget* parent = nullptr);
    ~LoginWindow();
private:
    Ui::LoginWindowClass* ui;
private:
    PasswordGenerator* generatorWindow{nullptr};
    LocalizationStringLoaderXML* m_locStCom{ nullptr };
    ConfigurationLoaderXML* m_cfgLoCom{nullptr};
private slots:
    void pbtn_login_clicked();
    void label_AccountPassError_cancel();
    void pbtn_regist_clicked();
    void cBox_languageChanged_indexChanged();
    void cBox_savePassword_checkd();
    void cBox_LoginAuto_checked();
private:
    virtual void closeEvent(QCloseEvent* event)override;
private:
    inline void build_ui();
    inline void build_connect();
    inline void set_label_accountPassError();
    inline void set_loginGroup();
    inline void set_WindowBackground();
    void setLanguageString(LocalizationStringLoaderXML* locStCom);
public:
    void setlocStCom(LocalizationStringLoaderXML* locStCom);
    void setConfigLoadCom(ConfigurationLoaderXML* cfgLoCom);
};
