#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDate>

class Transaction {
protected:
    double amount;
    QDate date;

public:
    Transaction();
    Transaction(double amount, QDate date);
    double getAmount() const;
    QDate getDate() const;
};

#endif // TRANSACTION_H
