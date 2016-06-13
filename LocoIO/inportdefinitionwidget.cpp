#include "inportdefinitionwidget.h"
#include "ui_inportdefinitionwidget.h"

InPortDefinitionWidget::InPortDefinitionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InPortDefinitionWidget)
{
    ui->setupUi(this);
}

InPortDefinitionWidget::~InPortDefinitionWidget()
{
    delete ui;
}
void InPortDefinitionWidget::retranslateControls()
{
 ui->retranslateUi(this);
}
void InPortDefinitionWidget::setServoOpt()
{
 ui->lblDoubleInput->setText("");
}
