#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "temperatureconverter.h"
#include "currencyconverter.h"
#include "aboutdialog.h"
#include "exchangeratetrendselector.h"
#include <QMessageBox>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

template<typename T>
inline T MainWindow::getWidget(QString name) const
{
    return static_cast<T>(ui->centralWidget->findChild<T>(name));
}

void MainWindow::clearLayout()
{
    for (auto widget: ui->centralWidget->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly))
        delete widget;
    delete ui->centralWidget->layout();
}

void MainWindow::createNumericRepresentationLayout()
{
    QLabel *label = new QLabel(this);
    label->setObjectName("label_bin");
    label->setText("Binary");
    QLabel *label_2 = new QLabel(this);
    label_2->setObjectName("label_dec");
    label_2->setText("Decimal");
    QLabel *label_3 = new QLabel(this);
    label_3->setObjectName("label_oct");
    label_3->setText("Octal");
    QLabel *label_4 = new QLabel(this);
    label_4->setObjectName("label_hex");
    label_4->setText("Hex");

    QLineEdit *lineEdit = new QLineEdit(this);
    lineEdit->setObjectName("lineEdit_bin");
    QLineEdit *lineEdit_2 = new QLineEdit(this);
    lineEdit_2->setObjectName("lineEdit_dec");
    QLineEdit *lineEdit_3 = new QLineEdit(this);
    lineEdit_3->setObjectName("lineEdit_oct");
    QLineEdit *lineEdit_4 = new QLineEdit(this);
    lineEdit_4->setObjectName("lineEdit_hex");

    QGridLayout *myLayout = new QGridLayout(ui->centralWidget);
    myLayout->addWidget(label, 0, 0);
    myLayout->addWidget(lineEdit, 0, 1);
    myLayout->addWidget(label_2, 1, 0);
    myLayout->addWidget(lineEdit_2, 1, 1);
    myLayout->addWidget(label_3, 2, 0);
    myLayout->addWidget(lineEdit_3, 2, 1);
    myLayout->addWidget(label_4, 3, 0);
    myLayout->addWidget(lineEdit_4, 3, 1);
    ui->centralWidget->setLayout(myLayout);
}

void MainWindow::createTemperatureConversionLayout()
{
    QLabel *label = new QLabel(this);
    label->setObjectName("label_celsius");
    label->setText("ºC");
    QLabel *label_2 = new QLabel(this);
    label_2->setObjectName("label_fahrenheit");
    label_2->setText("ºF");
    QLabel *label_3 = new QLabel(this);
    label_3->setObjectName("label_kelvin");
    label_3->setText("ºK");

    QLineEdit *lineEdit = new QLineEdit(this);
    lineEdit->setObjectName("lineEdit_celsius");
    QLineEdit *lineEdit_2 = new QLineEdit(this);
    lineEdit_2->setObjectName("lineEdit_fahrenheit");
    QLineEdit *lineEdit_3 = new QLineEdit(this);
    lineEdit_3->setObjectName("lineEdit_kelvin");

    QGridLayout *myLayout = new QGridLayout(ui->centralWidget);
    myLayout->addWidget(label, 0, 0);
    myLayout->addWidget(lineEdit, 0, 1);
    myLayout->addWidget(label_2, 1, 0);
    myLayout->addWidget(lineEdit_2, 1, 1);
    myLayout->addWidget(label_3, 2, 0);
    myLayout->addWidget(lineEdit_3, 2, 1);
    ui->centralWidget->setLayout(myLayout);
}

