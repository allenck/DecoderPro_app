#include "outportdefinitionwidget.h"
#include "ui_outportdefinitionwidget.h"

OutPortDefinitionWidget::OutPortDefinitionWidget(LocoIOData* data,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutPortDefinitionWidget)
{
 ui->setupUi(this);
 this->data = data;
 bSetting = false;
 connect(ui->sbBlinkRate, SIGNAL(valueChanged(int)), this, SLOT(on_sbBlinkRate_valueChanged(int)));
 setBlinkSb(this->data->getBlinkRate());
}

OutPortDefinitionWidget::~OutPortDefinitionWidget()
{
 delete ui;
}
void OutPortDefinitionWidget::setBlinkSb(int rate)
{
 bSetting = true;
 ui->sbBlinkRate->setValue(rate);
 bSetting = false;
}
void OutPortDefinitionWidget::on_sbBlinkRate_valueChanged(int val)
{
 if(bSetting)
  return;
// int iUnitConfig = data->getUnitConfig();
// int iPortRefresh = iUnitConfig & 0x01;    // bit 0
// int iAltCodePBs = (iUnitConfig & 0x02) >> 1; // bit 1
// int iIsServo = (iUnitConfig & 0x08) >> 3; // bit 3
// int iBlinkRate =  (iUnitConfig & 0xf0) >> 4;
// if(val != iBlinkRate)
// {
////  iAltCodePBs=1;
////  iIsServo = 0;
//  iBlinkRate = val;
//  data->setUnitConfig(iPortRefresh, iAltCodePBs, iIsServo, iBlinkRate);
  data->setBlinkRate(val);
  data->setOption(0, data->getUnitConfig());

// }
}
void OutPortDefinitionWidget::retranslateControls()
{
 ui->retranslateUi(this);
}
