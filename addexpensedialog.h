#ifndef ADDEXPENSEDIALOG_H
#define ADDEXPENSEDIALOG_H

#include <QDialog>
#include "expense.h"

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

private:
    Ui::AddExpenseDialog *ui;
};

#endif // ADDEXPENSEDIALOG_H
