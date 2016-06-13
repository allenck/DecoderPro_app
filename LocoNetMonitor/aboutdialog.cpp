#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "libpr3version.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
 ui->setupUi(this);
 ui->label->setText( QString("1.0.%1 %2 %3:%4:%5").arg(VER_BUILDNR).arg(VER_DATE).arg(VER_HOUR).arg(VER_MINUTE).arg(VER_SECOND));
 ui->labelPr3->setText(QString("libPr3 version %1").arg(libPr3Version::buildVersion()));
}

AboutDialog::~AboutDialog()
{
 delete ui;
}
