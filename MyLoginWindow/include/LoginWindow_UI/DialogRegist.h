#include <QDialog>
#include "ui_DialogRegist.h"


QT_BEGIN_NAMESPACE
namespace Ui { class DialogRegistClass; };
QT_END_NAMESPACE

class DialogRegist : public QDialog
{
    Q_OBJECT

public:
    DialogRegist(QWidget* parent = nullptr);
    ~DialogRegist();
private:
    Ui::DialogRegistClass* ui;
private:
    void build_ui();
    void build_connect();
    QString get_Account() { return ui->ledit_account->text(); }
    QString get_password() { return ui->ledit_password->text(); }
    bool registAccount();
private slots:
    void on_pbtn_ok_clicked();
    void on_ledit_account_changed();
    void on_ledit_password_changed();
    void on_ledit_password_again_changed();
};
