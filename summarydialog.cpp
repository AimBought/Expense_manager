#include "summarydialog.h"
#include "ui_summarydialog.h"

SummaryDialog::SummaryDialog(const std::vector<Expense> &expenses, QWidget *parent) : QDialog(parent), ui(new Ui::SummaryDialog)
{
    this->expensesList = expenses;
    ui->setupUi(this);
    populateCategories();

    for (const Expense &exp : expensesList)
    {
        ui->summaryListWidget->addItem(exp.toString());
    }

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

    for (const Expense &exp : expensesList) {
        if (category == "All" || exp.getCategory() == category)
            ui->summaryListWidget->addItem(exp.toString());
    }
}
