#include "PasswordGenerator.h"

#include"PortalAccountTable.h"
#include"DialogNewAccount.h"
#include"DialogAddExistAccount.h"
#include"LocalizationStringLoader-XML.h"

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
    /*模型与视图相关组件的生成*/
    m_treeModel = new QStandardItemModel(this);
    m_tableModel = new QStandardItemModel(this);
    m_treeSelection = new QItemSelectionModel(m_treeModel, this);

    /*右键菜单的设置*/
    m_menu = new QMenu(this);
    m_menu->addAction(ui->act_deleteNode);

    /*账户密码管理模块的配置的设置与加载*/
    m_portalAccountTable->setUID(m_UID);
    m_portalAccountTable->setFilePath(m_filePath);
    m_portalAccountTable->ini_portal();

    /*视图的模型设置*/
    ui->tableView->setModel(m_tableModel);
    ui->treeView->setSelectionModel(m_treeSelection);
    ui->treeView->setModel(m_treeModel);
    ui->treeView->setHeaderHidden(true);

    /*视图初始数据的填充*/
    build_tree_model();
    build_table_model_all_account();

    /*图标的建立*/
    build_icon();

    /*状态栏的组件补充*/
    set_label_UID();
}

void PasswordGenerator::build_connect()
{
    QObject::connect(ui->treeView,&QTreeView::clicked, this,
        &PasswordGenerator::build_treeSelectChange_for_table);

    QObject::connect(ui->act_storeNewAccount,&QAction::triggered,
        this,&PasswordGenerator::act_newAccount_trigger);

    QObject::connect(ui->pbtn_storeNewAccount,&QPushButton::clicked,
        ui->act_storeNewAccount,&QAction::trigger);

    QObject::connect(ui->act_saveInfo,&QAction::triggered,
        this,&PasswordGenerator::act_saveInfo_trigger);

    QObject::connect(ui->pbtn_saveInfo,&QPushButton::clicked,
        ui->act_saveInfo,&QAction::trigger);

    QObject::connect(ui->act_displayAllAccount,&QAction::triggered,
        this,&PasswordGenerator::act_displayAllAccount_trigger);

    QObject::connect(ui->pbtn_displayAllAccount,&QPushButton::clicked,
        ui->act_displayAllAccount, &QAction::trigger);

    QObject::connect(ui->act_storeExistAccount,&QAction::triggered,
        this,&PasswordGenerator::act_storeExistAccount_trigger);

    QObject::connect(ui->pbtn_storeExistAccount,&QPushButton::clicked,
        ui->act_storeExistAccount,&QAction::triggered);

    QObject::connect(ui->act_deleteNode,&QAction::triggered,
        this,&PasswordGenerator::act_deleteNode_trigger);

    QObject::connect(ui->act_exit,&QAction::triggered,
        this,&PasswordGenerator::act_exit_trigger);
}

void PasswordGenerator::ini_config()
{
    /*用于初始化类的配置信息，在类使用前使用，初始化步骤有依赖关系，切忌不要随意更改初始化顺序*/
    ini_GlobaComponet();
    check_filePath();
    build_languageString();
    build_ui();
    build_connect();
}


void PasswordGenerator::build_tree_model()
{
    /*将模型中的数据填充到树视图中*/
    m_treeModel->clear();
    auto root = m_treeModel->invisibleRootItem();
    
    /*节点*/
    auto  platformList = m_portalAccountTable->PlatformList();
    for (const auto & platform: platformList) {
        QStandardItem* platforItem = new QStandardItem();
        platforItem->setText(QString::fromStdString(platform));
        platforItem->setData("platform", Qt::UserRole);
        platforItem->setIcon(getIcon("peoples.png"));
        auto accountList=m_portalAccountTable->AccountList(platform);
        for (const auto & account:accountList) {
            QStandardItem* accountItem = new QStandardItem();
            accountItem->setData("account", Qt::UserRole);
            accountItem->setText(QString::fromStdString(account.accountName));
            ui->treeView->setExpanded(accountItem->index(), true);
            accountItem->setEditable(false);
            accountItem->setIcon(getIcon("people.png"));

            platforItem->appendRow(accountItem);

        }

        root->appendRow(platforItem);
        ui->treeView->setExpanded(platforItem->index(),true);
        platforItem->setEditable(false);
    }
    m_treeSelection->clearSelection();
}

