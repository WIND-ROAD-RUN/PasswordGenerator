#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LocalizationStringManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LocalizationStringManagerClass; };
QT_END_NAMESPACE

class LocalizationStringXML;
class LocalizationStringManager : public QMainWindow
{
    Q_OBJECT
public:
    LocalizationStringManager(QWidget *parent = nullptr);
    ~LocalizationStringManager();
private:
    Ui::LocalizationStringManagerClass *ui;
private:
    /*使用的全局资源组件模块*/
    LocalizationStringXML* localStringComponet{nullptr};
private:
    QString m_filePath{};
private:
    void build_connect();
    void build_ui();
private:
    /*重写的父类函数*/
    virtual void closeEvent(QCloseEvent* event)override;
private slots:
    void pbtn_openFile_clicked();
    void pbtn_search_clicked();
    void pbtn_store_clicked();
    void pbtn_saveData_clicked();
};
