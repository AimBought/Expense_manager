#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "expense.h"
#include <vector>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::vector<Expense> expenses;
    Expense totalExpense;


private slots:
    void on_addButton_clicked();
    void showListContextMenu(const QPoint &pos);
    void on_saveButton_clicked();
};
#endif // MAINWINDOW_H