void PasswordGenerator::build_treeSelectChange_for_table(const QModelIndex& index) {
    /*将树视图中的节点选择信息同步到表格视图中*/
    m_tableModel->clear();
    
    auto NodeType = m_treeModel->itemFromIndex(index);
    
    //表头的添加
    QStringList headerList;
    headerList.push_back(localizationString("22"));
    headerList.push_back(localizationString("5"));
    headerList.push_back(localizationString("6"));
    headerList.push_back(localizationString("23"));
    m_tableModel->setColumnCount(headerList.size());
    m_tableModel->setHorizontalHeaderLabels(headerList);

    //根据不同的节点实行不同的操作也即显示的数据方式不一样
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
    /*表格视图显示全部账户的信息*/
    m_tableModel->clear();
    m_row = m_portalAccountTable->AccountNumber();
    m_tableModel->setRowCount(m_row);

    QStringList headerList;
    headerList.push_back(localizationString("22"));
    headerList.push_back(localizationString("5"));
    headerList.push_back(localizationString("6"));
    headerList.push_back(localizationString("23"));
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

void PasswordGenerator::build_languageString()
{
    ui->pbtn_displayAllAccount->setText(localizationString("36"));
    ui->pbtn_saveInfo->setText(localizationString("37"));
    ui->pbtn_storeExistAccount->setText(localizationString("35"));
    ui->pbtn_storeNewAccount->setText(localizationString("34"));

    ui->gBox_yourAccount->setTitle(localizationString("38"));

    ui->act_storeNewAccount->setText(localizationString("39"));
    ui->act_storeExistAccount->setText(localizationString("40"));
    ui->act_deleteNode->setText(localizationString("32"));
    ui->act_displayAllAccount->setText(localizationString("36"));
    ui->act_saveInfo->setText(localizationString("37"));
    ui->act_exit->setText(localizationString("63"));
    ui->act_log_off->setText(localizationString("64"));

    this->setWindowTitle(localizationString("41"));
    ui->menu_edit->setTitle(localizationString("42"));
    ui->menu_exit->setTitle(localizationString("65"));
}

QString PasswordGenerator::localizationString(const std::string stringId)
{
    return QString(QString::fromStdString(m_locstringLoader->getString(stringId)));
}

void PasswordGenerator::build_icon()
{
    auto cutDir = QDir::currentPath();
    auto IconDir = cutDir + "/icon";
    ui->act_saveInfo->setIcon(getIcon("people-bottom.png"));
    ui->act_deleteNode->setIcon(getIcon("people-minus.png"));
    ui->act_displayAllAccount->setIcon(getIcon("every-user.png"));
    ui->act_findAccount->setIcon(getIcon("people-search.png"));
    ui->act_storeExistAccount->setIcon(getIcon("people-plus-one.png"));
    ui->act_storeNewAccount->setIcon(getIcon("people-plus-one.png"));
    ui->act_exit->setIcon(getIcon("exit.png"));
    ui->act_log_off->setIcon(getIcon("switch_account.png"));

    ui->pbtn_displayAllAccount->setIcon(getIcon("every-user.png"));
    ui->pbtn_saveInfo->setIcon(getIcon("people-bottom.png"));
    ui->pbtn_storeExistAccount->setIcon(getIcon("people-plus-one.png"));
    ui->pbtn_storeNewAccount->setIcon(getIcon("people-plus-one.png"));

    this->setWindowIcon(getIcon("data-display.png"));
}

QIcon PasswordGenerator::getIcon(const QString& fileName)
{
    auto cutDir = QDir::currentPath();
    auto filePath = cutDir + "/icon/"+fileName;
    return QIcon(filePath);
}

void PasswordGenerator::add_account_forTable(const AccountInfo& account, const QString& platform, int row)
{
    /*提炼的函数，方便对一个Account数据条目添加到表格视图中*/
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
        EncrpyIsIrreversibleItem->setText(localizationString("24"));
    }
    else {
        EncrpyIsIrreversibleItem->setText(localizationString("25"));
    }
    EncrpyIsIrreversibleItem->setEditable(false);
    m_tableModel->setItem(row, 3, EncrpyIsIrreversibleItem);

}

void PasswordGenerator::set_label_UID()
{
    m_label_UID_statue = new QLabel(this);
    QString text_label_UID = "UID: ";
    text_label_UID += m_UID;
    m_label_UID_statue->setText(text_label_UID);
    QFont label_UID_statue_font = m_label_UID_statue->font();
    label_UID_statue_font.setPointSize(10);
    m_label_UID_statue->setFont(label_UID_statue_font);
    ui->statusBar->addWidget(m_label_UID_statue);
}

void PasswordGenerator::contextMenuEvent(QContextMenuEvent* event)
{

    auto selectedIndexes = ui->treeView->selectionModel()->selectedIndexes();
    if (selectedIndexes.size() == 1) {
        m_menu->exec(event->globalPos());
    }
}

void PasswordGenerator::closeEvent(QCloseEvent* event)
{
    QMessageBox::StandardButton result =
        QMessageBox::question(this,
            localizationString("14"),
            localizationString("62"));
    if (result==QMessageBox::Yes) {
        act_saveInfo_trigger();
        event->accept();
    }
    else if (result==QMessageBox::No) {
        event->accept();
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
    QMessageBox::information(this, localizationString("26"), localizationString("27"));

    build_tree_model();
    
}

void PasswordGenerator::act_saveInfo_trigger()
{
    auto saveRet = m_portalAccountTable->save_change();
    if (saveRet!=ErrorAccountTableModule::No_ERROR) {
        QMessageBox::warning(this, localizationString("28"), localizationString("29"));
    }
    else {
        QMessageBox::information(this, localizationString("26"), localizationString("30"));
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

    QMessageBox::information(this, localizationString("26"), localizationString("27"));

    build_tree_model();
    delete m_DlgAddExistAccount;
}

void PasswordGenerator::act_deleteNode_trigger()
{
    auto ret=QMessageBox::question(this, localizationString("14"), localizationString("31"));
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
    

    QMessageBox::information(this, localizationString("32"), localizationString("33"));
}

void PasswordGenerator::act_exit_trigger()
{
    this->close();
}

void PasswordGenerator::check_filePath()
{
    /*检查配置文件，若没有配置文件那么就生成一个*/

    //查询是否含有当前账户对应的数据文件，如果没有那么就生成一个
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
    m_locstringLoader = LocalizationStringLoaderXML::getInstance();
}

