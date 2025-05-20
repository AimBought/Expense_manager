#include "transaction.h"


Transaction::Transaction() : amount(0.0), date(QDate::currentDate()) {}

Transaction::Transaction(double amount, QDate date): amount(amount), date(date) {}

double Transaction::getAmount() const
{
    return amount;
}

QDate Transaction::getDate() const
{
    return date;
}
