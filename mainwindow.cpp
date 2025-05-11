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
    }
    //Feedback after adding new item
    SimpleLogger simpleLogger;
    simpleLogger.logMessage("Added new item successfully!");

}

void MainWindow::showListContextMenu(const QPoint &pos)
{

    QPoint globalPos = ui->listWidget->mapToGlobal(pos);


    QListWidgetItem *item = ui->listWidget->itemAt(pos);
    if (!item)
        return;

    QMenu contextMenu(this);
    QAction *deleteAction   = contextMenu.addAction(tr("Delete"));


    QAction *selectedAction = contextMenu.exec(globalPos);
    if (selectedAction == deleteAction) {

        QListWidgetItem *taken = ui->listWidget->takeItem(ui->listWidget->row(item));
        delete taken;
        //Feddback after deleting item
        SimpleLogger simpleLogger;
        simpleLogger.logMessage("Deleted item successfully");

    }
}
