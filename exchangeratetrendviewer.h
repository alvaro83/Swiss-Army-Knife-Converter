#ifndef EXCHANGERATETRENDVIEWER_H
#define EXCHANGERATETRENDVIEWER_H

#include <QDialog>

namespace Ui {
class ExchangeRateTrendViewer;
}

class ExchangeRateTrendViewer : public QDialog
{
    Q_OBJECT

public:
    explicit ExchangeRateTrendViewer(QWidget *parent = 0);
    ~ExchangeRateTrendViewer();

private slots:
    void on_saveButton_clicked();

private:
    Ui::ExchangeRateTrendViewer *ui;
};

#endif // EXCHANGERATETRENDVIEWER_H