void MainWindow::createCurrencyConversionLayout()
{
    QLabel *label = new QLabel(this);
    label->setObjectName("label_euro");
    label->setText("EUR");
    QLabel *label_b = new QLabel(this);
    label_b->setObjectName("label_rate_euro");
    label_b->setText("Exchange rate");
    QLabel *label_2 = new QLabel(this);
    label_2->setObjectName("label_usd");
    label_2->setText("USD");
    QLabel *label_2_b = new QLabel(this);
    label_2_b->setObjectName("label_rate_usd");
    label_2_b->setText("Exchange rate");
    QLabel *label_3 = new QLabel(this);
    label_3->setObjectName("label_jpy");
    label_3->setText("JPY");
    QLabel *label_3_b = new QLabel(this);
    label_3_b->setObjectName("label_rate_jpy");
    label_3_b->setText("Exchange rate");

    QLineEdit *lineEdit = new QLineEdit(this);
    lineEdit->setObjectName("lineEdit_euro");
    QLineEdit *lineEdit_b = new QLineEdit(this);
    lineEdit_b->setObjectName("lineEdit_rate_euro");
    QLineEdit *lineEdit_2 = new QLineEdit(this);
    lineEdit_2->setObjectName("lineEdit_usd");
    QLineEdit *lineEdit_2_b = new QLineEdit(this);
    lineEdit_2_b->setObjectName("lineEdit_rate_usd");
    QLineEdit *lineEdit_3 = new QLineEdit(this);
    lineEdit_3->setObjectName("lineEdit_jpy");
    QLineEdit *lineEdit_3_b = new QLineEdit(this);
    lineEdit_3_b->setObjectName("lineEdit_rate_jpy");

    QGridLayout *myLayout = new QGridLayout(ui->centralWidget);
    myLayout->addWidget(label, 0, 0);
    myLayout->addWidget(lineEdit, 0, 1);
    myLayout->addWidget(label_b, 0, 2);
    myLayout->addWidget(lineEdit_b, 0, 3);
    myLayout->addWidget(label_2, 1, 0);
    myLayout->addWidget(lineEdit_2, 1, 1);
    myLayout->addWidget(label_2_b, 1, 2);
    myLayout->addWidget(lineEdit_2_b, 1, 3);
    myLayout->addWidget(label_3, 2, 0);
    myLayout->addWidget(lineEdit_3, 2, 1);
    myLayout->addWidget(label_3_b, 2, 2);
    myLayout->addWidget(lineEdit_3_b, 2, 3);
    ui->centralWidget->setLayout(myLayout);
}

/* SETTERS */
void MainWindow::setBin(int n)
{
    QString bin;
    bin.setNum(n, 2);
    getWidget<QLineEdit*>("lineEdit_bin")->setText(bin);
}

void MainWindow::setDec(int n)
{
    getWidget<QLineEdit*>("lineEdit_dec")->setText(QString::number(n));
}

void MainWindow::setOct(int n)
{
    QString octal;
    octal.setNum(n, 8);
    getWidget<QLineEdit*>("lineEdit_oct")->setText(octal);
}

void MainWindow::setHex(int n)
{
    QString hex;
    hex.setNum(n, 16);
    getWidget<QLineEdit*>("lineEdit_hex")->setText(hex);
}

void MainWindow::setFahrenheit(TemperatureConverter temp)
{
    QString str_f;
    str_f.setNum(temp.getFahrenheit(), '.', 1);
    getWidget<QLineEdit*>("lineEdit_fahrenheit")->setText(str_f);
}

void MainWindow::setCelsius(TemperatureConverter temp)
{
    QString str_c;
    str_c.setNum(temp.getCelsius(), '.', 1);
    getWidget<QLineEdit*>("lineEdit_celsius")->setText(str_c);
}

void MainWindow::setKelvin(TemperatureConverter temp)
{
    QString str_k;
    str_k.setNum(temp.getKelvin(), '.', 2);
    getWidget<QLineEdit*>("lineEdit_kelvin")->setText(str_k);
}

void MainWindow::setEUR(float total, double rate)
{
    QString str_t;
    str_t.setNum(total * rate, '.', 2);
    getWidget<QLineEdit*>("lineEdit_euro")->setText(str_t);
    QString str_r;
    str_r.setNum(rate);
    getWidget<QLineEdit*>("lineEdit_rate_euro")->setText(str_r);
}

void MainWindow::setUSD(float total, double rate)
{
    QString str_t;
    str_t.setNum(total * rate, '.', 2);
    getWidget<QLineEdit*>("lineEdit_usd")->setText(str_t);
    QString str_r;
    str_r.setNum(rate);
    getWidget<QLineEdit*>("lineEdit_rate_usd")->setText(str_r);
}

void MainWindow::setJPY(float total, double rate)
{
    QString str_t;
    str_t.setNum(total * rate, '.', 2);
    getWidget<QLineEdit*>("lineEdit_jpy")->setText(str_t);
    QString str_r;
    str_r.setNum(rate);
    getWidget<QLineEdit*>("lineEdit_rate_jpy")->setText(str_r);
}

