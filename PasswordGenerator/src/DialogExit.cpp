#include "DialogExit.h"

DialogExit::DialogExit(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogExitClass())
{
    ui->setupUi(this);
}

DialogExit::~DialogExit()
{
    delete ui;
}
