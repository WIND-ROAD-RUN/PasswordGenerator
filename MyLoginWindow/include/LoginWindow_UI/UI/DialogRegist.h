#include "ui_DialogRegist.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class DialogRegistClass; };
QT_END_NAMESPACE

class LocalizationStringLoaderXML;
class DialogRegist 
    : public QDialog
{
    Q_OBJECT
private:
    Ui::DialogRegistClass* ui;

    LocalizationStringLoaderXML* m_locStCom{ nullptr };

public:
    DialogRegist(QWidget* parent = nullptr);

    ~DialogRegist();

private:
    void build_ui();

    void build_connect();

    void build_languageString();

private:
    QString get_account() { return ui->ledit_account->text(); }

    QString get_password() { return ui->ledit_password->text(); }

    bool registAccount();

private:
    /*提炼函数如下*/
    QString localizationString(const std::string stringId);

private slots:
    void on_pbtn_ok_clicked();

    void on_ledit_account_changed();

    void on_ledit_password_changed();

    void on_ledit_password_again_changed();

};
