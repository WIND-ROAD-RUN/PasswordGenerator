#pragma once

#include <QtWidgets/QDialog>
#include "ui_DialogNewAccount.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DialogNewAccountClass; };
QT_END_NAMESPACE

class AccountInfo;
class LocalizationStringLoaderXML;

class DialogNewAccount 
    : public QDialog
{
    Q_OBJECT

public:
    DialogNewAccount(QWidget *parent = nullptr);
    ~DialogNewAccount();
private:
    Ui::DialogNewAccountClass *ui;
private:
    std::string m_password{};
private:
    /*使用的全局资源组件模块*/
    LocalizationStringLoaderXML* m_locstringLoader{ nullptr };
private:
    void build_ui();
    void build_connect();
    void build_languageString();
    void build_icon();
private:
    /*类配置设置相关的函数*/
    void ini_GlobaComponet();
private:
    /*提炼函数*/
    QIcon getIcon(const QString& fileName);
    QString localizationString(const std::string stringId);
private slots:
    void cbox_phoneNumber_checked_change();
    void cbox_user_checked_change();
    void pbtn_ok_clicked();
    void pbtn_cancel_clicked();
public:
    /*返回新增的账户信息*/
    QString Platform();
    QString Account();
    QString Phonenumber();
    QString User();
    std::pair<int,int> PasswordLength();
    bool haveSpecialSymbols();
    bool haveUpperLowerCase();
    bool isIrreversibleEncrpy();
    std::string Password();
    AccountInfo accountInfo();
};
