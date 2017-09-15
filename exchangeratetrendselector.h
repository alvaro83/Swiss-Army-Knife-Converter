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
    ~ExchangeRateTrendSelector();
    QDate getInitialDate();
    QDate getEndDate();

private:
    Ui::ExchangeRateTrendSelector *ui;
};

#endif // EXCHANGERATETRENDSELECTOR_H
