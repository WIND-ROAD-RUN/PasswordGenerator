#pragma once

#include <QDialog>
#include "ui_DialogExit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DialogExitClass; };
QT_END_NAMESPACE

class DialogExit : public QDialog
{
    Q_OBJECT

public:
    DialogExit(QWidget *parent = nullptr);
    ~DialogExit();

private:
    Ui::DialogExitClass *ui;
};
