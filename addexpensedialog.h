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
    explicit AddExpenseDialog(QWidget *parent = nullptr);
    ~AddExpenseDialog();

    Expense getExpense() const;
    void setExpense(const Expense &expense);

private:
    Ui::AddExpenseDialog *ui;
};

#endif // ADDEXPENSEDIALOG_H
