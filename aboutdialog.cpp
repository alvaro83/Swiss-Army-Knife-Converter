#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->label_2->setText("<a href=\"mailto:alvaro.g.arroyo@gmail.com?subject=Swiss Army Knife Converter on Github\">Alvaro Gonzalez Arroyo</a>");
    ui->label_2->setOpenExternalLinks(true);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
