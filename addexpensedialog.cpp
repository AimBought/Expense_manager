#include "addexpensedialog.h"
#include "ui_addexpensedialog.h"

AddExpenseDialog::AddExpenseDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddExpenseDialog)
{
    ui->setupUi(this);
    ui->amountSpinBox->setMaximum(1000000.0);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

AddExpenseDialog::~AddExpenseDialog()
{
    delete ui;
}

Expense AddExpenseDialog::getExpense() const
{
    return Expense(
        ui->categoryLineEdit->text(),
        ui->productLineEdit->text(),
        ui->paymentMethodComboBox->currentText(),
        ui->amountSpinBox->value(),
        ui->dateEdit->date()
        );
    //test do commita
}

void AddExpenseDialog::setExpense(const Expense &expense)
{
    ui->categoryLineEdit->setText(expense.category);
    ui->productLineEdit->setText(expense.product);
    ui->paymentMethodComboBox->setCurrentText(expense.paymentMethod);
    ui->amountSpinBox->setValue(expense.amount);
    ui->dateEdit->setDate(expense.date);
}
