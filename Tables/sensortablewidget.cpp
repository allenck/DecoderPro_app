
#include "sensortablewidget.h"
#include "ui_sensortablewidget.h"
#include "instancemanager.h"
#include "abstractsensor.h"
#include "lnsensor.h"
#include "../LayoutEditor/systemnamecomparator.h"
#include "sensortableaction.h"
#include "../LayoutEditor/sensortabledatamodel.h"
#include <QSortFilterProxyModel>
#include "xtablecolumnmodel.h"

SensorTableWidget::SensorTableWidget(int iMgr, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorTableWidget)
{
 ui->setupUi(this);
 //this->bInternal = bInternal;
 this->iMgr = iMgr;
 mgr = (ProxySensorManager*)InstanceManager::sensorManagerInstance();
 action = new SensorTableAction("Sensor Table", this);
 if(iMgr >= 0)
 {
  action->m = new SensorTableDataModel((SensorManager*)mgr->getMgr(iMgr),this);
  action->setManager((Manager*)mgr->getMgr(iMgr));
  ((SensorTableDataModel*)action->m)->updateNameList();
 }
 else
 {
  action->m = new SensorTableDataModel((SensorManager*)mgr,this);
  action->setManager((Manager*)mgr);
  ((SensorTableDataModel*)action->m)->updateNameList();
 }
// ui->tableWidget->clearContents();
// rows.clear();
// stateMapper = new QSignalMapper(this);
// deleteMapper = new QSignalMapper(this);
// invertedMapper = new QSignalMapper(this);
// delayMapper = new QSignalMapper(this);
// fillTable();
 //action->createModel();
 QSortFilterProxyModel* sorter = new QSortFilterProxyModel();
 sorter->setSourceModel(action->m);
 //ui->verticalLayout->removeWidget(ui->tableView);
 //ui->tableView = ((SensorTableDataModel*)action->m)->makeJTable(sorter);
 ui->tableView->setModel(sorter);
 ui->tableView->setColumnModel(new XTableColumnModel());
 //ui->verticalLayout->addWidget(ui->tableView);
 ((SensorTableDataModel*)action->m)->setColumnToHoldButton(ui->tableView, SensorTableDataModel::DELETECOL);

 //ui->tableView->setModel(action->m);
 ((SensorTableDataModel*)action->m)->configureTable(ui->tableView);
 ((SensorTableDataModel*)action->m)->setPersistentButtons();
}

SensorTableWidget::~SensorTableWidget()
{
    delete ui;
}
void SensorTableWidget::showDebounceInfo(bool bVisible)
{
// for(int col = 6; col <=8; col ++)
//  ui->tableWidget->setColumnHidden(col,!bVisible);
    ((SensorTableDataModel*)action->m)->table = ui->tableView;
    action->showDebounceChanged(bVisible);
}
