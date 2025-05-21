#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "addexpensedialog.h"
#include "Business_logic/expense.h"
#include "Business_logic/exceptions.h"
#include "simplelogger.h"
#include "summarydialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //context menu enabled
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, &QListWidget::customContextMenuRequested,
            this, &MainWindow::showListContextMenu);
    connect(ui->themeCheckBox, &QCheckBox::toggled, this, &MainWindow::on_themeCheckBox_toggled);
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
        if (expense.getCategory().isEmpty() ||
            expense.getProduct().isEmpty() ||
            expense.getAmount() <= 0.0) {
            //Feedback after adding new item
            SimpleLogger simpleLogger;
            simpleLogger.logMessage("Can't add empty expense!");
            return;
        }
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
    QAction* editAction = contextMenu.addAction("Edit");
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
            if (updated.getCategory().isEmpty() ||
                updated.getProduct().isEmpty() ||
                updated.getAmount() <= 0.0) {
                //Feedback after adding new item
                SimpleLogger simpleLogger;
                simpleLogger.logMessage("Can't edit to empty expense!");
                return;
            }
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
    try
    {
        QFile file("expenses.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            throw FileWriteException();
        }

        QTextStream out(&file);
        for (const Expense &e : expenses)
        {
            out << e.toString() << "\n";
        }
        file.close();
        //Feedback after saving successfully
        SimpleLogger simpleLogger;
        simpleLogger.logMessage("Saved to file successfully!");
    }
    catch (exception& FileWriteException)
    {
        //Feedback after error
        SimpleLogger simpleLogger;
        simpleLogger.logMessage(FileWriteException.what());
    }
}

void MainWindow::on_readButton_clicked()
{
    try
    {
        QFile file("expenses.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            throw FileReadException();
        }
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
    catch (exception& FileReadException)
    {
        //Feedback after error
        SimpleLogger simpleLogger;
        simpleLogger.logMessage(FileReadException.what());
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

void MainWindow::on_themeCheckBox_toggled(bool checked)
{
    if (checked) {
        // DARK MODE
        qApp->setStyleSheet(R"(
            QWidget {
                background-color: #121212;
                color: #FFFFFF;
            }
            QPushButton {
                background-color: #1E1E1E;
                border: 1px solid #333;
                color: #FFFFFF;
            }
            QLineEdit, QComboBox, QListWidget {
                background-color: #1E1E1E;
                color: #FFFFFF;
                border: 1px solid #333;
            }
        )");
    } else {
        // LIGHT MODE (clear stylesheet or set custom light one)
        qApp->setStyleSheet("");
    }
}

void MainWindow::on_summaryButton_clicked()
{
    SummaryDialog summaryDialog(expenses, this);
    summaryDialog.exec();
}
