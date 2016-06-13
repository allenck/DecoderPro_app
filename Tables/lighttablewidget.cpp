#include "lighttablewidget.h"
#include "ui_lighttablewidget.h"
#include "instancemanager.h"
#include "abstractlightmanager.h"
#include "abstractlight.h"
#include "addeditlightdialog.h"
#include "../LayoutEditor/systemnamecomparator.h"


LightTableWidget::LightTableWidget(bool bInternal, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LightTableWidget)
{
 ui->setupUi(this);
 this->bInternal = bInternal;
 mgr = (ProxyLightManager*)InstanceManager::lightManagerInstance();
 ui->tableWidget->clearContents();
 ui->tableWidget->verticalHeader()->setHidden(true);
 rows.clear();
 stateMapper = new QSignalMapper(this);
 deleteMapper = new QSignalMapper(this);
 enabledMapper = new QSignalMapper(this);
 editMapper = new QSignalMapper(this);
 if(!this->bInternal)
 {
  for(int i=0; i < mgr->nMgrs(); i++)
  {
   AbstractLightManager* lMgr = (AbstractLightManager*)mgr->getMgr(i);
   connect(lMgr, SIGNAL(newLightCreated(AbstractLightManager*,Light*)), this, SLOT(on_newLightCreated(AbstractLightManager*,Light*)));

   fillTable(lMgr);
  }
 }
 else
 {
  // Internal only
  AbstractLightManager* lMgr = (AbstractLightManager*)mgr->getMgr(mgr->nMgrs()-1);
  connect(lMgr, SIGNAL(newLightCreated(AbstractLightManager*,Light*)), this, SLOT(on_newLightCreated(AbstractLightManager*, Light*)));
  fillTable(lMgr);
 }
 ui->tableWidget->resizeColumnsToContents();
 connect(ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(on_tableWidget_cellChanged(int,int)));
 connect(stateMapper, SIGNAL(mapped(int)), this, SLOT(on_stateMapper_signaled(int)));
 connect(deleteMapper, SIGNAL(mapped(int)), this, SLOT(on_deleteMapper_signaled(int)));
 connect(enabledMapper, SIGNAL(mapped(int)), this, SLOT(on_enabledMapper_signaled(int)));
 connect(editMapper, SIGNAL(mapped(int)), this, SLOT(on_editMapper_signaled(int)));
}

