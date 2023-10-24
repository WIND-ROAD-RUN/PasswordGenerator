#include "PasswordGenerator.h"

#include"PortalAccountTable.h"
#include"DialogNewAccount.h"

#include<QStandardItemModel>
#include<QItemSelectionModel>
#include<QTreeView>
#include<QSortFilterProxyModel>
#include<QMessagebox>

PasswordGenerator::PasswordGenerator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PasswordGeneratorClass())
{
    ui->setupUi(this);
    build_ui();
    build_connect();
}

PasswordGenerator::~PasswordGenerator()
{
    delete ui;
    delete m_treeModel;
    delete m_treeSelection;
    delete m_portalAccountTable;
}

void PasswordGenerator::build_ui()
{
    m_treeModel = new QStandardItemModel(this);
    m_tableModel = new QStandardItemModel(this);
    m_treeSelection = new QItemSelectionModel(m_treeModel, this);

    m_portalAccountTable = PortalAccountTable::getInstance();

    m_portalAccountTable->setFilePath(m_filePath);
    m_portalAccountTable->setUID("root");
    m_portalAccountTable->ini_portal();

    ui->tableView->setModel(m_tableModel);

    ui->treeView->setSelectionModel(m_treeSelection);
    ui->treeView->setModel(m_treeModel);

    build_tree_model();
    build_table_model_all_account();

}

void PasswordGenerator::build_connect()
{
    QObject::connect(ui->treeView,&QTreeView::clicked, this, &PasswordGenerator::build_treeSelectChange_for_table);
    QObject::connect(ui->act_storeNewAccount,&QAction::triggered,this,&PasswordGenerator::act_newAccount_trigger);
    QObject::connect(ui->pbtn_storeNewAccount,&QPushButton::clicked,ui->act_storeNewAccount,&QAction::trigger);
    QObject::connect(ui->act_saveInfo,&QAction::triggered,this,&PasswordGenerator::act_saveInfo_trigger);
    QObject::connect(ui->pbtn_saveInfo,&QPushButton::clicked,ui->act_saveInfo,&QAction::trigger);
    QObject::connect(ui->act_displayAllAccount,&QAction::triggered,this,&PasswordGenerator::act_displayAllAccount_trigger);
    QObject::connect(ui->pbtn_displayAllAccount,&QPushButton::clicked,ui->act_displayAllAccount, &QAction::trigger);
}


void PasswordGenerator::build_tree_model()
{
    m_treeModel->clear();
    auto root = m_treeModel->invisibleRootItem();

    /*节点*/
    auto  platformList = m_portalAccountTable->PlatformList();
    for (const auto & platform: platformList) {
        QStandardItem* platforItem = new QStandardItem();
        platforItem->setText(QString::fromStdString(platform));
        platforItem->setData("platform", Qt::UserRole);
        auto accountList=m_portalAccountTable->AccountList(platform);
        for (const auto & account:accountList) {
            QStandardItem* accountItem = new QStandardItem();
            accountItem->setData("account", Qt::UserRole);
            accountItem->setText(QString::fromStdString(account.accountName));
            ui->treeView->setExpanded(accountItem->index(), true);
            accountItem->setEditable(false);

            platforItem->appendRow(accountItem);

        }

        root->appendRow(platforItem);
        ui->treeView->setExpanded(platforItem->index(),true);
        platforItem->setEditable(false);
    }
    m_treeSelection->clearSelection();
}

