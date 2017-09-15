#include "blockwidget.h"
#include "ui_blockwidget.h"
#include "instancemanager.h"
#include "block.h"
#include "abstractreporter.h"
#include <QButtonGroup>
#include "instancemanager.h"
#include "addeditdialog.h"
#include "rosterentry.h"
#include "blocktableaction.h"
#include <QSortFilterProxyModel>
#include "xtablecolumnmodel.h"

BlockWidget::BlockWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockWidget)
{
 ui->setupUi(this);
// ui->tableWidget->clearContents();
// ui->tableWidget->verticalHeader()->setHidden(true);
 //rows.clear();
// deleteMapper = new QSignalMapper(this);
// curvatureMapper = new QSignalMapper(this);
// sensorMapper = new QSignalMapper(this);
// chkUseCurrentMapper = new QSignalMapper(this);
// chkPermissiveMapper = new QSignalMapper(this);
// speedMapper = new QSignalMapper(this);
 BlockTableDataModel* model = new BlockTableDataModel(ui->chkInches,NULL);
 QSortFilterProxyModel* sorter = new QSortFilterProxyModel();
 sorter->setSourceModel(model);
 ui->tableView->setModel(sorter);
 ui->tableView->setColumnModel(new XTableColumnModel());
 model->configureTable(ui->tableView);

// mgr = (BlockManager*)InstanceManager::blockManagerInstance();
// connect(mgr, SIGNAL(newBlockCreated(Block*)), this, SLOT(on_newBlockCreated(Block*)));
// int row = ui->tableWidget->rowCount();
// QStringList list = mgr->getSystemNameList();
// ui->tableWidget->setRowCount(row + list.count());
// ui->tableWidget->setColumnCount(15);
// ui->tableWidget->setAlternatingRowColors(true);
 QButtonGroup* group = new QButtonGroup(this);
 group->addButton(ui->chkInches);
 group->addButton(ui->chlCentimeters);
 group->setExclusive(true);
 ui->chkInches->setChecked(true); // TODO: make this a preference

 model->setPersistentButtons();

// foreach (QString sysName, list)
// {
//  Block* b = (Block*)mgr->getBySystemName(sysName);
//  rows.append(b);
//  updateRow(row, b);
////  PropertyChangeListener* listener;
////  b->addPropertyChangeListener(listener = new PropertyChangeListener());
//  connect(b->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//  row++;
// }
// ui->tableWidget->resizeColumnsToContents();
// connect(ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(on_tableWidget_cellChanged(int,int)));
// connect(deleteMapper, SIGNAL(mapped(QObject*)), this, SLOT(on_deleteMapper_clicked(QObject*)));
// connect(curvatureMapper, SIGNAL(mapped(QObject*)), this, SLOT(on_curvatureMapper_indexChanged(QObject*)));
// connect(sensorMapper, SIGNAL(mapped(QObject*)), this, SLOT(on_sensorMapper_indexChanged(QObject*)));
// connect(chkUseCurrentMapper, SIGNAL(mapped(QObject*)), this, SLOT(on_chkUseCurrentMapper_toggled(QObject*)));
// connect(chkPermissiveMapper, SIGNAL(mapped(QObject*)), this, SLOT(on_chkPermissiveMapper_toggled(QObject*)));
// connect(speedMapper, SIGNAL(mapped(QObject*)), this, SLOT(on_speedMapper_indexChanged(QObject*)));
}
//void BlockWidget::updateRow(int row, Block* b)
//{
//  QTableWidgetItem* sn = new QTableWidgetItem(b->getSystemName());
//  sn->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
//  ui->tableWidget->setItem(row, 0,sn);
//  QTableWidgetItem* un = new QTableWidgetItem(b->getUserName());
//  ui->tableWidget->setItem(row, 1, un);
//  QVariant value = b->getValue();
//  QTableWidgetItem* r = new QTableWidgetItem("");
//  if(!value.isNull())
//  {
//   RosterEntry* re = VPtr<RosterEntry>::asPtr(value);
//   r->setText(re->getRoadNumber());
//  }
//  ui->tableWidget->setItem(row, 2, r);

