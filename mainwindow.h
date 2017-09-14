#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkReply>
#include "temperatureconverter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_lineEdit_bin_returnPressed();

    void on_lineEdit_dec_returnPressed();

    void on_lineEdit_oct_returnPressed();

    void on_lineEdit_hex_returnPressed();

    void on_lineEdit_celsius_returnPressed();

    void on_lineEdit_fahrenheit_returnPressed();

    void on_lineEdit_kelvin_returnPressed();

    void on_lineEdit_euro_returnPressed();

    void on_lineEdit_usd_returnPressed();

    void on_lineEdit_jpy_returnPressed();

    void on_actionBinary_Decimal_Octal_Hexadecimal_triggered();

    void on_actionCelsius_Fahrenheit_Kelvin_triggered();

    void on_actionAbout_triggered();

    void on_actionCurrent_exchange_rates_triggered();

    void on_actionExchange_rate_trend_triggered();

private:
    Ui::MainWindow *ui;

    void setBin(int n);

    void setDec(int n);

    void setOct(int n);

    void setHex(int n);

    void setFahrenheit(TemperatureConverter temp);

    void setCelsius(TemperatureConverter temp);

    void setKelvin(TemperatureConverter temp);

    void setEUR(float total, double rate);

    void setUSD(float total, double rate);

    void setJPY(float total, double rate);

    void showErrorBox();

    void clearLayout();

    void createNumericRepresentationLayout();

    void createTemperatureConversionLayout();

    void createCurrencyConversionLayout();

    template<typename T> inline T getWidget(QString name) const;

};

#endif // MAINWINDOW_H
