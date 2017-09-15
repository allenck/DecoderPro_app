#include "routewidget.h"
#include "ui_routewidget.h"
#include "instancemanager.h"
//#include "addeditroute.h"
#include "routetableaction.h"
#include "jtextfield.h"
#include <QMessageBox>
#include "../LayoutEditor/systemnamecomparator.h"


RouteWidget::RouteWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RouteWidget)
{
 ui->setupUi(this);
 ui->tableWidget->clearContents();
 ui->tableWidget->verticalHeader()->setHidden(true);
 log = new Logger("RouteWidget");
 rows.clear();
 deleteMapper = new QSignalMapper(this);
 editMapper = new QSignalMapper(this);
 setMapper = new QSignalMapper(this);
 mgr = (DefaultRouteManager*)InstanceManager::routeManagerInstance();
 connect(mgr, SIGNAL(newRouteCreated(Route*)), this, SLOT(on_newRouteCreated(Route*)));
 int row = ui->tableWidget->rowCount();
 QStringList list = mgr->getSystemNameList();
 qSort(list.begin(), list.end(), SystemNameComparator::compare);
 ui->tableWidget->setRowCount(row + list.count());
 ui->tableWidget->setColumnCount(8);
 ui->tableWidget->setAlternatingRowColors(true);
 ui->tableWidget->resizeColumnsToContents();
 act = new RouteTableAction(this);
 bLoading = true;
 foreach (QString sysName, list)
 {
  DefaultRoute* b = (DefaultRoute*)mgr->getBySystemName(sysName);
  rows.append(b);
  updateRow(row, b);
//  PropertyChangeListener* listener;
//  b->addPropertyChangeListener(listener = new PropertyChangeListener());
  connect(b, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  row++;
 }
 bLoading = false;
 ui->tableWidget->resizeColumnsToContents();
 connect(ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(on_tableWidget_cellChanged(int,int)));
 connect(setMapper, SIGNAL(mapped(int)), this, SLOT(on_setMapper_clicked(int)));
 connect(deleteMapper, SIGNAL(mapped(int)), this, SLOT(on_deleteMapper_clicked(int)));
 connect(editMapper, SIGNAL(mapped(int)), this, SLOT(on_editMapper_clicked(int)));
 connect(mgr, SIGNAL(beanDeleted(NamedBean*)), this, SLOT(on_beanDeleted(NamedBean*)));
}

RouteWidget::~RouteWidget()
{
    delete ui;
}
void RouteWidget::updateRow(int row, DefaultRoute* r)
{
  QTableWidgetItem* sn = new QTableWidgetItem(r->getSystemName());
  sn->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
  ui->tableWidget->setItem(row, 0, sn);
  QTableWidgetItem* un = new QTableWidgetItem(r->getUserName());
  un->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);
  ui->tableWidget->setItem(row, 1, un);
  QPushButton* btn = new QPushButton(tr("Set"));
  setMapper->setMapping(btn,row);
  btn->setToolTip("Sets all Route Turnouts to the state shown in the Route definition");
  connect(btn, SIGNAL(clicked()), setMapper, SLOT(map()));
  ui->tableWidget->setCellWidget(row, 2, btn);
  QTableWidgetItem* comment = new QTableWidgetItem(r->getComment());
  comment->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);
  ui->tableWidget->setItem(row, 3, comment);
  QPushButton* btnDelete = new QPushButton();
  deleteMapper->setMapping(btnDelete,row);
  connect(btnDelete, SIGNAL(clicked()), deleteMapper, SLOT(map()));
  btnDelete->setText(tr("Delete"));
  ui->tableWidget->setCellWidget(row,4,btnDelete);
  QTableWidgetItem* enabled = new QTableWidgetItem();
  enabled->setFlags(Qt::ItemIsUserCheckable| Qt::ItemIsEnabled);
  enabled->setCheckState(r->getEnabled()?Qt::Checked:Qt::Unchecked);
  ui->tableWidget->setItem(row,5,enabled);
  QTableWidgetItem* locked = new QTableWidgetItem();
  if(r->canLock())
   locked->setFlags(Qt::ItemIsUserCheckable| Qt::ItemIsEnabled);
  else
  {
   locked->setFlags(Qt::NoItemFlags);
   locked->setText(tr("n/a"));
  }
  locked->setCheckState(r->getLocked()?Qt::Checked:Qt::Unchecked);
  ui->tableWidget->setItem(row,6,locked);
  QPushButton* btnEdit = new QPushButton();
  btnEdit->setText(tr("Edit"));
  editMapper->setMapping(btnEdit, row);
  connect(btnEdit, SIGNAL(clicked()), editMapper, SLOT(map()));
  ui->tableWidget->setCellWidget(row,7,btnEdit);
}
void RouteWidget::on_btnAdd_clicked()
{
// AddEditRoute* dlg = new AddEditRoute(NULL, this);
// dlg->exec();
  act->_systemName->setText("");
  act->addPressed();
}
void RouteWidget::propertyChange(PropertyChangeEvent *e)
{
 qDebug()<< "property change received" + e->toString();
 DefaultRoute* rTarget = qobject_cast<DefaultRoute*>(e->source);
 for(int row =0; row<rows.count(); row++)
 {
  DefaultRoute* r = rows.at(row);
  if(r == rTarget)
  {
   bLoading = true;
   updateRow(row, r);
   bLoading = false;
   break;
  }
 }
}
void RouteWidget::on_newRouteCreated( Route *o)
{
 DefaultRoute* r = (DefaultRoute*)o;
 int row = rows.count();
 ui->tableWidget->setRowCount(row + 1);
 updateRow(row, (DefaultRoute*)r);
 ui->tableWidget->setRowHidden(row,false);
 rows.append((DefaultRoute*)r);
}
void RouteWidget::on_tableWidget_cellChanged(int row, int col)
{
 if(rows.isEmpty()) return;
 if(row == rows.count()) return;
 if(bLoading) return;
 DefaultRoute* r = rows.at(row);
 switch(col)
 {
  case 1: // user name
   {
    //Directly changing the username should only be possible if the username was previously null or ""
    // check to see if user name already exists
    QString value = ui->tableWidget->item(row,col)->text();
    if ((value)==(""))
    {
     r->setUserName(value);
     return;
    }
    else
    {
     NamedBean* nB = mgr->getByUserName(value);
     if (nB != NULL)
     {
      log->error("User name is not unique " + value);
      QString msg;
      msg = tr("User Name \" %1 \" has already been used.").arg(value);
      QMessageBox::warning(this, tr("Warning"), msg);
      ui->tableWidget->item(row,col)->setText(r->getUserName()); // restore original value
      return;
     }
    }
    NamedBean* nBean = mgr->getBySystemName(ui->tableWidget->item(row,0)->text());
    nBean->setUserName( value);
    //fireTableRowsUpdated(row, row);
    break;
   }
  case 3:
   r->setComment(ui->tableWidget->item(row,col)->text());
   break;
 case 5: // enabled
 {
     Qt::CheckState enabled = ui->tableWidget->item(row, col)->checkState();
     r->setEnabled(enabled == Qt::Checked);
     break;
 }
 case 6:
     Qt::CheckState locked = ui->tableWidget->item(row, col)->checkState();
     r->setLocked(locked == Qt::Checked);
     break;
 }
}
void RouteWidget::on_setMapper_clicked(int row)
{
 DefaultRoute* r = rows.at(row);
 r->setRoute();
}
void RouteWidget::on_deleteMapper_clicked(int row)
{
 DefaultRoute* r = rows.at(row);
 rows.remove(row);
 ui->tableWidget->removeRow(row);
 mgr->deregister(r);
}
void RouteWidget::on_editMapper_clicked(int row)
{
 //DefaultRoute* r = (DefaultRoute*)o;
 DefaultRoute* r = rows.at(row);
 act->addPressed();
 act->_systemName->setText(r->getSystemName());
 act->editPressed();
}
void RouteWidget::on_beanDeleted(NamedBean *bean)
{
 if(rows.contains((DefaultRoute*)bean))
 {
  rows.remove(rows.indexOf((DefaultRoute*)bean));
  ui->tableWidget->setRowCount(rows.count());
 }
}