//  QTableWidgetItem* comment = new QTableWidgetItem(b->getComment());
//  ui->tableWidget->setItem(row, 3, comment);
//  QPushButton* btn = new QPushButton();
//  btn->setText(tr("Delete"));
//  connect(btn, SIGNAL(clicked()), deleteMapper, SLOT(map()));
//  deleteMapper->setMapping(btn, b);
//  ui->tableWidget->setCellWidget(row,4,btn);
//  QTableWidgetItem* direction = new QTableWidgetItem(b->getDirection());
//  ui->tableWidget->setItem(row, 5, direction);
//  QTableWidgetItem* length;
//  if(ui->chkInches->isChecked())
//   length = new QTableWidgetItem(QString("%1").arg(b->getLengthIn()));
//  else
//   length = new QTableWidgetItem(QString("%1").arg(b->getLengthCm()));
//  ui->tableWidget->setItem(row, 6, length);
//  QComboBox* cbCurvature = new QComboBox();
//  connect(cbCurvature, SIGNAL(currentIndexChanged(int)), curvatureMapper, SLOT(map()));
//  curvatureMapper->setMapping(cbCurvature, b);
//  QStringList list;
//  list << tr("None") << tr("Gradual") << tr("Tight") << tr("Severe");
//  cbCurvature->addItems(list);
//  int iCurve;
//  switch (b->getCurvature())
//  {
//  default:
//  case Block::NONE:
//   iCurve = 0;
//   break;
//  case Block::GRADUAL:
//   iCurve = 1;
//   break;
//  case Block::TIGHT:
//   iCurve = 2;
//   break;
//  case Block::SEVERE:
//   iCurve = 3;
//   break;
//  }
//  cbCurvature->setCurrentIndex(iCurve);
//  ui->tableWidget->setCellWidget(row, 7, cbCurvature);
//  QString sState;
//  switch(b->getState())
//  {
//   case Sensor::ACTIVE:
//    sState = "Occupied";
//    break;
//   case Sensor::INACTIVE:
//    sState = "UnOccupied";
//    break;
//   default:
//    sState = "Unknown";
//    break;
//  }
//  QTableWidgetItem* state = new QTableWidgetItem(sState);
//  ui->tableWidget->setItem(row, 8, state);
//  QComboBox* sensorCb = cbSensor(b->getSensor()!= NULL?b->getSensor()->getSystemName():"");
//  connect(sensorCb, SIGNAL(currentIndexChanged(int)), sensorMapper, SLOT(map()));
//  sensorMapper->setMapping(sensorCb,b);
//  ui->tableWidget->setCellWidget(row,9,sensorCb);
//  QTableWidgetItem* sensor = new QTableWidgetItem((b->getSensor()!= NULL?b->getSensor()->getSystemName():""));
//  ui->tableWidget->setItem(row, 14, sensor);
//  if(b->getReporter() != NULL)
//  {
//   QTableWidgetItem* reporter = new QTableWidgetItem(((AbstractReporter*)b->getReporter())->getSystemName());
//   ui->tableWidget->setItem(row, 10, reporter);
//  }
//  QCheckBox* chkUseCurrent = new QCheckBox();
//  connect(chkUseCurrent, SIGNAL(toggled(bool)), chkUseCurrentMapper, SLOT(map()));
//  chkUseCurrentMapper->setMapping(chkUseCurrent, b);
//  chkUseCurrent->setChecked(b->isReportingCurrent());
//  //chkUseCurrent->setChecked(b->);
//  ui->tableWidget->setCellWidget(row, 11, chkUseCurrent);
//  QCheckBox* chkPermissive = new QCheckBox();
//  chkPermissive->setChecked(b->getPermissiveWorking());
//  connect(chkPermissive, SIGNAL(toggled(bool)), chkPermissiveMapper, SLOT(map()));
//  chkPermissiveMapper->setMapping(chkPermissive,b);
//  ui->tableWidget->setCellWidget(row, 12, chkPermissive);
//  QComboBox* speed = new QComboBox();
//  QStringList speedList;
//  speedList << tr("Use Global Normal") << tr("Maximum") << tr("Normal") << tr("Limited") << tr("Medium") << tr("Slow") << tr("Restricted") << tr("Stop");
//  speed->addItems(speedList);
//  connect(speed, SIGNAL(currentIndexChanged(int)), speedMapper, SLOT(map()));
//  speedMapper->setMapping(speed, b);
//  QString sSpeed = b->getBlockSpeed();
//  int iSpeed = speed->findText(sSpeed);
//  if(iSpeed>=0)
//   speed->setCurrentIndex(speed->findText(sSpeed));
//  ui->tableWidget->setCellWidget(row, 13, speed);
//  row++;
//}

