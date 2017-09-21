#ifndef CURRENCYCONVERTER_H
#define CURRENCYCONVERTER_H

#include <QtNetwork/QNetworkReply>
#include <QtCharts/QLineSeries>

class CurrencyConverter : public QObject
{
    Q_OBJECT

public:
    CurrencyConverter();

    void computeExchangeRates(QString base, QDate date = QDate::currentDate());

    double getRate(QString currency);

    void displayExchangeRateTrend(QDate initial, QDate end,
                                  QString origin, QString destination,
                                  QWidget* parent = NULL);

signals:
    void setProgress(int val);

    void computationFinished();

private:
    QMap<QString, double> rates;

    QByteArray readExchangeRatesURL(QString base, QDate date = QDate::currentDate());

    void getExchangeRates(QByteArray byteArray);

};

#endif // CURRENCYCONVERTER_H
