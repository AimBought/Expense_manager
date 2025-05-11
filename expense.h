#ifndef EXPENSE_H
#define EXPENSE_H

#include <QString>
#include <QDate>


class Expense {
public:
    Expense(const QString &category, const QString &product, const QString &paymentMethod, double amount, const QDate &date);

    QString toString() const;
    QString category;
    QString product;
    QString paymentMethod;
    double amount;
    QDate date;
};

#endif // EXPENSE_H