BlockWidget::~BlockWidget()
{
    delete ui;
}
//QComboBox* BlockWidget::cbSensor(QString sensorName)
//{
// QComboBox* box = new QComboBox();
// AbstractSensorManager* mgr = (AbstractSensorManager*)InstanceManager::sensorManagerInstance();
// QStringList list = mgr->getSystemNameList();
// box->addItem("");
// box->addItems(list);

// if(sensorName != "")
//  box->setCurrentIndex(box->findText(sensorName));
// return box;
//}
//void BlockWidget::propertyChange(PropertyChangeEvent *e)
//{
// qDebug()<< "property change received" + e->toString();
// Block* bTarget = qobject_cast<Block*>(e->source);
// for(int row =0; row<rows.count(); row++)
// {
//  Block* b = rows.at(row);
//  if(b == bTarget)
//  {
//   updateRow(row, b);
//   break;
//  }
// }
//}
//void BlockWidget::on_chkInches_toggled(bool bState)
//{
// for(int row = 0; row < rows.count(); row++)
// {
//  QTableWidgetItem* item = ui->tableWidget->item(row,6);
//  Block* b = rows.at(row);
//  if(bState)
//   item->setText(QString("%1").arg(b->getLengthIn()));
//  else
//   item->setText(QString("%1").arg(b->getLengthCm()));
// }
//}
//void BlockWidget::on_newBlockCreated(Block *b)
//{
//  int row = ui->tableWidget->rowCount();
//  ui->tableWidget->setRowCount(row +1);
//  updateRow(row, b);
//  rows.append(b);
//}
//void BlockWidget::on_tableWidget_cellChanged(int row, int col)
//{
// if(rows.isEmpty()) return;
// if(row == rows.count()) return;
// Block* b = rows.at(row);
// switch(col)
// {
//  case 1: // user name
//   b->setUserName(ui->tableWidget->item(row,col)->text());
//   break;
//  case 2: //value
//  {
//   QTableWidgetItem* bval = ui->tableWidget->item(row, col);

