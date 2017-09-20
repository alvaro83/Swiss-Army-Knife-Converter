#include "exchangeratetrendviewer.h"
#include "ui_exchangeratetrendviewer.h"

ExchangeRateTrendViewer::ExchangeRateTrendViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExchangeRateTrendViewer)
{
    ui->setupUi(this);
}

ExchangeRateTrendViewer::~ExchangeRateTrendViewer()
{
    delete ui;
}

void ExchangeRateTrendViewer::on_saveButton_clicked()
{
    //TODO
}
