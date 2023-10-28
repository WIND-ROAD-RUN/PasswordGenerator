#pragma once

#include <QtWidgets/QDialog>
#include "ui_DialogNewAccount.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DialogNewAccountClass; };
QT_END_NAMESPACE

class AccountInfo;
class LocalizationStringLoaderXML;

class DialogNewAccount : public QDialog
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
    LocalizationStringLoaderXML* m_locstringLoader{ nullptr };
private:
    void build_ui();
    void build_connect();
    void build_languageString();
    void build_icon();
    QIcon getIcon(const QString& fileName);
private:
    void ini_GlobaComponet();
private:
    inline QString localizationString(const std::string stringId);
private slots:
    void cbox_phoneNumber_checked_change();
    void cbox_user_checked_change();
    void pbtn_ok_clicked();
    void pbtn_cancel_clicked();
public:
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
