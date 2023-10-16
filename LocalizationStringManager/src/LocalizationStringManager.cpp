#include "LocalizationStringManager.h"

#include <QFileDialog>
#include<QEvent>
#include<QCloseEvent>
#include<QMessageBox>

#include<string>

#include"LocalizationStringModule-XML.h"



LocalizationStringManager::LocalizationStringManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LocalizationStringManagerClass())
{
    ui->setupUi(this);
    build_connect();
    build_ui();
}

LocalizationStringManager::~LocalizationStringManager()
{
    delete ui;
}

void LocalizationStringManager::build_connect()
{
    QObject::connect(ui->pbtn_openFile,&QPushButton::clicked,this,&LocalizationStringManager::pbtn_openFile_clicked);
    QObject::connect(ui->pbtn_search,&QPushButton::clicked,this,&LocalizationStringManager::pbtn_search_clicked);
    QObject::connect(ui->pbtn_store, &QPushButton::clicked, this, &LocalizationStringManager::pbtn_store_clicked);
    QObject::connect(ui->pbtn_saveData, &QPushButton::clicked, this, &LocalizationStringManager::pbtn_saveData_clicked);
}

void LocalizationStringManager::build_ui()
{
    ui->frame_search->setEnabled(false);
    ui->frame_store->setEnabled(false);
    ui->ledit_filePath->setEnabled(false);
    ui->pbtn_saveData->setEnabled(false);
}

void LocalizationStringManager::closeEvent(QCloseEvent* event)
{
    QMessageBox::StandardButton result = QMessageBox::question(this, "数据可能还未保存", "是否要保存并退出？");
    if (result == QMessageBox::Yes) {
        this->pbtn_saveData_clicked();
        event->accept();
    }
    else {
        event->accept();
    }
}

void LocalizationStringManager::pbtn_search_clicked()
{
    ui->ledit_search_result->clear();
    if (!localStringComponet) {
        localStringComponet = new LocalizationStringXML(m_filePath.toStdString());
        localStringComponet->loadFile();
    }
    std::string s;
    bool result=localStringComponet->localString
                (s,
                 ui->ledit_search_id->text().toStdString(),
                 ui->cBox_search_local->currentText().toStdString());
    if (!result) {
        QMessageBox::warning(this,"错误","未查询到该字符串");
    }
    else {
        ui->ledit_search_result->setText(QString::fromStdString(s));
    }

}

void LocalizationStringManager::pbtn_store_clicked()
{
    if (!localStringComponet) {
        localStringComponet = new LocalizationStringXML(m_filePath.toStdString());
        localStringComponet->loadFile();
    }
    bool result = localStringComponet->storeLocalString
                    (ui->ledit_store_id->text().toStdString(),
                        ui->cBox_store_local->currentText().toStdString(),
                        ui->ledit_store_string->text().toStdString());
    if (!result) {
        QMessageBox::warning(this,"错误","已有相同属性的字符串，如果要更改，请使用更改区域进行更改");
    }
    else {
        QMessageBox::information(this,"成功","已提交你输入的字符串");
    }
}

void LocalizationStringManager::pbtn_saveData_clicked()
{
    if (localStringComponet->saveFile()) {
        QMessageBox::information(this,"成功","已将数据保存到文件中");
    }
    else {
        QMessageBox::warning(this, "错误", "未知错误，数据保存失败");
    }
}

void LocalizationStringManager::pbtn_openFile_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this,"选择一个XML数据文件",QDir::currentPath(),"数据文件(*.xml)");
    if (!fileName.isEmpty()) {
        m_filePath = fileName;
        ui->ledit_filePath->setText(fileName);
        ui->frame_search->setEnabled(true);
        ui->frame_store->setEnabled(true);
        ui->pbtn_saveData->setEnabled(true);
    }
}

