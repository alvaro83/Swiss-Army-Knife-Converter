#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    void on_actionBinary_Decimal_Octal_Hexadecimal_triggered();

    void on_actionCelsius_Fahrenheit_Kelvin_triggered();

private:
    Ui::MainWindow *ui;

    void setBin(int n);

    void setDec(int n);

    void setOct(int n);

    void setHex(int n);

    void setFahrenheit(TemperatureConverter temp);

    void setCelsius(TemperatureConverter temp);

    void setKelvin(TemperatureConverter temp);

    void showErrorBox();

    void clearLayout();

};

#endif // MAINWINDOW_H
