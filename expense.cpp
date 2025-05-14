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

//overloading operator + for displaying sum of items' price
Expense operator+(const Expense &lhs, const Expense &rhs)
{
    Expense result = lhs;
    result.amount += rhs.amount;
    return result;
}

//amount getter
double Expense::getAmount() const
{
    return amount;
}

//for creating empty classes(used for summing with overloaded + sign)
Expense::Expense()
    : category(""), product(""), paymentMethod(""), amount(0.0), date(QDate::currentDate())
{
}
Expense::Expense(double amount)
    : category(""), product(""), paymentMethod(""), amount(amount), date(QDate::currentDate())
{
}

