#pragma once

#include <QtWidgets/QDialog>
#include "ui_DialogNewAccount.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DialogNewAccountClass; };
QT_END_NAMESPACE

class DialogNewAccount : public QDialog
{
    Q_OBJECT

public:
    DialogNewAccount(QWidget *parent = nullptr);
    ~DialogNewAccount();

private:
    Ui::DialogNewAccountClass *ui;
};
