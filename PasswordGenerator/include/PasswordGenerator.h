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
class LocalizationStringLoaderXML;

class PasswordGenerator : public QMainWindow
{
    Q_OBJECT

public:
    PasswordGenerator(QWidget *parent = nullptr);
    ~PasswordGenerator();
private:
    Ui::PasswordGeneratorClass *ui;
private:
    QStandardItemModel* m_treeModel{nullptr};
    QStandardItemModel* m_tableModel{ nullptr };
    QItemSelectionModel* m_treeSelection{ nullptr };
    PortalAccountTable* m_portalAccountTable{ nullptr };
    QMenu* m_menu{ nullptr };
private:
    LocalizationStringLoaderXML* m_locstringLoader{nullptr};
private:
    std::string m_UID;
    std::string m_filePath;
private:
    DialogNewAccount* m_DlgNewAccount{ nullptr };
    DialogAddExistAccount* m_DlgAddExistAccount{ nullptr };
private:
    int m_column{ 0 };
    int m_row{ 0 };
public:
    void set_UID(const std::string& UID) { m_UID = UID; }
    void set_filePath(const std::string& filePath) { m_filePath = filePath; }
    void ini_config();
private:
    void build_ui();
    void build_connect();
    void build_tree_model();
    void build_table_model_all_account();
    void build_languageString();
    inline QString localizationString(const std::string stringId);
public:
    void build_icon(const QIcon & icon);
private:
    void add_account_forTable(const AccountInfo & account,const QString & platform ,int row);
    void contextMenuEvent(QContextMenuEvent* event);
    void check_filePath();
    void ini_GlobaComponet();
private slots:
    void build_treeSelectChange_for_table(const QModelIndex& index);
    void act_newAccount_trigger();
    void act_saveInfo_trigger();
    void act_displayAllAccount_trigger();
    void act_storeExistAccount_trigger();
    void act_deleteNode_trigger();
};
