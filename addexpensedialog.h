#ifndef ADDEXPENSEDIALOG_H
#define ADDEXPENSEDIALOG_H

#include <QDialog>
#include "Business_logic/expense.h"

namespace Ui {
class AddExpenseDialog;
}

class AddExpenseDialog : public QDialog
{
    Q_OBJECT

public:
    //sets up new window dialog
    explicit AddExpenseDialog(QWidget *parent = nullptr);
    ~AddExpenseDialog();
    //used for getting data from different widgets
    Expense getExpense() const;
    //used while editing expense for naming already added ones
    void setExpense(const Expense &expense);

private:
    Ui::AddExpenseDialog *ui;
};

#endif // ADDEXPENSEDIALOG_H
