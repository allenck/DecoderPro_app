#include "sensorentrywidget.h"
#include "ui_sensorentrywidget.h"
#include "namedicon.h"
#include "proxysensormanager.h"
#include "instancemanager.h"
#include "multisensoricon.h"

SensorEntryWidget::SensorEntryWidget(int iconNum, MultiSensorIconEntry* entry, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorEntryWidget)
{
 ui->setupUi(this);
 setIconNum(iconNum);
 this->_entry = entry;
 this->_icon = entry->icon;
 ui->iconButton->setIcon(QPixmap::fromImage(_icon->getImage()));
 connect(ui->iconButton, SIGNAL(iconChanged(NamedIcon*)), this, SLOT(on_iconChanged(NamedIcon*)));
 if(entry->namedSensor == NULL)
 {
  this->_sensor = "";
  ui->edSensor->setText(tr("undefined"));
 }
 else
 {
  this->_sensor = entry->namedSensor->getName();
  ui->edSensor->setText(_sensor);
 }
 connect(ui->edSensor, SIGNAL(sensorChanged(QString)), this, SLOT(on_edSensor_textChanged(QString)));
}

SensorEntryWidget::~SensorEntryWidget()
{
    delete ui;
}
void SensorEntryWidget::on_edSensor_textChanged(QString text)
{
 if(text == "")
 {
  ui->edSensor->setText(tr("undefined"));
  return;
 }
 _sensor = text;
 _entry->namedSensor=  ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(_sensor, ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(_sensor));
 emit entryChanged(_iconNum, _entry);
}

int SensorEntryWidget::iconNum() { return _iconNum;}
NamedIcon* SensorEntryWidget::icon() { return _icon;}

void SensorEntryWidget::setIconNum(int iconNum)
{
 _iconNum = iconNum;
 ui->labelPosition->setText(tr("Position %1").arg(iconNum+1));
}
QString SensorEntryWidget::sensor()
{
 if(ui->edSensor->text() == tr("undefined"))
   _sensor = "";
 else
   _sensor = ui->edSensor->text();
 return _sensor;
}
MultiSensorIconEntry* SensorEntryWidget::entry() {return _entry;}
void SensorEntryWidget::on_iconChanged(NamedIcon *icon)
{
 _entry->icon = icon;
 emit entryChanged(_iconNum, _entry);
}
void SensorEntryWidget::on_btnDelete_clicked() { emit deleteRequested(_iconNum);}
