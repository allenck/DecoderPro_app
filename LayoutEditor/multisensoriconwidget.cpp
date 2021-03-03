#include "multisensoriconwidget.h"
#include "ui_multisensoriconwidget.h"
#include "proxysensormanager.h"
#include "abstractsensor.h"
#include "multisensoricon.h"
#include "namedicon.h"
#include <QPixmap>
#include "instancemanager.h"
#include "sensorentrywidget.h"
#include "namedicon.h"
#include <QSignalMapper>
#include "actionlistener.h"
#include "abstractsensormanager.h"

MultiSensorIconWidget::MultiSensorIconWidget(MultiSensorIcon* icon, Editor* editor, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultiSensorIconWidget)
{
 ui->setupUi(this);
 this->editor = editor;
 _icon = icon;
 ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
 ui->tableWidget->resizeColumnToContents(0);

 fillSensorTable();
 widgets = QList<SensorEntryWidget*>();
 ui->pbInconsistent->setIcon(QPixmap::fromImage( _icon->getInconsistentIcon()->getImage()));
 ui->pbUnknown->setIcon(QPixmap::fromImage( _icon->getUnknownIcon()->getImage()));
 ui->pbInactive->setIcon(QPixmap::fromImage( _icon->getInactiveIcon()->getImage()));
 ui->rbUpDown->setChecked(_icon->getUpDown());
 connect(ui->pbInconsistent, SIGNAL(iconChanged(NamedIcon*)), _icon, SLOT(setInconsistentIcon(NamedIcon*)));
 connect(ui->pbUnknown, SIGNAL(iconChanged(NamedIcon*)), _icon, SLOT(setUnknownIcon(NamedIcon*)));
 connect(ui->pbInactive, SIGNAL(iconChanged(NamedIcon*)), _icon, SLOT(setInactiveIcon(NamedIcon*)));

 //mapper = new QSignalMapper();
 if(_icon->getNumEntries() > 0)
 {
  for(int i= 0; i < _icon->getNumEntries(); i++)
  {
   NamedIcon* namedIcon = _icon->getSensorIcon(i);
//   SensorEntryWidget* sensorEntryWidget = new SensorEntryWidget(i, _icon->entries->at(i));
//   widgets.append(sensorEntryWidget);
//   ui->gridLayout->setColumnMinimumWidth(i, sensorEntryWidget->width());
//   ui->gridLayout->addWidget(sensorEntryWidget, i/3, i%3,1, 1, Qt::AlignCenter);
//   //mapper->setMapping(sensorEntryWidget,i);
//   connect(sensorEntryWidget, SIGNAL(entryChanged(int, MultiSensorIconEntry*)), this, SLOT(on_entryChanged(int, MultiSensorIconEntry*)));
//   connect(sensorEntryWidget, SIGNAL(deleteRequested(int)), this, SLOT(on_deleteRequested(int)));
  }
 }
 bValid = true;
 int i = 0;
 foreach (SensorEntryWidget* sensorEntryWidget, widgets)
 {
  if(sensorEntryWidget->sensor() == "") bValid = false;
  connect(sensorEntryWidget, SIGNAL(entryChanged(int,MultiSensorIconEntry*)), this, SLOT(on_entryChanged(int,MultiSensorIconEntry*)));
  connect(sensorEntryWidget, SIGNAL(deleteRequested(int)), this, SLOT(on_deleteRequested(int)));

 }
}
MultiSensorIconWidget::~MultiSensorIconWidget()
{
    delete ui;
}
void MultiSensorIconWidget::fillSensorTable()
{
 ProxySensorManager* mgr = (ProxySensorManager*)InstanceManager::sensorManagerInstance();

 for(int i=0; i < mgr->mgrs.count(); i++)
 {
  AbstractSensorManager* sMgr = (AbstractSensorManager*)mgr->mgrs.at(i);
  connect(sMgr, SIGNAL(newSensorCreated(AbstractSensorManager*,Sensor*)), this, SLOT(on_newSensorCreated(AbstractSensorManager*,Sensor*)));
  connect(sMgr, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));
  int row = ui->tableWidget->rowCount();
  QStringList list = sMgr->getSystemNameList();
  ui->tableWidget->setRowCount(row + list.count());
  ui->tableWidget->setAlternatingRowColors(true);
  ui->tableWidget->resizeColumnsToContents();
  ui->tableWidget->verticalHeader()->setHidden(true);

  foreach (QString sysName, list)
  {
   AbstractSensor* s = (AbstractSensor*)sMgr->getBySystemName(sysName);
   QTableWidgetItem* sn = new QTableWidgetItem(s->getSystemName());
   ui->tableWidget->setItem(row, 0,sn);
   QTableWidgetItem* un = new QTableWidgetItem(s->getUserName());
   ui->tableWidget->setItem(row, 1, un);
   rows.append(s);
   row++;
  }
 }
}
void MultiSensorIconWidget::on_tableWidget_cellClicked(int row, int col)
{
 QObject* o = rows.at(row);
 QTableWidgetItem* item = ui->tableWidget->item(row, col);
 if(item!= NULL)
 {
  if(item->text() == "") return;
  QDrag *dr = new QDrag(this);
  // The data to be transferred by the drag and drop operation is contained in a QMimeData object
  QMimeData *data = new QMimeData;
  data->setText(item->text());
  // Assign ownership of the QMimeData object to the QDrag object.
  dr->setMimeData(data);
  // Start the drag and drop operation
  dr->start();
 }
}
void  MultiSensorIconWidget::setIcon(MultiSensorIcon *icon)
{
 _icon = icon;
 foreach (SensorEntryWidget* o, widgets)
 {
  ui->gridLayout->removeWidget((QWidget*)o);
  delete o;
 }
 widgets.clear();
 ui->pbInconsistent->setIcon(QPixmap::fromImage( _icon->getInconsistentIcon()->getImage()));
 ui->pbUnknown->setIcon(QPixmap::fromImage( _icon->getUnknownIcon()->getImage()));
 ui->pbInactive->setIcon(QPixmap::fromImage( _icon->getInactiveIcon()->getImage()));
 ui->rbUpDown->setChecked(_icon->getUpDown());
 ui->rbRightLeft->setChecked(!_icon->getUpDown());

 for(int i= 0; i < _icon->getNumEntries(); i++)
 {
  NamedIcon* namedIcon = _icon->getSensorIcon(i);
//  SensorEntryWidget* sensorEntryWidget = new SensorEntryWidget(i, _icon->entries->at(i));
//  widgets.append(sensorEntryWidget);
//  ui->gridLayout->setColumnMinimumWidth(i, sensorEntryWidget->width());
//  ui->gridLayout->addWidget(sensorEntryWidget, i/3, i%3,1, 1, Qt::AlignCenter);
//  //mapper->setMapping(sensorEntryWidget,i);
//  connect(sensorEntryWidget, SIGNAL(entryChanged(int, MultiSensorIconEntry*)), this, SLOT(on_entryChanged(int, MultiSensorIconEntry*)));
//  connect(sensorEntryWidget, SIGNAL(deleteRequested(int)), this, SLOT(on_deleteRequested(int)));
 }
}

