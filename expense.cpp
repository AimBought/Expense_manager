#include "expense.h"

Expense::Expense(const QString &category, const QString &product, const QString &paymentMethod, double amount, const QDate &date)
    : category(category), product(product), paymentMethod(paymentMethod),
    amount(amount), date(date) {}

QString Expense::toString() const {
    return QString("%1 | %2 | %3 | %4 zł | %5")
        .arg(category)
        .arg(product)
        .arg(paymentMethod)
        .arg(amount, 0, 'f', 2)
        .arg(date.toString("yyyy-MM-dd"));
}
