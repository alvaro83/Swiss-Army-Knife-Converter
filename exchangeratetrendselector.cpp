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
