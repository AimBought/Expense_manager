#include "addexpensedialog.h"
#include "ui_addexpensedialog.h"

AddExpenseDialog::AddExpenseDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddExpenseDialog)
{
    ui->setupUi(this);
}

AddExpenseDialog::~AddExpenseDialog()
{
    delete ui;
}
