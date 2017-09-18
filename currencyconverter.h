#ifndef CURRENCYCONVERTER_H
#define CURRENCYCONVERTER_H

#include <QtNetwork/QNetworkReply>
#include <QtCharts/QLineSeries>

class CurrencyConverter
{
public:
    CurrencyConverter(QString base, QDate date = QDate::currentDate());

    double getRate(QString currency);

    static void computeExchangeRateTrend(QDate initial, QDate end,
                                         QString origin, QString destination,
                                         QWidget* parent = NULL);

private:
    QMap<QString, double> rates;

    QByteArray readExchangeRatesURL(QString base, QDate date = QDate::currentDate());

    void getExchangeRates(QByteArray byteArray);

};

#endif // CURRENCYCONVERTER_H