LightTableWidget::~LightTableWidget()
{
    delete ui;
}
void LightTableWidget::fillTable(AbstractLightManager * lMgr)
{
 int row = ui->tableWidget->rowCount();
 QStringList list = lMgr->getSystemNameList();
 qSort(list.begin(), list.end(), SystemNameComparator::compare);
 ui->tableWidget->setRowCount(row + list.count());
 ui->tableWidget->setAlternatingRowColors(true);
 ui->tableWidget->resizeColumnsToContents();
 ui->tableWidget->setColumnCount(8);

 foreach (QString sysName, list)
 {
  AbstractLight* s = (AbstractLight*)lMgr->getBySystemName(sysName);
  newRow(row, s);
  rows.append(s);
//  PropertyChangeListener* l = new PropertyChangeListener();
//  s->addPropertyChangeListener(l);
  connect(s->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  row++;
 }
}
void LightTableWidget::newRow(int row, AbstractLight* l)
{
 QTableWidgetItem* sn = new QTableWidgetItem(l->getSystemName());
 ui->tableWidget->setItem(row, 0,sn);
 QTableWidgetItem* un = new QTableWidgetItem(l->getUserName());
 ui->tableWidget->setItem(row, 1, un);
 QPushButton* btn = new QPushButton();
 stateMapper->setMapping(btn,row);
 connect(btn, SIGNAL(clicked()), stateMapper, SLOT(map()));
 btn->setText(getValue(l));
 ui->tableWidget->setCellWidget(row,2,btn);
 QTableWidgetItem* cmt = new QTableWidgetItem(l->getComment());
 ui->tableWidget->setItem(row, 3, cmt);
 QPushButton* btnDelete = new QPushButton();
 deleteMapper->setMapping(btnDelete, row);
 btnDelete->setText(tr("Delete"));
 connect(btnDelete, SIGNAL(clicked()), deleteMapper, SLOT(map()));
 ui->tableWidget->setCellWidget(row,4,btnDelete);
 QCheckBox* chkEnabled = new QCheckBox();
 chkEnabled->setChecked(l->getEnabled());
 enabledMapper->setMapping(chkEnabled, row);
 connect(chkEnabled, SIGNAL(clicked()), enabledMapper, SLOT(map()));
 ui->tableWidget->setCellWidget(row,5,chkEnabled);

 QTableWidgetItem* intensity = new QTableWidgetItem(QString("%1").arg(l->getTargetIntensity()));
 ui->tableWidget->setItem(row, 6,intensity);

 QPushButton* btnEdit = new QPushButton(tr("Edit"));
 editMapper->setMapping(btnEdit, row);
 connect(btnEdit, SIGNAL(clicked()), editMapper, SLOT(map()));
 ui->tableWidget->setCellWidget(row, 7, btnEdit);
}
void LightTableWidget::updateRow(int row, AbstractLight *l)
{
 QTableWidgetItem* sn = ui->tableWidget->item(row,0);
 sn->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
 sn->setText(l->getSystemName());
 QTableWidgetItem* un = ui->tableWidget->item(row,1);
 un->setText(l->getUserName());
 un->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
 QPushButton* btn = (QPushButton*)ui->tableWidget->cellWidget(row,2);
 btn->setText(l->getState()==Light::ON?tr("On"):tr("Off"));
 QTableWidgetItem* cmt = ui->tableWidget->item(row,3);
 cmt->setText(l->getComment());
 QCheckBox* chkEnabled = (QCheckBox*)ui->tableWidget->cellWidget(row, 5);
 chkEnabled->setChecked(l->getEnabled());
 QTableWidgetItem* intensity = ui->tableWidget->item(row, 6);
 intensity->setText(QString("%1").arg(l->getTargetIntensity()));
}

void LightTableWidget::propertyChange(PropertyChangeEvent *e)
{
 //qDebug()<< "property change received" + e->toString();
 AbstractLight* lTarget = qobject_cast<AbstractLight*>(e->source);
 for(int row =0; row < rows.count(); row++)
 {
  AbstractLight* l = rows.at(row);
  if(l == lTarget)
  {
   updateRow(row, lTarget);
   break;
  }
 }
}

void LightTableWidget::on_tableWidget_cellChanged(int row, int col)
{
 if(row >= rows.count()) return; // value not yet added
 AbstractLight* l = rows.at(row);
 switch(col)
 {
 case 3: // comment
     l->setComment(ui->tableWidget->item(row,col)->text());
  break;
 case 6:
  l->setTargetIntensity(ui->tableWidget->item(row,col)->text().toInt());
  break;
 default:
  break;
 }
}
void LightTableWidget::on_deleteMapper_signaled(int row)
{
 AbstractLight* l = rows.at(row);
 mgr->deregister(l);
}
void LightTableWidget::on_enabledMapper_signaled(int row)
{
 AbstractLight* l = rows.at(row);
 QCheckBox* chk = (QCheckBox*)ui->tableWidget->cellWidget(row,5);
 l->setEnabled(chk->isChecked());
}
void LightTableWidget::on_stateMapper_signaled(int row)
{
 AbstractLight* l = rows.at(row);
 QPushButton* btn = (QPushButton*)ui->tableWidget->cellWidget(row,2);
 btn->setText(getValue(l));
}
void LightTableWidget::on_editMapper_signaled(int row)
{
 AbstractLight* l = rows.at(row);
 AddEditLightDialog* dlg = new AddEditLightDialog(l, this);
 //dlg->exec();
  dlg->show();
}
void LightTableWidget::on_newLightCreated(AbstractLightManager *lMgr, Light *l)
{
 for(int i=0; i < mgr->nMgrs(); i++)
 {
  if(!bInternal || (bInternal && (i == mgr->nMgrs()-1)))
  {
   AbstractLightManager* currMgr = (AbstractLightManager*)mgr->getMgr(i);
   if(currMgr == lMgr)
   {
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(row+1);
    newRow(row, (AbstractLight*)l);
    rows.append((AbstractLight*)l);
   }
  }
 }
}
/*public*/ QString LightTableWidget::getValue(AbstractLight* l) {
    int val = l->getState();
    switch (val) {
    case Light::ON: return tr("On");
    case Light::INTERMEDIATE: return tr("Intermediate");
    case Light::OFF: return tr("Off");
    case Light::TRANSITIONINGTOFULLON: return tr("Transitioning To Full On");
    case Light::TRANSITIONINGHIGHER: return tr("Transitioning Higher");
    case Light::TRANSITIONINGLOWER: return tr("Transitioning Lower");
    case Light::TRANSITIONINGTOFULLOFF: return tr("Transitioning To Full Off");
    default: return "Unexpected value: "+QString::number(val);
    }
}
