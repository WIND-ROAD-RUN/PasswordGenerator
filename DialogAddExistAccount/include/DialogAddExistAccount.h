#pragma once

#include <QtWidgets/QDialog>
#include "ui_DialogAddExistAccount.h"
#include<string>

QT_BEGIN_NAMESPACE
namespace Ui { class DialogAddExistAccountClass; };
QT_END_NAMESPACE

class AccountInfo;
class LocalizationStringLoaderXML;

class DialogAddExistAccount : public QDialog
{
    Q_OBJECT

public:
    DialogAddExistAccount(QWidget *parent = nullptr);
    ~DialogAddExistAccount();

private:
    Ui::DialogAddExistAccountClass *ui;
private:
    std::string m_filePath;
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
    void pbtn_cancel_clicked();
    void pbtn_ok_clicked();
public:
    void set_filePath(const std::string& filePath) { m_filePath = filePath; }
    QString Platform() { return ui->ledit_platform->text(); }
    QString Password() { return ui->ledit_password->text(); }
    QString Account() { return ui->ledit_account->text(); }
    AccountInfo accountInfo();
};
