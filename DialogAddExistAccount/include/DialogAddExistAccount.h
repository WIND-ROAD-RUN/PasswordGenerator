#pragma once

#include <QtWidgets/QDialog>
#include "ui_DialogAddExistAccount.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DialogAddExistAccountClass; };
QT_END_NAMESPACE

class DialogAddExistAccount : public QDialog
{
    Q_OBJECT

public:
    DialogAddExistAccount(QWidget *parent = nullptr);
    ~DialogAddExistAccount();

private:
    Ui::DialogAddExistAccountClass *ui;
};
