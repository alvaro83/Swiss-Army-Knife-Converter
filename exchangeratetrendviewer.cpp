#include "exchangeratetrendviewer.h"
#include "ui_exchangeratetrendviewer.h"
#include <QMessageBox>
#include <QPixmap>
#include <QFileDialog>

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
    QString saveFilename = QFileDialog::getSaveFileName(this, "Save as", "Choose a filename", "PNG(*.png);; TIFF(*.tiff *.tif);; JPEG(*.jpg *.jpeg)");

    if (saveFilename != NULL)
    {
        QString saveExtension = "PNG";
        int pos = saveFilename.lastIndexOf('.');

        if (pos >= 0)
            saveExtension = saveFilename.mid(pos + 1);

        if(!QPixmap::grabWidget(ui->rateViewer).save(saveFilename, qPrintable(saveExtension)))
        {
            QMessageBox::warning(this, "Warning", "File could not be saved", QMessageBox::Ok);
        }
    }
}
