#include "currencyconverter.h"
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
#include <QProgressDialog>

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

void CurrencyConverter::computeExchangeRateTrend(QDate initial, QDate end,
                                                 QString origin, QString destination,
                                                 bool displayProgress, QWidget* parent)
{
    QtCharts::QLineSeries* series = new QtCharts::QLineSeries(parent);

    int days = QDateTime(initial).daysTo(QDateTime(end)) + 1;
    float s = days/100.0;

    QProgressDialog bar;

    if (displayProgress)
    {
        bar.setCancelButton(0);
        bar.show();
    }

    while (initial <= end)
    {
        CurrencyConverter curr(origin, initial);
        initial = initial.addDays(1);
        QDateTime momentInTime;
        momentInTime.setDate(initial);
        if (curr.getRate(destination) != 0)
            series->append(momentInTime.toMSecsSinceEpoch(), curr.getRate(destination));
        int val = 100.0 - floor((momentInTime.daysTo(QDateTime(end)))/ s);
        if (displayProgress)
            bar.setValue(val);
    }

    if (displayProgress)
        bar.close();

    QtCharts::QChart* chart = new QtCharts::QChart();
    chart->setParent(parent);
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle(origin + " -> " + destination + " Exchange rate trend");

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

    QtCharts::QChartView* chartView = new QtCharts::QChartView(chart, parent);
    chartView->setRenderHint(QPainter::Antialiasing);
    chart->setMinimumSize(650, 550);
    parent->setLayout(new QVBoxLayout());
    parent->setMinimumSize(650, 550);
}
