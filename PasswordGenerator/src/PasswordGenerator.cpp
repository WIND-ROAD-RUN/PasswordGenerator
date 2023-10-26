#include "PasswordGenerator.h"

#include"PortalAccountTable.h"
#include"DialogNewAccount.h"
#include"DialogAddExistAccount.h"

#include<QStandardItemModel>
#include<QItemSelectionModel>
#include<QTreeView>
#include<QSortFilterProxyModel>
#include<QMessagebox>
#include<QContextMenuEvent>
#include<QDir>

PasswordGenerator::PasswordGenerator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PasswordGeneratorClass())
{
    ui->setupUi(this);
    
}

PasswordGenerator::~PasswordGenerator()
{
    delete ui;
    delete m_treeModel;
    delete m_treeSelection;
    delete m_portalAccountTable;
    delete m_menu;
}

void PasswordGenerator::build_ui()
{
    m_treeModel = new QStandardItemModel(this);
    m_tableModel = new QStandardItemModel(this);
    m_treeSelection = new QItemSelectionModel(m_treeModel, this);
    m_menu = new QMenu(this);
    m_menu->addAction(ui->act_deleteNode);

    m_portalAccountTable->setUID(m_UID);

    m_portalAccountTable->setFilePath(m_filePath);
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
    QObject::connect(ui->act_storeExistAccount,&QAction::triggered,this,&PasswordGenerator::act_storeExistAccount_trigger);
    QObject::connect(ui->pbtn_storeExistAccount,&QPushButton::clicked,ui->act_storeExistAccount,&QAction::triggered);
    QObject::connect(ui->act_deleteNode,&QAction::triggered,this,&PasswordGenerator::act_deleteNode_trigger);
}

void PasswordGenerator::ini_config()
{
    ini_GlobaComponet();
    check_filePath();
    build_ui();
    build_connect();
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

void PasswordGenerator::contextMenuEvent(QContextMenuEvent* event)
{

    auto selectedIndexes = ui->treeView->selectionModel()->selectedIndexes();
    if (selectedIndexes.size() == 1) {
        m_menu->exec(event->globalPos());
    }
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
    QMessageBox::information(this, "成功", "添加成功");

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

void PasswordGenerator::act_storeExistAccount_trigger()
{
    m_DlgAddExistAccount = new DialogAddExistAccount;
    int ret=m_DlgAddExistAccount->exec();

    if (ret == QDialog::Rejected) {
        return;
    }
    auto NewAccount = m_DlgAddExistAccount->accountInfo();
    auto NewAccountRet = m_portalAccountTable->newAccount(m_DlgAddExistAccount->Platform().toStdString(), NewAccount);
    if (NewAccountRet == ErrorAccountTableModule::NoPlatformNode) {
        m_portalAccountTable->newPlatform(m_DlgAddExistAccount->Platform().toStdString());
        m_portalAccountTable->newAccount(m_DlgAddExistAccount->Platform().toStdString(), NewAccount);
    }
    delete m_DlgAddExistAccount;
    QMessageBox::information(this,"成功","添加成功");

    build_tree_model();
}

void PasswordGenerator::act_deleteNode_trigger()
{
    auto ret=QMessageBox::question(this, "确认", "你真的要删除么?");
    if (ret!=QMessageBox::Yes) {
        return;
    }

    auto cutIndex=ui->treeView->selectionModel()->currentIndex();
    auto cutItem = m_treeModel->itemFromIndex(cutIndex);

    if (cutItem->data(Qt::UserRole) == "account") {
        auto platform=cutItem->parent()->text();
        m_portalAccountTable->deleteAccount(platform.toStdString(),cutItem->text().toStdString());
        build_tree_model();
    }
    else if (cutItem->data(Qt::UserRole) == "platform") {
        m_portalAccountTable->deletePlatform(cutItem->text().toStdString());
        build_tree_model();
    }
    

    QMessageBox::information(this,"删除","删除成功");
}

void PasswordGenerator::check_filePath()
{
    QString path = QString::fromStdString(m_filePath);
    QFileInfo QPath(path);
    if (!QPath.exists()) {
        QFile userData(path);
        if (userData.open(QFile::ReadWrite)) {
            userData.close();
        }
        m_portalAccountTable->setNewFile(m_filePath,m_UID);
    }
}

void PasswordGenerator::ini_GlobaComponet()
{
    m_portalAccountTable = PortalAccountTable::getInstance();
}

