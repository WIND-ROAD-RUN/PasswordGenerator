#pragma once

#include <QtWidgets/QDialog>
#include "ui_DialogAddExistAccount.h"
#include<string>

QT_BEGIN_NAMESPACE
namespace Ui { class DialogAddExistAccountClass; };
QT_END_NAMESPACE

class AccountInfo;
class LocalizationStringLoaderXML;

class DialogAddExistAccount 
    : public QDialog
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
    /*使用的全局资源组件模块*/
    LocalizationStringLoaderXML* m_locstringLoader{ nullptr };
private:
    void build_ui();
    void build_connect();
    void build_languageString();
    void build_icon();
private:
    /*类配置加载相关函数*/
    void ini_GlobaComponet();
private:
    /*提炼函数*/
    QIcon getIcon(const QString& fileName);
    QString localizationString(const std::string stringId);
private slots:
    void pbtn_cancel_clicked();
    void pbtn_ok_clicked();
public:
    /*类配置设置相关函数*/
    void set_filePath(const std::string& filePath) { m_filePath = filePath; }
public:
    /*取得添加账户的信息*/
    QString Platform() { return ui->ledit_platform->text(); }
    QString Password() { return ui->ledit_password->text(); }
    QString Account() { return ui->ledit_account->text(); }
    AccountInfo accountInfo();
};
