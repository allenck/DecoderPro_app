#include "servoregisterswidget.h"
#include "ui_servoregisterswidget.h"

ServoRegistersWidget::ServoRegistersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServoRegistersWidget)
{
    ui->setupUi(this);
}

ServoRegistersWidget::~ServoRegistersWidget()
{
    delete ui;
}
void ServoRegistersWidget::addWidget(RegistersWidget *rw)
{
 ui->HorizontalLayout_registersWidget->addWidget(rw);
}
void ServoRegistersWidget::retranslateControls()
{
 ui->retranslateUi(this);
}
