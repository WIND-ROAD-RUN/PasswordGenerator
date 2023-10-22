#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PasswordGenerator.h"


QT_BEGIN_NAMESPACE
namespace Ui { class PasswordGeneratorClass; };
QT_END_NAMESPACE

class QStandardItemModel;
class QItemSelectionModel;
class PortalAccountTable;

class PasswordGenerator : public QMainWindow
{
    Q_OBJECT

public:
    PasswordGenerator(QWidget *parent = nullptr);
    ~PasswordGenerator();
private:
    Ui::PasswordGeneratorClass *ui;
private:
    QStandardItemModel* m_model;
    QItemSelectionModel* m_selection;
    PortalAccountTable* m_portalAccountTable;
private:
    void build_ui();
    void build_connect();
    void update_ui();
    void build_model();
};
