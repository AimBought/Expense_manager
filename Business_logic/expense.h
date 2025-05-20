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
    //amount getter
    double getAmount() const;
    //category getter
    QString getCategory() const;
    //product getter
    QString getProduct() const;
    //allow for creating empty objects
    Expense();
    Expense(double amount);
    //used for read from file function
    static Expense fromString(const QString &str);
};

//overloading operator + for displaying sum of items' price
Expense operator+(const Expense &lhs, const Expense &rhs);

#endif // EXPENSE_H
