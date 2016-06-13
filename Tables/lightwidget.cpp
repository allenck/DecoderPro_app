#include "lightwidget.h"
#include "ui_lightwidget.h"
#include "instancemanager.h"
#include "abstractlightmanager.h"
#include "addeditlightdialog.h"

LightWidget::LightWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LightWidget)
{
 ui->setupUi(this);
 ui->tabWidget->clear(); // remove default tabs

 tableWidget1 = new LightTableWidget(false,this); // ALL
 ui->tabWidget->addTab(tableWidget1,tr("All"));
 tableWidget2 = new LightTableWidget(true,this); // Internal only
 ui->tabWidget->addTab(tableWidget2, tr("Internal"));
 setWindowTitle("Lights");
 dlg = NULL;
}

LightWidget::~LightWidget()
{
 delete ui;
}
void LightWidget::on_btnAdd_clicked()
{
 if(dlg == NULL)
  dlg = new AddEditLightDialog(NULL, this);
 dlg->show();
 dlg->raise();
 dlg->activateWindow();
}
