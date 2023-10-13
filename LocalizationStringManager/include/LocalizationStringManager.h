#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LocalizationStringManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LocalizationStringManagerClass; };
QT_END_NAMESPACE

class LocalizationStringManager : public QMainWindow
{
    Q_OBJECT

public:
    LocalizationStringManager(QWidget *parent = nullptr);
    ~LocalizationStringManager();

private:
    Ui::LocalizationStringManagerClass *ui;
};