//   QVariant value = b->getValue();
//   if(!value.isNull())
//   {
//    RosterEntry* re = VPtr<RosterEntry>::asPtr(value);
//    bval->setText(re->getRoadNumber());
//   }
//   else
//    bval->setText("");
//   break;
//  }
//  case 3:
//  {
//   b->setComment(ui->tableWidget->item(row,col)->text());
//   break;
//  }
//  //case 4:  delete
//  case 5: // direction
//  {
//   break;
//  }
//  case 6: // length
//  {
//   bool bOk=false;
//   float val = ui->tableWidget->item(row,col)->text().toFloat(&bOk);
//   if(bOk)
//   {
//    if(ui->chkInches->isChecked())
//     b->setLength(val*25.4); // length is stored im millimeters.
//    else
//     b->setLength(val*10.0);
//   }
//   else
//   {
//    QTableWidgetItem* length;
//    if(ui->chkInches->isChecked())
//     length = new QTableWidgetItem(QString("%1").arg(b->getLengthIn()));
//    else
//     length = new QTableWidgetItem(QString("%1").arg(b->getLengthCm()));
//   }
//   break;
//  }
//  case 8: // State
//  {
//   QString sState;
//   switch(b->getState())
//   {
//      case Sensor::ACTIVE:
//       sState = "Occupied";
//       break;
//      case Sensor::INACTIVE:
//       sState = "UnOccupied";
//       break;
//      default:
//       sState = "Unknown";
//       break;
//   }
//   QTableWidgetItem* state = ui->tableWidget->item(row, col);
//   state->setText(sState);
//   break;
//  }
//  //case 9: // sensor
// case 10: // reporter
//  {
//   QTableWidgetItem* reporter = ui->tableWidget->item(row, col);
//   reporter->setText(((AbstractReporter*)b->getReporter())->getSystemName());
//   break;
//  }
//  //case 11: //Use current
//  //case 12: //Permissive
//  //case 13: // SPEED
//  case 14:
//  {
//   QTableWidgetItem* sensor = ui->tableWidget->item(row, col);
//   sensor->setText((b->getSensor()!= NULL?b->getSensor()->getSystemName():""));
//   break;
//  }
//  default:
//  {
//   break;
//  }
// }
//}
//void BlockWidget::on_btnAdd_clicked()
//{
// AddEditDialog dlg(tr("Blocks"),this);
// if(dlg.exec() == QDialog::Accepted)
// {
//  QString sysName = dlg.systemName();
//  QString userName = dlg.userName();
//  QString sPrefix = mgr->getSystemPrefix()+ mgr->typeLetter();
//  if(dlg.isAddRange())
//  {
//   int count = dlg.numToAdd();
//   int addr = dlg.systemName().toInt();
//   for(int iAddr = addr; iAddr < addr + count -1; iAddr++)
//   {
//    sysName = sPrefix+QString("%1").arg(iAddr);
//    if(dlg.isAutoGen())
//     mgr->createNewBlock(userName+QString("%1").arg(iAddr));
//    else
//     mgr->createNewBlock(sysName, userName+QString("%1").arg(iAddr));
//   }
//  }
//  else
//  {
//   sysName = sPrefix+dlg.systemName();
//   if(dlg.isAutoGen())
//    mgr->createNewBlock(userName);
//   else
//    mgr->createNewBlock(sysName, userName);
//  }
// }
//}
//void BlockWidget::on_deleteMapper_clicked(QObject *o)
//{
// Block* b = (Block*)o;
// int row = rows.indexOf(b);
// if(row >= 0)
// {
//  rows.remove(row);
//  ui->tableWidget->removeRow(row);
//  mgr->deregister(b);
// }
//}
//void BlockWidget::on_curvatureMapper_indexChanged(QObject *o)
//{
// Block* b = (Block*)o;
// int row = rows.indexOf(b);
// if(row >= 0)
// {
//  int i = ((QComboBox*)ui->tableWidget->cellWidget(row, 7))->currentIndex();
//  if(i > 0)
//      b->setCurvature(1<<(i-1));
//  else
//   b->setCurvature(0);
// }
//}
//void BlockWidget::on_sensorMapper_indexChanged(QObject *o)
//{
// Block* b = (Block*)o;
// int row = rows.indexOf(b);
// if(row >= 0)
// {
//  int i = ((QComboBox)ui->tableWidget->cellWidget(row, 7)).currentIndex();
//  Q_UNUSED(i);
//  QString sensorName = ((QComboBox)ui->tableWidget->cellWidget(row, 7)).currentText();
//  b->setSensor(sensorName);
// }
//}
//void BlockWidget::on_chkUseCurrentMapper_toggled(QObject *o)
//{
// Block* b = (Block*)o;
// int row = rows.indexOf(b);
// if(row >= 0)
// {
//   bool bState = ((QCheckBox*)ui->tableWidget->cellWidget(row, 11))->isChecked();
//   b->setReportingCurrent(bState);
// }
//}
//void BlockWidget::on_chkPermissiveMapper_toggled(QObject *o)
//{
// Block* b = (Block*)o;
// int row = rows.indexOf(b);
// if(row >= 0)
// {
//  bool bState = ((QCheckBox*)ui->tableWidget->cellWidget(row, 12))->isChecked();
//  b->setPermissiveWorking(bState);
// }
//}
//void BlockWidget::on_speedMapper_indexChanged(QObject *o)
//{
// Block* b = (Block*)o;
// int row = rows.indexOf(b);
// if(row >= 0)
// {
//  QString s = ((QComboBox*)ui->tableWidget->cellWidget(row, 13))->currentText();
//  b->setBlockSpeed(s);
// }
//}
