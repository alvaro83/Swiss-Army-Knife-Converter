#ifndef CURRENCYCONVERTER_H
#define CURRENCYCONVERTER_H

#include <QtNetwork/QNetworkReply>

class CurrencyConverter
{
public:
    CurrencyConverter(QString base, QDate date = QDate::currentDate());

    double getRate(QString currency);

private:
    QMap<QString, double> rates;

    QByteArray readExchangeRatesURL(QString base, QDate date = QDate::currentDate());

    void getExchangeRates(QByteArray byteArray);

};

#endif // CURRENCYCONVERTER_H
