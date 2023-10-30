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

class PasswordGenerator 
    : public QMainWindow
{
    Q_OBJECT

public:
    PasswordGenerator(QWidget *parent = nullptr);

    ~PasswordGenerator();

private:
    Ui::PasswordGeneratorClass *ui;

private:
    /*类内保存的qt对象引用*/
    QStandardItemModel* m_treeModel{nullptr};

    QStandardItemModel* m_tableModel{ nullptr };

    QItemSelectionModel* m_treeSelection{ nullptr };

    QMenu* m_menu{ nullptr };

private:
    /*使用的全局数据模块*/
    PortalAccountTable* m_portalAccountTable{ nullptr };

    LocalizationStringLoaderXML* m_locstringLoader{nullptr};

private:
    /*保存的数据文件信息*/
    std::string m_UID;

    std::string m_filePath;

private:
    /*使用的自定义窗口类*/
    DialogNewAccount* m_DlgNewAccount{ nullptr };

    DialogAddExistAccount* m_DlgAddExistAccount{ nullptr };

private:
    /*表格使用的大小参数*/
    int m_column{ 0 };

    int m_row{ 0 };

public:
    /*对外公开的设置函数，在使用此类前应该进行相关配置，最后一定要使用ini_config进行配置加载确保类的正常运作*/
    void set_UID(const std::string& UID) { m_UID = UID; }

    void set_filePath(const std::string& filePath) { m_filePath = filePath; }

    void ini_config();

private:
    /*ui生成的相关函数*/
    void build_ui();

    void build_connect();

    void build_tree_model();

    void build_table_model_all_account();

    void build_languageString();

    void build_icon();

private:
    /*提炼函数*/
    QString localizationString(const std::string stringId);

    QIcon getIcon(const QString & fileName );

    void add_account_forTable(const AccountInfo& account, const QString& platform, int row);

private:
    /*与配置相关的一些工作*/
    void check_filePath();

    void ini_GlobaComponet();

private:
    /*重写父类的函数*/
    void contextMenuEvent(QContextMenuEvent* event);

private slots:
    void build_treeSelectChange_for_table(const QModelIndex& index);

    void act_newAccount_trigger();

    void act_saveInfo_trigger();

    void act_displayAllAccount_trigger();

    void act_storeExistAccount_trigger();

    void act_deleteNode_trigger();

};
