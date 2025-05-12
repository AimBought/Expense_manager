#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

#include "addexpensedialog.h"
#include "expense.h"

#include "simplelogger.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //context menu enabled
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, &QListWidget::customContextMenuRequested,
            this, &MainWindow::showListContextMenu);
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
        expenses.push_back(expense);
    }
    //Feedback after adding new item
    SimpleLogger simpleLogger;
    simpleLogger.logMessage("Added new item successfully!");

}

void MainWindow::showListContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->listWidget->mapToGlobal(pos);
    QListWidgetItem* item = ui->listWidget->itemAt(pos);
    if (!item) return;

    QMenu contextMenu;
    QAction* editAction   = contextMenu.addAction("Edit");
    QAction* deleteAction = contextMenu.addAction("Delete");

    QAction* selectedAction = contextMenu.exec(globalPos);
    if (!selectedAction) return;

    if (selectedAction == deleteAction)
    {
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
        //Feedback after deleting item
        SimpleLogger simpleLogger;
        simpleLogger.logMessage("Deleted item successfully!");
    }
    else if (selectedAction == editAction)
    {
        int row = ui->listWidget->row(item);

        AddExpenseDialog dialog(this);
        dialog.setExpense(expenses[row]);

        if (dialog.exec() == QDialog::Accepted)
        {
            Expense updated = dialog.getExpense();
            expenses[row] = updated;
            item->setText(updated.toString());
            //Feedback after editing item
            SimpleLogger simpleLogger;
            simpleLogger.logMessage("Edited item successfully!");
        }
    }
}


