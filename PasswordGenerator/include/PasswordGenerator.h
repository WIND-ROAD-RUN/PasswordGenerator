#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PasswordGenerator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PasswordGeneratorClass; };
QT_END_NAMESPACE

class QStandardItemModel;
class QItemSelectionModel;
class PortalAccountTable;
class AccountInfo;
class DialogNewAccount;
class DialogAddExistAccount;

class PasswordGenerator : public QMainWindow
{
    Q_OBJECT

public:
    PasswordGenerator(QWidget *parent = nullptr);
    ~PasswordGenerator();
private:
    Ui::PasswordGeneratorClass *ui;
private:
    QStandardItemModel* m_treeModel;
    QStandardItemModel* m_tableModel;
    QItemSelectionModel* m_treeSelection;
    PortalAccountTable* m_portalAccountTable;
    std::string m_filePath;
    QMenu* m_menu;
private:
    DialogNewAccount* m_DlgNewAccount;
    DialogAddExistAccount* m_DlgAddExistAccount;
private:
    int m_column{ 0 };
    int m_row{ 0 };
public:
    void set_filePath(const std::string & filePath) { m_filePath = filePath; }
    void ini_config();
private:
    void build_ui();
    void build_connect();
    void build_tree_model();
    void build_table_model_all_account();
private:
    void add_account_forTable(const AccountInfo & account,const QString & platform ,int row);
    void contextMenuEvent(QContextMenuEvent* event);
private slots:
    void build_treeSelectChange_for_table(const QModelIndex& index);
    void act_newAccount_trigger();
    void act_saveInfo_trigger();
    void act_displayAllAccount_trigger();
    void act_storeExistAccount_trigger();
    void act_deleteNode_trigger();
};
