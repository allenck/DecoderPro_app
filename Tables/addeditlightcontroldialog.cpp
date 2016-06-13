#include "addeditlightcontroldialog.h"
#include "ui_addeditlightcontroldialog.h"

AddEditLightControlDialog::AddEditLightControlDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEditLightControlDialog)
{
 ui->setupUi(this);
}

AddEditLightControlDialog::~AddEditLightControlDialog()
{
    delete ui;
}
void AddEditLightControlDialog::on_comboBox_currentIndexChanged(int index)
{
 switch(index)
 {
 default:
 case 0: // none
  ui->lblNoControl->setVisible(true);
  ui->lblSensor->setVisible(false);
  ui->edSensor1->setVisible(false);
  ui->edSensor2->setVisible(false);
  ui->lblSensorState->setVisible(false);
  ui->cbSensorState->setVisible(false);
  ui->lblTimeOn->setVisible(false);
  ui->timeEditOn->setVisible(false);
  ui->lblTimeOff->setVisible(false);
  ui->timeEditOff->setVisible(false);
  ui->lblTurnoutName->setVisible(false);
  ui->edTurnout->setVisible(false);
  ui->lblStatusTurnout->setVisible(false);
  ui->cbStatusTurnout->setVisible(false);
  ui->lblTriggerSensor->setVisible(false);
  ui->edTriggerSensor->setVisible(false);
  ui->lblDuration->setVisible(false);
  ui->sbDuration->setVisible(false);
  break;
 case 1: // by sensor
  ui->lblNoControl->setVisible(false);
  ui->lblSensor->setVisible(true);
  ui->edSensor1->setVisible(true);
  ui->edSensor2->setVisible(false);
  ui->lblSensorState->setVisible(false);
  ui->cbSensorState->setVisible(false);
  ui->lblTimeOn->setVisible(false);
  ui->timeEditOn->setVisible(false);
  ui->lblTimeOff->setVisible(false);
  ui->timeEditOff->setVisible(false);
  ui->lblTurnoutName->setVisible(false);
  ui->edTurnout->setVisible(false);
  ui->lblStatusTurnout->setVisible(false);
  ui->cbStatusTurnout->setVisible(false);
  ui->lblTriggerSensor->setVisible(false);
  ui->edTriggerSensor->setVisible(false);
  ui->lblDuration->setVisible(false);
  ui->sbDuration->setVisible(false);
  break;
 case 2: // by fast clock
  ui->lblNoControl->setVisible(false);
  ui->lblSensor->setVisible(false);
  ui->edSensor1->setVisible(false);
  ui->edSensor2->setVisible(false);
  ui->lblSensorState->setVisible(false);
  ui->cbSensorState->setVisible(false);
  ui->lblTimeOn->setVisible(true);
  ui->timeEditOn->setVisible(true);
  ui->lblTimeOff->setVisible(true);
  ui->timeEditOff->setVisible(true);
  ui->lblTurnoutName->setVisible(false);
  ui->edTurnout->setVisible(false);
  ui->lblStatusTurnout->setVisible(false);
  ui->cbStatusTurnout->setVisible(false);
  ui->lblTriggerSensor->setVisible(false);
  ui->edTriggerSensor->setVisible(false);
  ui->lblDuration->setVisible(false);
  ui->sbDuration->setVisible(false);
  break;
 case 3: // by Turnout status
  ui->lblNoControl->setVisible(false);
  ui->lblSensor->setVisible(false);
  ui->edSensor1->setVisible(false);
  ui->edSensor2->setVisible(false);
  ui->lblSensorState->setVisible(false);
  ui->cbSensorState->setVisible(false);
  ui->lblTimeOn->setVisible(false);
  ui->timeEditOn->setVisible(false);
  ui->lblTimeOff->setVisible(false);
  ui->timeEditOff->setVisible(false);
  ui->lblTurnoutName->setVisible(true);
  ui->edTurnout->setVisible(true);
  ui->lblStatusTurnout->setVisible(true);
  ui->cbStatusTurnout->setVisible(true);
  ui->lblTriggerSensor->setVisible(false);
  ui->edTriggerSensor->setVisible(false);
  ui->lblDuration->setVisible(false);
  ui->sbDuration->setVisible(false);
  break;
 case 4: // by timed ON
  ui->lblNoControl->setVisible(false);
  ui->lblSensor->setVisible(false);
  ui->edSensor1->setVisible(false);
  ui->edSensor2->setVisible(false);
  ui->lblSensorState->setVisible(false);
  ui->cbSensorState->setVisible(false);
  ui->lblTimeOn->setVisible(false);
  ui->timeEditOn->setVisible(false);
  ui->lblTimeOff->setVisible(false);
  ui->timeEditOff->setVisible(false);
  ui->lblTurnoutName->setVisible(false);
  ui->edTurnout->setVisible(false);
  ui->lblStatusTurnout->setVisible(false);
  ui->cbStatusTurnout->setVisible(false);
  ui->lblTriggerSensor->setVisible(true);
  ui->edTriggerSensor->setVisible(true);
  ui->lblDuration->setVisible(true);
  ui->sbDuration->setVisible(true);
  break;
 case 5: // byt two sensors
  ui->lblNoControl->setVisible(false);
  ui->lblSensor->setVisible(true);
  ui->edSensor1->setVisible(true);
  ui->edSensor2->setVisible(true);
  ui->lblSensorState->setVisible(true);
  ui->cbSensorState->setVisible(true);
  ui->lblTimeOn->setVisible(false);
  ui->timeEditOn->setVisible(false);
  ui->lblTimeOff->setVisible(false);
  ui->timeEditOff->setVisible(false);
  ui->lblTurnoutName->setVisible(false);
  ui->edTurnout->setVisible(false);
  ui->lblStatusTurnout->setVisible(false);
  ui->cbStatusTurnout->setVisible(false);
  ui->lblTriggerSensor->setVisible(false);
  ui->edTriggerSensor->setVisible(false);
  ui->lblDuration->setVisible(false);
  ui->sbDuration->setVisible(false);
  break;
 }
}
