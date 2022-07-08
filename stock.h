#ifndef STOCK_H
#define STOCK_H

#include <QDialog>

class Stock
{

public:
    Stock() {}
    Stock(QString symbol, QString longname, long long price, long long bazar)
    {
        this->symbol = symbol;
        this->longname = longname;
        this->price = price;
        this->bazar = bazar;
        this->value = 0;
    }

    QString print()
    {
        return symbol + " " + longname + " "
               + QString::number(price) + " "
               + QString::number(bazar) + " " +
               " I have : "
               + QString::number(value) + "\n";
    }

    QString symbol; //5
    QString longname; //50
    long long price;
    long long bazar;
    long long value;

};


#endif // STOCK_H
