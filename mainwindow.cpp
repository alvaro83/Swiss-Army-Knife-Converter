#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "temperatureconverter.h"
#include <QMessageBox>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>

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

void MainWindow::clearLayout()
{
    for (auto widget: ui->centralWidget->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly))
        delete widget;
}

/* SETTERS */
void MainWindow::setBin(int n)
{
    QString bin;
    bin.setNum(n, 2);
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_bin")->setText(bin);
}

void MainWindow::setDec(int n)
{
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_dec")->setText(QString::number(n));
}

void MainWindow::setOct(int n)
{
    QString octal;
    octal.setNum(n, 8);
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_oct")->setText(octal);
}

void MainWindow::setHex(int n)
{
    QString hex;
    hex.setNum(n, 16);
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_hex")->setText(hex);
}

void MainWindow::setFahrenheit(TemperatureConverter temp)
{
    QString str_f;
    str_f.setNum(temp.getFahrenheit(), '.', 1);
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_fahrenheit")->setText(str_f);
}

void MainWindow::setCelsius(TemperatureConverter temp)
{
    QString str_c;
    str_c.setNum(temp.getCelsius(), '.', 1);
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_celsius")->setText(str_c);
}

void MainWindow::setKelvin(TemperatureConverter temp)
{
    QString str_k;
    str_k.setNum(temp.getKelvin(), '.', 2);
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_kelvin")->setText(str_k);
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
    QString str = ui->centralWidget->findChild<QLineEdit*>("lineEdit_bin")->text();
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_dec")->clear();
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_oct")->clear();
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_hex")->clear();

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
    QString str = ui->centralWidget->findChild<QLineEdit*>("lineEdit_dec")->text();
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_bin")->clear();
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_oct")->clear();
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_hex")->clear();

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
    QString str = ui->centralWidget->findChild<QLineEdit*>("lineEdit_oct")->text();
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_bin")->clear();
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_dec")->clear();
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_hex")->clear();

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
    QString str = ui->centralWidget->findChild<QLineEdit*>("lineEdit_hex")->text();
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_bin")->clear();
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_dec")->clear();
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_oct")->clear();

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
    QString str = ui->centralWidget->findChild<QLineEdit*>("lineEdit_celsius")->text();
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_fahrenheit")->clear();
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_kelvin")->clear();

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
    QString str = ui->centralWidget->findChild<QLineEdit*>("lineEdit_fahrenheit")->text();
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_celsius")->clear();
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_kelvin")->clear();

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
    QString str = ui->centralWidget->findChild<QLineEdit*>("lineEdit_kelvin")->text();
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_celsius")->clear();
    ui->centralWidget->findChild<QLineEdit*>("lineEdit_fahrenheit")->clear();

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

/* MENU ACTIONS */
void MainWindow::on_actionBinary_Decimal_Octal_Hexadecimal_triggered()
{
    clearLayout();

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

    ui->centralWidget->layout()->addWidget(label);
    ui->centralWidget->layout()->addWidget(lineEdit);
    ui->centralWidget->layout()->addWidget(label_2);
    ui->centralWidget->layout()->addWidget(lineEdit_2);
    ui->centralWidget->layout()->addWidget(label_3);
    ui->centralWidget->layout()->addWidget(lineEdit_3);
    ui->centralWidget->layout()->addWidget(label_4);
    ui->centralWidget->layout()->addWidget(lineEdit_4);

    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(on_lineEdit_bin_returnPressed()));
    connect(lineEdit_2, SIGNAL(returnPressed()), this, SLOT(on_lineEdit_dec_returnPressed()));
    connect(lineEdit_3, SIGNAL(returnPressed()), this, SLOT(on_lineEdit_oct_returnPressed()));
    connect(lineEdit_4, SIGNAL(returnPressed()), this, SLOT(on_lineEdit_hex_returnPressed()));
}

void MainWindow::on_actionCelsius_Fahrenheit_Kelvin_triggered()
{
    clearLayout();

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

    ui->centralWidget->layout()->addWidget(label);
    ui->centralWidget->layout()->addWidget(lineEdit);
    ui->centralWidget->layout()->addWidget(label_2);
    ui->centralWidget->layout()->addWidget(lineEdit_2);
    ui->centralWidget->layout()->addWidget(label_3);
    ui->centralWidget->layout()->addWidget(lineEdit_3);

    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(on_lineEdit_celsius_returnPressed()));
    connect(lineEdit_2, SIGNAL(returnPressed()), this, SLOT(on_lineEdit_fahrenheit_returnPressed()));
    connect(lineEdit_3, SIGNAL(returnPressed()), this, SLOT(on_lineEdit_kelvin_returnPressed()));
}
