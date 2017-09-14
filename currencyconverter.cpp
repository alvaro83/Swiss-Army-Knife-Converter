#include "currencyconverter.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include <QObject>

CurrencyConverter::CurrencyConverter(QString base, QDate date)
{
    QByteArray bts = this->readExchangeRatesURL(base, date);

    rates.insert("EUR", 0);
    rates.insert("USD", 0);
    rates.insert("JPY", 0);
    getExchangeRates(bts);
}

double CurrencyConverter::getRate(QString currency)
{
    return rates.value(currency);
}

QByteArray CurrencyConverter::readExchangeRatesURL(QString base, QDate date)
{
    QNetworkAccessManager nam;
    QString date_str;

    if (date == QDate::currentDate())
        date_str = "latest";
    else
        date_str = date.toString(Qt::ISODate);

    QUrl url("http://api.fixer.io/" + date_str + "?base=" + base + "&symbols=EUR,USD,JPY");
    QNetworkRequest request;
    request.setUrl(url);
    QNetworkReply* reply = nam.get(request);

    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    QObject::connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), &loop, SLOT(quit()));
    loop.exec();

    QByteArray bts = reply->readAll();
    return bts;
}

void CurrencyConverter::getExchangeRates(QByteArray byteArray)
{
    QJsonParseError err;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(byteArray, &err);

    QJsonObject jsonObject = jsonResponse.object();

    QJsonObject rates_json = jsonObject["rates"].toObject();

    QMapIterator<QString, double> i(rates);
    while (i.hasNext())
    {
        i.next();
        QJsonValue value = rates_json.value(i.key());
        rates[i.key()] = value.toDouble();
    }
}
