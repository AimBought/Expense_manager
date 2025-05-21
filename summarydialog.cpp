#include "summarydialog.h"
#include "ui_summarydialog.h"

SummaryDialog::SummaryDialog(const std::vector<Expense> &expenses, QWidget *parent) : QDialog(parent), ui(new Ui::SummaryDialog)
{
    this->expensesList = expenses;
    ui->setupUi(this);
    populateCategories();

    //add all items at the beginning and count expenses
    Expense sum;
    for (const Expense &exp : expensesList)
    {
        ui->summaryListWidget->addItem(exp.toString());
        sum = sum + exp;
    }
    ui->expenseLabel->setText(QString("%1 zł").arg(sum.getAmount(), 0, 'f', 2));

    connect(ui->categoryComboBox, &QComboBox::currentTextChanged,
            this, &SummaryDialog::updateListForCategory);
}

SummaryDialog::~SummaryDialog()
{
    delete ui;
}

void SummaryDialog::populateCategories()
{
    QSet<QString> uniqueCategories;
    for (const Expense &exp : expensesList)
        uniqueCategories.insert(exp.getCategory());

    ui->categoryComboBox->addItem("All");
    for (const QString &cat : uniqueCategories)
        ui->categoryComboBox->addItem(cat);
}

void SummaryDialog::updateListForCategory(const QString &category)
{
    ui->summaryListWidget->clear();

    //add category items and count expenses
    Expense sum;
    for (const Expense &exp : expensesList)
    {
        if (category == "All" || exp.getCategory() == category)
        {
            ui->summaryListWidget->addItem(exp.toString());
            sum = sum + exp;
        }
    }

    ui->expenseLabel->setText(QString("%1 zł").arg(sum.getAmount(), 0, 'f', 2));
}


