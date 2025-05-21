#ifndef SUMMARYDIALOG_H
#define SUMMARYDIALOG_H

#include <QDialog>
#include "expense.h"

namespace Ui {
class SummaryDialog;
}

class SummaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SummaryDialog(const std::vector<Expense> &expenses, QWidget *parent = nullptr);
    ~SummaryDialog();

private:
    Ui::SummaryDialog *ui;
    std::vector<Expense> expensesList;

    void updateListForCategory(const QString &category);
    void populateCategories();
};

#endif // SUMMARYDIALOG_H
