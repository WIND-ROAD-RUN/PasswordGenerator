#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PasswordGenerator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PasswordGeneratorClass; };
QT_END_NAMESPACE

class PasswordGenerator : public QMainWindow
{
    Q_OBJECT

public:
    PasswordGenerator(QWidget *parent = nullptr);
    ~PasswordGenerator();

private:
    Ui::PasswordGeneratorClass *ui;
};