void MainWindow::showErrorBox()
{
    QMessageBox msgBox("", "Invalid input!",
                       QMessageBox::Critical, 0, 0, 0,
                       nullptr, Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
    msgBox.QDialog::setWindowTitle("Error");
    msgBox.exec();
}

/* SLOTS */
void MainWindow::on_lineEdit_bin_returnPressed()
{
    QString str = getWidget<QLineEdit*>("lineEdit_bin")->text();
    getWidget<QLineEdit*>("lineEdit_dec")->clear();
    getWidget<QLineEdit*>("lineEdit_oct")->clear();
    getWidget<QLineEdit*>("lineEdit_hex")->clear();

    bool ok;
    int n = str.toInt(&ok, 2);
    if(ok)
    {
        setDec(n);
        setOct(n);
        setHex(n);
    }
    else
    {
        showErrorBox();
    }
}

void MainWindow::on_lineEdit_dec_returnPressed()
{
    QString str = getWidget<QLineEdit*>("lineEdit_dec")->text();
    getWidget<QLineEdit*>("lineEdit_bin")->clear();
    getWidget<QLineEdit*>("lineEdit_oct")->clear();
    getWidget<QLineEdit*>("lineEdit_hex")->clear();

    bool ok;
    int n = str.toInt(&ok, 10);
    if(ok)
    {
        setBin(n);
        setOct(n);
        setHex(n);
    }
    else
    {
        showErrorBox();
    }
}

void MainWindow::on_lineEdit_oct_returnPressed()
{
    QString str = getWidget<QLineEdit*>("lineEdit_oct")->text();
    getWidget<QLineEdit*>("lineEdit_bin")->clear();
    getWidget<QLineEdit*>("lineEdit_dec")->clear();
    getWidget<QLineEdit*>("lineEdit_hex")->clear();

    bool ok;
    int n = str.toInt(&ok, 8);
    if(ok)
    {
        setBin(n);
        setDec(n);
        setHex(n);
    }
    else
    {
        showErrorBox();
    }
}

void MainWindow::on_lineEdit_hex_returnPressed()
{
    QString str = getWidget<QLineEdit*>("lineEdit_hex")->text();
    getWidget<QLineEdit*>("lineEdit_bin")->clear();
    getWidget<QLineEdit*>("lineEdit_dec")->clear();
    getWidget<QLineEdit*>("lineEdit_oct")->clear();

    bool ok;
    int n = str.toInt(&ok, 16);
    if(ok)
    {
        setBin(n);
        setDec(n);
        setOct(n);
    }
    else
    {
        showErrorBox();
    }
}

void MainWindow::on_lineEdit_celsius_returnPressed()
{
    QString str = getWidget<QLineEdit*>("lineEdit_celsius")->text();
    getWidget<QLineEdit*>("lineEdit_fahrenheit")->clear();
    getWidget<QLineEdit*>("lineEdit_kelvin")->clear();

    bool ok;
    float n = str.toFloat(&ok);
    if(ok)
    {
        TemperatureConverter temp;
        temp.setCelsius(n);
        setFahrenheit(temp);
        setKelvin(temp);
    }
    else
    {
        showErrorBox();
    }
}

void MainWindow::on_lineEdit_fahrenheit_returnPressed()
{
    QString str = getWidget<QLineEdit*>("lineEdit_fahrenheit")->text();
    getWidget<QLineEdit*>("lineEdit_celsius")->clear();
    getWidget<QLineEdit*>("lineEdit_kelvin")->clear();

    bool ok;
    float n = str.toFloat(&ok);
    if(ok)
    {
        TemperatureConverter temp;
        temp.setFahrenheit(n);
        setCelsius(temp);
        setKelvin(temp);
    }
    else
    {
        showErrorBox();
    }
}

void MainWindow::on_lineEdit_kelvin_returnPressed()
{
    QString str = getWidget<QLineEdit*>("lineEdit_kelvin")->text();
    getWidget<QLineEdit*>("lineEdit_celsius")->clear();
    getWidget<QLineEdit*>("lineEdit_fahrenheit")->clear();

    bool ok;
    float n = str.toFloat(&ok);
    if(ok)
    {
        TemperatureConverter temp;
        temp.setKelvin(n);
        setCelsius(temp);
        setFahrenheit(temp);
    }
    else
    {
        showErrorBox();
    }
}

void MainWindow::on_lineEdit_euro_returnPressed()
{
    QString str = getWidget<QLineEdit*>("lineEdit_euro")->text();
    getWidget<QLineEdit*>("lineEdit_usd")->clear();
    getWidget<QLineEdit*>("lineEdit_jpy")->clear();
    getWidget<QLineEdit*>("lineEdit_rate_euro")->clear();
    getWidget<QLineEdit*>("lineEdit_rate_usd")->clear();
    getWidget<QLineEdit*>("lineEdit_rate_jpy")->clear();

    bool ok;
    float n = str.toFloat(&ok);
    if(ok)
    {
        CurrencyConverter curr("EUR");

        setUSD(n, curr.getRate("USD"));
        setJPY(n, curr.getRate("JPY"));
    }
    else
    {
        showErrorBox();
    }
}

void MainWindow::on_lineEdit_usd_returnPressed()
{
    QString str = getWidget<QLineEdit*>("lineEdit_usd")->text();
    getWidget<QLineEdit*>("lineEdit_euro")->clear();
    getWidget<QLineEdit*>("lineEdit_jpy")->clear();
    getWidget<QLineEdit*>("lineEdit_rate_euro")->clear();
    getWidget<QLineEdit*>("lineEdit_rate_usd")->clear();
    getWidget<QLineEdit*>("lineEdit_rate_jpy")->clear();

    bool ok;
    float n = str.toFloat(&ok);
    if(ok)
    {
        CurrencyConverter curr("USD");

        setEUR(n, curr.getRate("EUR"));
        setJPY(n, curr.getRate("JPY"));
    }
    else
    {
        showErrorBox();
    }
}

void MainWindow::on_lineEdit_jpy_returnPressed()
{
    QString str = getWidget<QLineEdit*>("lineEdit_jpy")->text();
    getWidget<QLineEdit*>("lineEdit_usd")->clear();
    getWidget<QLineEdit*>("lineEdit_euro")->clear();
    getWidget<QLineEdit*>("lineEdit_rate_euro")->clear();
    getWidget<QLineEdit*>("lineEdit_rate_usd")->clear();
    getWidget<QLineEdit*>("lineEdit_rate_jpy")->clear();

    bool ok;
    float n = str.toFloat(&ok);
    if(ok)
    {
        CurrencyConverter curr("JPY");

        setEUR(n, curr.getRate("EUR"));
        setUSD(n, curr.getRate("USD"));
    }
    else
    {
        showErrorBox();
    }
}

/* MENU ACTIONS */
void MainWindow::on_actionBinary_Decimal_Octal_Hexadecimal_triggered()
{
    clearLayout();

    createNumericRepresentationLayout();

    connect(getWidget<QLineEdit*>("lineEdit_bin"), SIGNAL(returnPressed()), this, SLOT(on_lineEdit_bin_returnPressed()));
    connect(getWidget<QLineEdit*>("lineEdit_dec"), SIGNAL(returnPressed()), this, SLOT(on_lineEdit_dec_returnPressed()));
    connect(getWidget<QLineEdit*>("lineEdit_oct"), SIGNAL(returnPressed()), this, SLOT(on_lineEdit_oct_returnPressed()));
    connect(getWidget<QLineEdit*>("lineEdit_hex"), SIGNAL(returnPressed()), this, SLOT(on_lineEdit_hex_returnPressed()));
}

void MainWindow::on_actionCelsius_Fahrenheit_Kelvin_triggered()
{
    clearLayout();

    createTemperatureConversionLayout();

    connect(getWidget<QLineEdit*>("lineEdit_celsius"), SIGNAL(returnPressed()), this, SLOT(on_lineEdit_celsius_returnPressed()));
    connect(getWidget<QLineEdit*>("lineEdit_fahrenheit"), SIGNAL(returnPressed()), this, SLOT(on_lineEdit_fahrenheit_returnPressed()));
    connect(getWidget<QLineEdit*>("lineEdit_kelvin"), SIGNAL(returnPressed()), this, SLOT(on_lineEdit_kelvin_returnPressed()));
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog aDialog;
    aDialog.setModal(true);
    aDialog.exec();
}

void MainWindow::on_actionCurrent_exchange_rates_triggered()
{
    clearLayout();

    createCurrencyConversionLayout();

    connect(getWidget<QLineEdit*>("lineEdit_euro"), SIGNAL(returnPressed()), this, SLOT(on_lineEdit_euro_returnPressed()));
    connect(getWidget<QLineEdit*>("lineEdit_usd"), SIGNAL(returnPressed()), this, SLOT(on_lineEdit_usd_returnPressed()));
    connect(getWidget<QLineEdit*>("lineEdit_jpy"), SIGNAL(returnPressed()), this, SLOT(on_lineEdit_jpy_returnPressed()));
}

void MainWindow::on_actionExchange_rate_trend_triggered()
{
    show_exchange_rate_trend_dialog();
}

void MainWindow::show_exchange_rate_trend_dialog(QDate startSelectedDate, QDate endSelectedDate)
{
    ExchangeRateTrendSelector selDlg(startSelectedDate, endSelectedDate, this);

    connect(&selDlg, SIGNAL(accepted()), this, SLOT(displayExchangeRateTrend()));

    selDlg.exec();
}

void MainWindow::displayExchangeRateTrend()
{
    ExchangeRateTrendSelector* selector = qobject_cast<ExchangeRateTrendSelector*>(sender());
    if (selector != NULL)
    {
        QDate initial = selector->getInitialDate();
        QDate end = selector->getEndDate();
        QString origin = selector->getOriginCurrency();
        QString destination = selector->getDestinationCurrency();
        if (origin == destination)
        {
            showErrorBox();
            show_exchange_rate_trend_dialog(initial, end);
            return;
        }

        CurrencyConverter::computeExchangeRateTrend(initial, end, origin, destination, true);
    }
}
