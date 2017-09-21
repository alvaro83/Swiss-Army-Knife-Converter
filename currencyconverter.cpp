#include "currencyconverter.h"
#include "exchangeratetrendviewer.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include <QObject>
#include <QVBoxLayout>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QPushButton>

CurrencyConverter::CurrencyConverter()
{
    rates.insert("EUR", 0);
    rates.insert("USD", 0);
    rates.insert("JPY", 0);
}

void CurrencyConverter::computeExchangeRates(QString base, QDate date)
{
    QByteArray bts = this->readExchangeRatesURL(base, date);
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

void CurrencyConverter::displayExchangeRateTrend(QDate initial, QDate end,
                                                 QString origin, QString destination,
                                                 QWidget* parent)
{
    ExchangeRateTrendViewer wdg(parent);

    QtCharts::QLineSeries* series = new QtCharts::QLineSeries(&wdg);

    int days = QDateTime(initial).daysTo(QDateTime(end)) + 1;
    float s = days/100.0;

    while (initial <= end)
    {
        computeExchangeRates(origin, initial);
        initial = initial.addDays(1);
        QDateTime momentInTime;
        momentInTime.setDate(initial);
        if (getRate(destination) != 0)
            series->append(momentInTime.toMSecsSinceEpoch(), getRate(destination));
        int val = 100.0 - floor((momentInTime.daysTo(QDateTime(end)))/ s);
        emit setProgress(val);
    }
    emit computationFinished();

    QtCharts::QChart* chart = new QtCharts::QChart();
    chart->setParent(&wdg);
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle(origin + " -> " + destination + " Exchange rate trend");
    chart->setMinimumSize(650, 550);

    QtCharts::QDateTimeAxis* axisX = new QtCharts::QDateTimeAxis(chart);
    axisX->setFormat("dd MMM yyyy");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QtCharts::QValueAxis* axisY = new QtCharts::QValueAxis(chart);
    axisY->setLabelFormat("%f");
    axisY->setTitleText("Exchange rate");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    wdg.findChild<QtCharts::QChartView*>("rateViewer")->setChart(chart);
    wdg.findChild<QtCharts::QChartView*>("rateViewer")->setRenderHint(QPainter::Antialiasing);

    wdg.exec();
}
