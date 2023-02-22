#include "turnoutdlg.h"
#include "locoiomode.h"
#include "locoiomodelist.h"
#include "ui_turnoutdlg.h"

TurnoutDlg::TurnoutDlg(LocoIOData* data, int channel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TurnoutDlg)
{
 ui->setupUi(this);
 this->data = data;
 this->channel = channel;
 LocoIOMode* lim = data->getLIM(channel);
 if(lim)
  this->opCode = lim->getOpcode();
 this->v1 = data->getV1(channel);
 this->v2 = data->getV2(channel);
 ui->lblHelp->setText(data->getMode(channel));
 ui->edV1->setText(QString("0x%1").arg(v1, 0, 16));
 ui->edV2->setText(QString("0x%1").arg(v2, 0, 16));
 ui->sbAddr->setMinimum(1);
 ui->chkInputHigh->setChecked(v2 & 0x10);
 ui->sbAddr->setValue((((v2 & 0x0F) << 7) | v1) +1 );
 switch(opCode)
 {
 case 0xB0: // OPC_SW_REQ Req switch function
  setWindowTitle(tr("OPC_SW_REQ values"));
  ui->gbB1Mode->setVisible(false);
  //ui->chkDS54Aux->setText(tr("Closed"));
  ui->chkClosedOn->setVisible(true);
  ui->chkClosedOn->setChecked(v2 & 0x20);
  ui->chkOutputOn->setVisible(true);
  ui->chkOutputOn->setChecked(v2 & 0x10);
  ui->chkInputHigh->setVisible(false);
  ui->gbB1Mode->setVisible(false);
  ui->sbAddr->setMaximum(4096);
  break;
 case 0xB1: // OPC_SW_REP turnout Sensor state report
  setWindowTitle(tr("OPC_SW_REP values"));
  ui->gbB1Mode->setVisible(false);
  ui->gbB1Mode->setVisible(true);
  ui->gbB1Mode->setVisible(true);
  ui->chkClosedOn->setVisible(false);
  ui->chkOutputOn->setVisible(false);
  if(v2 & 0x40)
  {
   ui->rbB1Input->setChecked(true);
   ui->chkOutputOn->setVisible(false);
   ui->chkClosedOn->setVisible(false);
   ui->chkDS54Aux->setText(tr("DS54 Aux Input"));
   ui->chkDS54Aux->setVisible(true);
   ui->chkDS54Aux->setChecked((v2 & 0x20)==0);
   if(v2 & 0x20) // DS54?
     ui->sbAddr->setMaximum(4);
   else
     ui->sbAddr->setMaximum(4096);
  }
  else
  {
   ui->rbB1Output->setChecked(true);
   ui->chkOutputOn->setVisible(true);
   ui->chkClosedOn->setVisible(true);
   ui->chkClosedOn->setChecked(v2 & 0x20);
   ui->chkOutputOn->setChecked(v2 & 0x10);
   ui->sbAddr->setMaximum(4096);
   ui->chkDS54Aux->setVisible(false);
  }
  break;
 case 0xB2: // OPC_INPUT_REP General sensor input codes
  setWindowTitle(tr("OPC_INPUT_REP values"));
  ui->gbB1Mode->setVisible(false);
  ui->chkDS54Aux->setText(tr("DS54 Aux Input"));
  ui->chkClosedOn->setVisible(false);
  ui->chkOutputOn->setVisible(false);
  ui->chkDS54Aux->setVisible(true);
  ui->chkDS54Aux->setChecked((v2 & 0x20)==0);
  if(v2 & 0x20) // DS54?
    ui->sbAddr->setMaximum(4);
  else
    ui->sbAddr->setMaximum(4096);
  ui->chkInputHigh->setVisible(true);
  ui->chkInputHigh->setChecked(v2 & 0x10);
  break;
 default:
  break;
 }
}

TurnoutDlg::~TurnoutDlg()
{
 delete ui;
}


int TurnoutDlg::getV1() { return v1;}
int TurnoutDlg::getV2(){return v2;}
void TurnoutDlg::on_btnCancel_clicked()
{
 reject();
}
void TurnoutDlg::on_btnOK_clicked()
{
 accept();
}
void TurnoutDlg::on_sbAddr_valueChanged(int value)
{
 qApp->processEvents();
 switch(opCode)
 {
 case 0xB0: // OPC_SW_REQ Req switch function
  v1 = (value-1) & 0x7f;
  v2 = (((value -1)& 0x48) >> 7) + 0x00 + (ui->chkClosedOn->isChecked()?0x20:0) + (ui->chkOutputOn->isChecked()?0x10:0);
  break;
 case 0xB1: // OPC_SW_REP turnout Sensor state report
  if(ui->rbB1Input->isChecked())
  {
   v1 = (value-1) & 0x7f;
   v2 = (((value -1)& 0x48) >> 7) + 0x40 + (ui->chkDS54Aux->isChecked()?0x00:0x20) + (ui->chkInputHigh->isChecked()?0x10:0);
  }
  else
  {// set output levels
   v1 = (value-1) & 0x7f;
   v2 = (((value -1)& 0x48) >> 7) + 0x00 + (ui->chkClosedOn->isChecked()?0x20:0) + (ui->chkOutputOn->isChecked()?0x10:0);
  }
  break;
 case 0xB2: // OPC_INPUT_REP General sensor input codes
  v1 = (value-1) & 0x7f;
  v2 = (((value -1)& 0x48) >> 7) + 0x00 + (ui->chkDS54Aux->isChecked()?0x00:0x20) + (ui->chkInputHigh->isChecked()?0x10:0);
  break;
 default:
  break;
 }
 ui->edV1->setText(QString("0x%1").arg(v1, 0, 16));
 ui->edV2->setText(QString("0x%1").arg(v2, 0, 16));
 LocoIOMode* lim = data->getLocoIOModeList()->getLocoIOModeFor(data->getSV(channel), v1, v2);
 if(lim != NULL)
  ui->lblHelp->setText(lim->getMode());
 else
  ui->lblHelp->setText(tr("Unknown or invalid mode!"));
}
void TurnoutDlg::on_chkInputHigh_toggled(bool bChecked)
{
    Q_UNUSED(bChecked)
 on_sbAddr_valueChanged(ui->sbAddr->value());
}
void TurnoutDlg::on_chkDS54Aux_toggled(bool bChecked)
{
 if(bChecked)
 {
  ui->lblAddr->setText(tr("DS54 Aux input:"));
  if(ui->sbAddr->value() > 4)
   ui->sbAddr->setValue(4);
  ui->sbAddr->setMinimum(1);
  ui->sbAddr->setMaximum(4);
 }
 else
 {ui->lblAddr->setText(tr("Address:"));
  ui->sbAddr->setMinimum(1);
  ui->sbAddr->setMaximum(4096);
 }
 on_sbAddr_valueChanged(ui->sbAddr->value());
}
void TurnoutDlg::on_chkClosedOn_toggled(bool bChecked)
{
 Q_UNUSED(bChecked)
 on_sbAddr_valueChanged(ui->sbAddr->value());
}
void TurnoutDlg::on_chkOutputOn_toggled(bool bChecked)
{
 Q_UNUSED(bChecked)
 on_sbAddr_valueChanged(ui->sbAddr->value());
}
