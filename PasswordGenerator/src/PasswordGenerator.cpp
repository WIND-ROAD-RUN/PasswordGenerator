#include "PasswordGenerator.h"

#include"PortalAccountTable.h"

#include<QStandardItemModel>
#include<QItemSelectionModel>

#define PATH R"(G:\project\code_place\vs_code_place\MyPasswordGenerator1\PasswordGenerator\database\AccountTable.xml)"

PasswordGenerator::PasswordGenerator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PasswordGeneratorClass())
{
    ui->setupUi(this);
    build_ui();

}

PasswordGenerator::~PasswordGenerator()
{
    delete ui;
    delete m_model;
    delete m_selection;
    delete m_portalAccountTable;
}

void PasswordGenerator::build_ui()
{
    m_model = new QStandardItemModel(this);
    m_selection = new QItemSelectionModel(m_model, this);
    m_portalAccountTable = PortalAccountTable::getInstance();

    m_portalAccountTable->setFilePath(PATH);
    m_portalAccountTable->setUID("root");
    m_portalAccountTable->ini_portal();

    build_model();
    ui->tableView->setModel(m_model);
    ui->tableView->setSelectionModel(m_selection);
    ui->treeView->setModel(m_model);

}

void PasswordGenerator::update_ui()
{
  
}

void PasswordGenerator::build_model()
{
    auto root = m_model->invisibleRootItem();

    /*设置平台节点*/
    auto  platformList = m_portalAccountTable->PlatformList();
    for (const auto & platform: platformList) {
        QStandardItem* platforItem = new QStandardItem();
        platforItem->setText(QString::fromStdString(platform));
        auto accountList=m_portalAccountTable->AccountList(platform);
        for (const auto & account:accountList) {
            QStandardItem* accountItem = new QStandardItem();
            accountItem->setText(QString::fromStdString(account.accountName));

            QStandardItem* passwordItem = new QStandardItem();
            passwordItem->setText(QString::fromStdString(account.password));
            accountItem->appendRow(passwordItem);

            QStandardItem* phoneNumberItem = new QStandardItem();
            phoneNumberItem->setText(QString::fromStdString(account.phoneNumber));
            accountItem->appendRow(phoneNumberItem);

            QStandardItem* UserItem = new QStandardItem();
            UserItem->setText(QString::fromStdString(account.User));
            accountItem->appendRow(UserItem);

            QStandardItem* EncrpyIsIrreversibleItem = new QStandardItem();
            accountItem->appendRow(EncrpyIsIrreversibleItem);
            if (account.EncrpyIsIrreversible) {
                EncrpyIsIrreversibleItem->setText("是");
            }
            else {
                EncrpyIsIrreversibleItem->setText("否");
            }

            QStandardItem* haveSpecialSymbolsItem = new QStandardItem();
            accountItem->appendRow(haveSpecialSymbolsItem);
            if (account.haveSpecialSymbols) {
                haveSpecialSymbolsItem->setText("是");
            }
            else {
                haveSpecialSymbolsItem->setText("否");
            }

            QStandardItem* haveUppercaseLowercaseItem = new QStandardItem();
            accountItem->appendRow(haveUppercaseLowercaseItem);
            if (account.haveUppercaseLowercase) {
                haveUppercaseLowercaseItem->setText("是");
            }
            else {
                haveUppercaseLowercaseItem->setText("否");
            }


            platforItem->appendRow(accountItem);

        }
        root->appendRow(platforItem);
    }
    

}
