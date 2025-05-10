#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

#include "addexpensedialog.h"
#include "expense.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    AddExpenseDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        Expense expense = dialog.getExpense();
        ui->listWidget->addItem(expense.toString());
    }
}