void PasswordGenerator::build_treeSelectChange_for_table(const QModelIndex& index) {
    m_tableModel->clear();
    
    auto NodeType = m_treeModel->itemFromIndex(index);
    
    QStringList headerList;
    headerList.push_back("平台");
    headerList.push_back("账户名");
    headerList.push_back("密码");
    headerList.push_back("是否为可逆加密");
    m_tableModel->setColumnCount(headerList.size());
    m_tableModel->setHorizontalHeaderLabels(headerList);

    if (NodeType->data(Qt::UserRole)=="platform") {
        auto platfromName = NodeType->text();
        auto accountList=m_portalAccountTable->AccountList(platfromName.toStdString());
        int i = 0;
        for (const auto & account:accountList) {
            add_account_forTable(account, platfromName,i);
            i++;
        }
    }
    else if(NodeType->data(Qt::UserRole) == "account") {
        auto accountName= NodeType->text();
        auto platform=NodeType->parent();
        auto account=m_portalAccountTable->search_account(platform->text().toStdString(),accountName.toStdString());
        
        add_account_forTable(account,platform->text(),0);
    }

    
}

void PasswordGenerator::build_table_model_all_account()
{
    m_tableModel->clear();
    m_row = m_portalAccountTable->AccountNumber();
    m_tableModel->setRowCount(m_row);

    QStringList headerList;
    headerList.push_back("平台");
    headerList.push_back("账户名");
    headerList.push_back("密码");
    headerList.push_back("是否为可逆加密");
    m_tableModel->setColumnCount(headerList.size());
    m_tableModel->setHorizontalHeaderLabels(headerList);

    int i{0};
    auto platformList = m_portalAccountTable->PlatformList();
    for (const auto & platform: platformList){
        auto accountList = m_portalAccountTable->AccountList(platform);
        for (const auto & account: accountList) {
            add_account_forTable(account,QString::fromStdString(platform),i);
            i++;
        }
    }
}

void PasswordGenerator::add_account_forTable(const AccountInfo& account, const QString& platform, int row)
{
    QStandardItem* platformItem = new QStandardItem;
    platformItem->setText(platform);
    platformItem->setEditable(false);
    m_tableModel->setItem(row, 0, platformItem);

    QStandardItem* accountNameItem = new QStandardItem;
    accountNameItem->setText(QString::fromStdString(account.accountName));
    accountNameItem->setEditable(false);
    m_tableModel->setItem(row, 1, accountNameItem);

    QStandardItem* passwordItem = new QStandardItem;
    passwordItem->setText(QString::fromStdString(account.password));
    passwordItem->setEditable(false);
    m_tableModel->setItem(row, 2, passwordItem);

    QStandardItem* EncrpyIsIrreversibleItem = new QStandardItem;
    if (account.EncrpyIsIrreversible) {
        EncrpyIsIrreversibleItem->setText(QString::fromStdString("是"));
    }
    else {
        EncrpyIsIrreversibleItem->setText(QString::fromStdString("否"));
    }
    EncrpyIsIrreversibleItem->setEditable(false);
    m_tableModel->setItem(row, 3, EncrpyIsIrreversibleItem);

}

void PasswordGenerator::act_newAccount_trigger()
{
    m_DlgNewAccount = new DialogNewAccount(this);
    int ret=m_DlgNewAccount->exec();
    if (ret==QDialog::Rejected) {
        return;
    }
    auto NewAccount=m_DlgNewAccount->accountInfo();
    auto NewAccountRet=m_portalAccountTable->newAccount(m_DlgNewAccount->Platform().toStdString(),NewAccount);
    if (NewAccountRet ==ErrorAccountTableModule::NoPlatformNode) {
        m_portalAccountTable->newPlatform(m_DlgNewAccount->Platform().toStdString());
        m_portalAccountTable->newAccount(m_DlgNewAccount->Platform().toStdString(), NewAccount);
    }
    delete m_DlgNewAccount;

    build_tree_model();
    
}

void PasswordGenerator::act_saveInfo_trigger()
{
    auto saveRet = m_portalAccountTable->save_change();
    if (saveRet!=ErrorAccountTableModule::No_ERROR) {
        QMessageBox::warning(this,"错误","保存文件错误");
    }
    else {
        QMessageBox::information(this,"成功","数据已保存");
    }

}

void PasswordGenerator::act_displayAllAccount_trigger()
{
    build_table_model_all_account();
}

