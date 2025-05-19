#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

#include "addexpensedialog.h"
#include "Business_logic/expense.h"

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
// addButton
{
    AddExpenseDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        Expense expense = dialog.getExpense();
        ui->listWidget->addItem(expense.toString());
        expenses.push_back(expense);
        //add expense to sum and display
        totalExpense = totalExpense + expense;
        ui->sumLabel->setText(QString("%1 zł").arg(totalExpense.getAmount(), 0, 'f', 2));
        //Feedback after adding new item
        SimpleLogger simpleLogger;
        simpleLogger.logMessage("Added new item successfully!");
    }
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
        int row = ui->listWidget->row(item);
        totalExpense = totalExpense + Expense(-expenses[row].getAmount());
        expenses.erase(expenses.begin() + row);
        delete ui->listWidget->takeItem(row);

        ui->sumLabel->setText(QString("%1 zł").arg(totalExpense.getAmount(), 0, 'f', 2));
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

            //edit sum of expenses
            Expense sum;
            for (const auto &exp : expenses)
            {
                sum = sum + exp;
            }
            totalExpense = sum;

            ui->sumLabel->setText(QString("%1 zł").arg(totalExpense.getAmount(), 0, 'f', 2));

            //Feedback after editing item
            SimpleLogger simpleLogger;
            simpleLogger.logMessage("Edited item successfully!");
        }
    }
}

void MainWindow::on_saveButton_clicked()
{
    QFile file("expenses.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        for (const Expense &e : expenses)
        {
            out << e.toString() << "\n";
        }
        file.close();
        //Feedback aftersuccessfully
        SimpleLogger simpleLogger;
        simpleLogger.logMessage("Saved to file successfully!");
    } else
    {
        //Feedback after error
        SimpleLogger simpleLogger;
        simpleLogger.logMessage("Couldn't save to file!");
    }
}

void MainWindow::on_readButton_clicked()
{
    QFile file("expenses.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);

        ui->listWidget->clear();
        expenses.clear();

        while (!in.atEnd())
        {
            QString line = in.readLine();
            Expense e = Expense::fromString(line);
            expenses.push_back(e);
            ui->listWidget->addItem(e.toString());
        }

        file.close();

        updateTotalExpense();

        //Feedback after reading successfully
        SimpleLogger simpleLogger;
        simpleLogger.logMessage("Read from file successfully!");
    }
    else
    {
        //Feedback after error
        SimpleLogger simpleLogger;
        simpleLogger.logMessage("Couldn't read from file!");
    }
}

void MainWindow::updateTotalExpense()
{
    Expense sum;
    for (const Expense &e : expenses)
    {
        sum = sum + e;
    }
    totalExpense = sum;
    ui->sumLabel->setText(QString("%1 zł").arg(totalExpense.getAmount(), 0, 'f', 2));
}

//removes all items from listWidget
void MainWindow::on_removeButton_clicked()
{
    ui->listWidget->clear();
    expenses.clear();
    updateTotalExpense();
    //Feedback after removing all items
    SimpleLogger simpleLogger;
    simpleLogger.logMessage("List cleared successfully");
}