void MultiSensorIconWidget::on_entryChanged(int /*iconNum*/, MultiSensorIconEntry* /*entry*/)
{
// if(_icon->entries->count()<= iconNum)
//  _icon->entries->append(entry);
// else
// _icon->entries->replace(iconNum,entry);
 bValid = true;
 foreach (SensorEntryWidget* w, widgets)
 {
  if(w->entry()->namedSensor == NULL)
  {
   bValid = false;
   break;
  }
 }
 _icon->displayState();
 emit iconValid(bValid);
}
bool MultiSensorIconWidget::on_btnChangeIcon_clicked()
{
 if(ui->tableWidget->isVisible())
 {
  ui->tableWidget->setVisible(false);
  return true;
 }
 else
 {
  ui->tableWidget->setVisible(true);
  return false;
 }
}
void MultiSensorIconWidget::on_rbUpDown_toggled(bool bChecked)
{
 _icon->setUpDown(bChecked);
}
void MultiSensorIconWidget::on_pbAddIcon_clicked()
{
 int iconNum = _icon->entries->count();
 SensorEntryWidget* sensorEntryWidget = new SensorEntryWidget(iconNum, new MultiSensorIconEntry(new NamedIcon("program:resources/icons/misc/X-red.gif","program:resources/icons/misc/X-red.gif"),NULL));
 widgets.append(sensorEntryWidget);
 ui->gridLayout->setColumnMinimumWidth(0, sensorEntryWidget->width());
 ui->gridLayout->addWidget(sensorEntryWidget, iconNum/3, iconNum%3, 1,1, Qt::AlignCenter);
 _icon->addEntry("", sensorEntryWidget->icon());
 connect(sensorEntryWidget, SIGNAL(entryChanged(int,MultiSensorIconEntry*)), this, SLOT(on_entryChanged(int,MultiSensorIconEntry*)));
 connect(sensorEntryWidget, SIGNAL(deleteRequested(int)), this, SLOT(on_deleteRequested(int)));
}
void MultiSensorIconWidget::on_deleteRequested(int index)
{
 foreach (SensorEntryWidget* o, widgets)
 {
  ui->gridLayout->removeWidget((QWidget*)o);
 }
 widgets.removeAt(index);
 _icon->entries->removeAt(index);
 for(int i= 0; i < widgets.count(); i++)
 {
  ui->gridLayout->addWidget(widgets.at(i), i/3, i%3,1, 1, Qt::AlignCenter);
  widgets.at(i)->setIconNum(i);
 }
}
void MultiSensorIconWidget::on_newSensorCreated(AbstractSensorManager *, Sensor *sensor)
{
 int row = ui->tableWidget->rowCount();
 ui->tableWidget->setRowCount(row+1);
 AbstractSensor* s = (AbstractSensor*)sensor;
 QTableWidgetItem* sn = new QTableWidgetItem(s->getSystemName());
 ui->tableWidget->setItem(row, 0,sn);
 QTableWidgetItem* un = new QTableWidgetItem(s->getUserName());
 ui->tableWidget->setItem(row, 1, un);
 rows.append(s);
}
void MultiSensorIconWidget::propertyChange(PropertyChangeEvent * e)
{
 if(e->getPropertyName() == "length")
 {
  ui->tableWidget->clear();
  fillSensorTable();
 }
}
