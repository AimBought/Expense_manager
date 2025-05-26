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
    //used for storing sum of expenses from a category
    std::vector<Expense> expensesList;

    //used for displaying expenses from selected category
    void updateListForCategory(const QString &category);
    //used for collecting all currently used categories
    void populateCategories();
};

#endif // SUMMARYDIALOG_H
