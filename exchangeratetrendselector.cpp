#include "exchangeratetrendselector.h"
#include "ui_exchangeratetrendselector.h"
#include <QDate>

ExchangeRateTrendSelector::ExchangeRateTrendSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExchangeRateTrendSelector)
{
    ui->setupUi(this);
    ui->calendarWidget->setMaximumDate(QDate::currentDate());
    ui->calendarWidget_2->setMaximumDate(QDate::currentDate());
    ui->calendarWidget_2->setSelectedDate(QDate::currentDate());
    ui->comboBox->addItems(currencies);
    ui->comboBox_2->addItems(currencies);
}

ExchangeRateTrendSelector::ExchangeRateTrendSelector(QDate startSelectedDate,
                                                     QDate endSelectedDate,
                                                     QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExchangeRateTrendSelector)
{
    ui->setupUi(this);
    ui->calendarWidget->setMaximumDate(QDate::currentDate());
    ui->calendarWidget_2->setMaximumDate(QDate::currentDate());
    ui->calendarWidget->setSelectedDate(startSelectedDate);
    ui->calendarWidget_2->setSelectedDate(endSelectedDate);
    ui->comboBox->addItems(currencies);
    ui->comboBox_2->addItems(currencies);
}

ExchangeRateTrendSelector::~ExchangeRateTrendSelector()
{
    delete ui;
}

QDate ExchangeRateTrendSelector::getInitialDate()
{
    return ui->calendarWidget->selectedDate();
}

QDate ExchangeRateTrendSelector::getEndDate()
{
    return ui->calendarWidget_2->selectedDate();
}

QString ExchangeRateTrendSelector::getOriginCurrency()
{
    return ui->comboBox->currentText();
}

QString ExchangeRateTrendSelector::getDestinationCurrency()
{
    return ui->comboBox_2->currentText();
}
