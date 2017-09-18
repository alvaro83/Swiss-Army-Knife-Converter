#ifndef EXCHANGERATETRENDSELECTOR_H
#define EXCHANGERATETRENDSELECTOR_H

#include <QDialog>

namespace Ui {
class ExchangeRateTrendSelector;
}

class ExchangeRateTrendSelector : public QDialog
{
    Q_OBJECT

public:
    explicit ExchangeRateTrendSelector(QWidget *parent = 0);
    ExchangeRateTrendSelector(QDate startSelectedDate,
                              QDate endSelectedDate,
                              QWidget *parent);
    ~ExchangeRateTrendSelector();
    QDate getInitialDate();
    QDate getEndDate();
    QString getOriginCurrency();
    QString getDestinationCurrency();

private:
    Ui::ExchangeRateTrendSelector *ui;
    QStringList currencies = QStringList() << "EUR" << "USD" << "JPY";
};

#endif // EXCHANGERATETRENDSELECTOR_H
