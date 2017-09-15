#include "signalheadwidget.h"
#include "ui_signalheadwidget.h"
#include "instancemanager.h"
#include "../Signal/abstractsignalheadmanager.h"
#include "../Signal/abstractsignalhead.h"
#include <QCheckBox>
#include <QPushButton>
#include "signalheadtableaction.h"
#include "virtualsignalhead.h"
#include "singleturnoutsignalhead.h"
#include "doubleturnoutsignalhead.h"
#include "../LayoutEditor/beantabledatamodel.h"
#include "../LayoutEditor/systemnamecomparator.h"

SignalHeadWidget::SignalHeadWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignalHeadWidget)
{
 ui->setupUi(this);
 log = new Logger("SignalHeadWidget");
 mgr = (AbstractSignalHeadManager*)InstanceManager::signalHeadManagerInstance();
 ui->tableWidget->clearContents();
 ui->tableWidget->resizeColumnsToContents();
 ui->tableWidget->verticalHeader()->setHidden(true);
 rows.clear();
 stateMapper = new QSignalMapper(this);
 deleteMapper = new QSignalMapper(this);
 litMapper = new QSignalMapper(this);
 heldMapper = new QSignalMapper(this);
 editMapper = new QSignalMapper(this);
 //connect(mgr, SIGNAL(newSignalHeadCreated(AbstractSignalHead*)), this, SLOT(on_newSignalHeadCreated(AbstractSignalHead*)));
 connect(mgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 fillTable();
 signalHeadTableAction = new SignalHeadTableAction(tr("SignalTable"), this);
 ui->tableWidget->resizeColumnsToContents();

}

SignalHeadWidget::~SignalHeadWidget()
{
    delete ui;
}

void SignalHeadWidget::fillTable()
{
 int row = ui->tableWidget->rowCount();
 QStringList list = mgr->getSystemNameList();
 qSort(list.begin(), list.end(), SystemNameComparator::compare);

 ui->tableWidget->setRowCount(row + list.count());
 ui->tableWidget->setAlternatingRowColors(true);
 ui->tableWidget->resizeColumnsToContents();
 ui->tableWidget->setColumnCount(8);

 foreach (QString sysName, list)
 {
  AbstractSignalHead* s = (AbstractSignalHead*)mgr->getBySystemName(sysName);
  updateRows(row, s);
  rows.append(s);
//  PropertyChangeListener* l = new PropertyChangeListener();
//  s->addPropertyChangeListener(l);
  connect(s->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  row++;
 }
 connect(ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(on_tableWidget_cellChanged(int,int)));
 connect(stateMapper, SIGNAL(mapped(int)), this, SLOT(on_stateMapper_signaled(int)));
 connect(deleteMapper, SIGNAL(mapped(int)), this, SLOT(on_deleteMapper_signaled(int)));
 connect(litMapper, SIGNAL(mapped(int)), this, SLOT(on_litMapper_signaled(int)));
 connect(heldMapper, SIGNAL(mapped(int)), this, SLOT(on_heldMapper_signaled(int)));
 connect(editMapper, SIGNAL(mapped(int)), this, SLOT(on_editMapper_signaled(int)));
}
void SignalHeadWidget::updateRows(int row, AbstractSignalHead* l)
{
 QTableWidgetItem* sn = new QTableWidgetItem(l->getSystemName());
 sn->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
 ui->tableWidget->setItem(row, 0,sn);
 QTableWidgetItem* un = new QTableWidgetItem(l->getUserName());
 ui->tableWidget->setItem(row, 1, un);
 QPushButton* btn = new QPushButton();
 stateMapper->setMapping(btn,row);
 connect(btn, SIGNAL(clicked()), stateMapper, SLOT(map()));
 stateMapper->setMapping(btn, l);
 btn->setText(l->getAppearanceName(l->getAppearance()));
 ui->tableWidget->setCellWidget(row,2,btn);
 QTableWidgetItem* cmt = new QTableWidgetItem(l->getComment());
 ui->tableWidget->setItem(row, 3, cmt);
 QPushButton* btnDelete = new QPushButton();
 deleteMapper->setMapping(btnDelete, row);
 btnDelete->setText(tr("Delete"));
 connect(btnDelete, SIGNAL(clicked()), deleteMapper, SLOT(map()));
 ui->tableWidget->setCellWidget(row,4,btnDelete);

 QCheckBox* chkLit = new QCheckBox();
 chkLit->setChecked(l->getLit());
 litMapper->setMapping(chkLit, row);
 connect(chkLit, SIGNAL(toggled(bool)), litMapper, SLOT(map()));
 ui->tableWidget->setCellWidget(row,5,chkLit);

 QCheckBox* chkHeld = new QCheckBox(tr(""));
 heldMapper->setMapping(chkHeld, row);
 connect(chkHeld, SIGNAL(clicked()), heldMapper, SLOT(map()));
 ui->tableWidget->setCellWidget(row, 6, chkHeld);

 QPushButton* btnEdit = new QPushButton(tr("Edit"));
 editMapper->setMapping(btnEdit, row);
 connect(btnEdit, SIGNAL(clicked()), editMapper, SLOT(map()));
 ui->tableWidget->setCellWidget(row,7,btnEdit);
}
void SignalHeadWidget::propertyChange(PropertyChangeEvent *e)
{
 qDebug()<< "property change received" + e->toString();
 if(e->getPropertyName() == "Appearance")
 {
  AbstractSignalHead* lTarget = qobject_cast<AbstractSignalHead*>(e->source);
  for(int row =0; row<rows.count(); row++)
  {
   AbstractSignalHead* l = rows.at(row);
   if(l == lTarget)
  {
    updateRows(row, lTarget);
    break;
   }
  }
 }
 else
 if(e->getPropertyName() == "length")
 {
  ui->tableWidget->clear();
  ui->tableWidget->setRowCount(0);
  fillTable();
 }
 else
 {
  qDebug()<< "property change received" + e->toString();
 }
}

void SignalHeadWidget::on_tableWidget_cellChanged(int row, int col)
{
 if(row >= rows.count()) return; // value not yet added
 AbstractSignalHead* l = rows.at(row);
 switch(col)
 {
 case BeanTableDataModel::USERNAMECOL:
  l->setUserName(ui->tableWidget->item(row,col)->text());
  break;
 case BeanTableDataModel::COMMENTCOL: // comment
     l->setComment(ui->tableWidget->item(row,col)->text());
  break;
 default:
  break;
 }
}
void SignalHeadWidget::on_deleteMapper_signaled(int row)
{
 AbstractSignalHead* l = rows.at(row);
 mgr->deregister(l);
 rows.remove(row);
 ui->tableWidget->removeRow(row);
}
void SignalHeadWidget::on_litMapper_signaled(int row)
{
 AbstractSignalHead* l = rows.at(row);
 QCheckBox* chk = (QCheckBox*)ui->tableWidget->cellWidget(row,5);
 //l->set(chk->isChecked());

}
void SignalHeadWidget::on_stateMapper_signaled(int row)
{
 AbstractSignalHead* t = rows.at(row);
 QPushButton* btn = (QPushButton*)ui->tableWidget->cellWidget(row,2);
 int oldState = t->getAppearance();
 int newState = 99;
 QVector<int> stateList = t->getValidStates();
 for (int i = 0; i < stateList.count(); i++)
 {
  if (oldState == stateList.at(i) )
  {
   if (i < stateList.count()-1)
   {
    newState = stateList.at(i+1);
    break;
   }
   else
   {
    newState = stateList.at(0);
    break;
   }
  }
 }
 if (newState==99)
 {
  if (stateList.count()==0)
  {
   newState=SignalHead::DARK;
   log->warn("New signal state not found so setting to Dark " + t->getDisplayName());
  }
  else
  {
   newState=stateList[0];
   log->warn("New signal state not found so setting to the first available " + t->getDisplayName());
  }
 }
 log->debug("was "+QString::number(oldState)+" becomes "+QString::number(newState));
 if(qobject_cast<VirtualSignalHead*>(t)!=NULL)
  ((VirtualSignalHead*)t)->setAppearance(newState);
 else if(qobject_cast<DoubleTurnoutSignalHead*>(t)!=NULL)
   ((DoubleTurnoutSignalHead*)t)->setAppearance(newState);
 else  if(qobject_cast<SingleTurnoutSignalHead*>(t)!=NULL)
   ((SingleTurnoutSignalHead*)t)->setAppearance(newState);
 else
  (t)->setAppearance(newState);
 btn->setText(t->getAppearanceName(newState));
}
void SignalHeadWidget::on_heldMapper_signaled(int row)
{
 AbstractSignalHead* l = rows.at(row);
 QCheckBox* chk = (QCheckBox*)ui->tableWidget->cellWidget(row,6);
}
void SignalHeadWidget:: on_newSignalHeadCreated(AbstractSignalHead *s)
{
 int row = ui->tableWidget->rowCount();
 ui->tableWidget->setRowCount(row +1);
 updateRows(row,s);
 rows.append(s);
}
void SignalHeadWidget::on_editMapper_signaled(int row)
{
    AbstractSignalHead* l = rows.at(row);
    signalHeadTableAction->editSignal((SignalHead*)l);

}
void SignalHeadWidget::on_btnAdd_clicked()
{
signalHeadTableAction->addPressed(NULL);
}
