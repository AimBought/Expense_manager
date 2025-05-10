#ifndef ADDEXPENSEDIALOG_H
#define ADDEXPENSEDIALOG_H

#include <QDialog>

namespace Ui {
class AddExpenseDialog;
}

class AddExpenseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddExpenseDialog(QWidget *parent = nullptr);
    ~AddExpenseDialog();

private:
    Ui::AddExpenseDialog *ui;
};

#endif // ADDEXPENSEDIALOG_H
