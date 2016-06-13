#include "idtagswidget.h"
#include "ui_idtagswidget.h"
#include "instancemanager.h"
#include "addeditdialog.h"
#include "tablesframe.h"

IdTagsWidget::IdTagsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IdTagsWidget)
{
 ui->setupUi(this);
 ui->tableWidget->clearContents();
 ui->tableWidget->verticalHeader()->setHidden(true);
 rows.clear();
 deleteMapper = new QSignalMapper(this);
 clearMapper = new QSignalMapper(this);

 this->parent = (TablesFrame*)parent;
 mgr = (DefaultIdTagManager*)InstanceManager::getDefault("DefaultIdTagManager");
 if(!mgr->isInitialised())
  mgr->init();
 int row = ui->tableWidget->rowCount();
 ui->tableWidget->setAlternatingRowColors(true);
 QStringList list = mgr->getSystemNameList();
 ui->tableWidget->setRowCount(row + list.count());
 ui->tableWidget->setColumnCount(9);
 ui->chkSaveWhen->setChecked(mgr->isStateStored());
 ui->chkFastClock->setChecked(mgr->isFastClockUsed());

 foreach (QString sysName, list)
 {
  DefaultIdTag* t = (DefaultIdTag*)mgr->getBySystemName(sysName);
//  connect(t, SIGNAL(propertyChange(DefaultIdTag*, QString,QObject*,QObject*)), this, SLOT(on_propertyChange(DefaultIdTag*,QString,QObject*,QObject*)));
//  connect(t, SIGNAL(propertyChange(AbstractNamedBean*,QString,QString,QString)), this, SLOT(on_propertyChange(AbstractNamedBean*,QString,QString,QString)));
  connect(t->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  updateRow(row, t);
  rows.append(t);
  row++;
 }
#if QT_VERSION >= 0x04FF00
 ui->tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);
 ui->tableWidget->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Fixed);
#else
 ui->tableWidget->horizontalHeader()->setResizeMode(4, QHeaderView::Fixed);
 ui->tableWidget->horizontalHeader()->setResizeMode(7, QHeaderView::Fixed);
#endif
 connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(on_btnAdd_clicked()));
 connect(ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(on_tableWidget_cellChanged(int,int)));
 connect(mgr, SIGNAL(newIdTagCreated(IdTag*)), this, SLOT(on_newIdTagCreated(IdTag*)));
 connect(deleteMapper, SIGNAL(mapped(QObject*)), this, SLOT(on_deleteMapper_clicked(QObject*)));
 connect(clearMapper, SIGNAL(mapped(QObject*)), this, SLOT(on_clearMapper_clicked(QObject*)));
}
void IdTagsWidget::updateRow(int row, AbstractIdTag* t)
{
 QTableWidgetItem* sn = new QTableWidgetItem(t->getSystemName());
 sn->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
 ui->tableWidget->setItem(row, 0,sn);
 QTableWidgetItem* un = new QTableWidgetItem(t->getUserName());
 ui->tableWidget->setItem(row, 1, un);
 QTableWidgetItem* tagId = new QTableWidgetItem(t->getTagID());
 ui->tableWidget->setItem(row, 2, tagId);
 QTableWidgetItem* comment = new QTableWidgetItem(t->getComment());
 ui->tableWidget->setItem(row,3,comment);
 QPushButton* btnDelete = new QPushButton(tr("Delete"));
 connect(btnDelete, SIGNAL(clicked()), deleteMapper, SLOT(map()));
 deleteMapper->setMapping(btnDelete, t);
 ui->tableWidget->setCellWidget(row,4,btnDelete);
 if(t->getWhereLastSeen() != NULL)
 {
  QTableWidgetItem* whereSeen = new QTableWidgetItem(t->getWhereLastSeen()->getSystemName());
  ui->tableWidget->setItem(row, 5, whereSeen);
 }

 if(t->getWhenLastSeen().isValid())
 {
  QTableWidgetItem* whenSeen = new QTableWidgetItem(t->getWhenLastSeen().toString(tr("yyyy/MM/dd hh:mm:ss")));
  ui->tableWidget->setItem(row, 6, whenSeen);
 }
 QPushButton* btnClear = new QPushButton(tr("Clear"));
 ui->tableWidget->setCellWidget(row,7,btnClear);
 connect(btnClear, SIGNAL(clicked()), clearMapper, SLOT(map()));
 clearMapper->setMapping(btnClear,t);
 QTableWidgetItem* rosterId = new QTableWidgetItem(QString("%1").arg(((DefaultIdTag*)t)->rosterId()));
 ui->tableWidget->setItem(row,8,rosterId);
}

IdTagsWidget::~IdTagsWidget()
{
    delete ui;
}
void IdTagsWidget::on_btnAdd_clicked()
{
 AddEditDialog* dlg = new AddEditDialog(parent->curType, this);
 if(dlg->exec() == QDialog::Accepted)
 {
  QString systemName = dlg->systemName();
  QString userName = dlg->userName();
  AbstractIdTag* t = (AbstractIdTag*)mgr->getBySystemName(systemName);
  if(t == NULL)
  {
   int row = rows.count();
   ui->tableWidget->setRowCount(row + 1);
   updateRow(row, (AbstractIdTag*)t);
   ui->tableWidget->setRowHidden(row,false);
   rows.append((AbstractIdTag*)t);
  }
  else
  {
   t->setUserName(userName);
  }
 }
}
void IdTagsWidget::propertyChange(PropertyChangeEvent* e)
{
 on_propertyChange((DefaultIdTag*)e->getSource(), e->getPropertyName(), NULL, NULL);
}

void IdTagsWidget::on_propertyChange(DefaultIdTag* tag,QString pName, QObject* /*o*/, QObject* /*n*/)
{
 //qDebug()<< tr("Property change: %1 %2 %3").arg(pName).arg(o!=NULL?o->metaObject()->className():"NULL").arg(n->metaObject()->className());
 if(rows.contains(tag))
 {
  int row = rows.indexOf(tag);
  if(pName == "whereLastSeen")
  {
   QTableWidgetItem* whereSeen;
   Reporter* reporter = tag->getWhereLastSeen();
   if(reporter == NULL)
    whereSeen = new QTableWidgetItem();
   else
    whereSeen = new QTableWidgetItem(tag->getWhereLastSeen()->getSystemName());
   ui->tableWidget->setItem(row, 5, whereSeen);
  }
  if(pName == "whenLastSeen")
  {
   QTableWidgetItem* whenSeen = new QTableWidgetItem(tag->getWhenLastSeen().toString(tr("yyyy/MM/dd hh:mm:ss")));
   ui->tableWidget->setItem(row, 6, whenSeen);
  }
  if(pName == "rosterId")
  {
   QTableWidgetItem* rosterId = new QTableWidgetItem(QString("%1").arg(tag->rosterId()));
   ui->tableWidget->setItem(row, 8, rosterId);
  }
 }
}
void IdTagsWidget::on_propertyChange(AbstractNamedBean *bean, QString /*pName*/, QString /*o*/, QString /*n*/)
{
 AbstractIdTag* t = (AbstractIdTag*)bean;
 if(rows.contains(t))
 {
  int row = rows.indexOf(t);
  QTableWidgetItem* sn = new QTableWidgetItem(t->getSystemName());
  ui->tableWidget->setItem(row, 0,sn);
  QTableWidgetItem* un = new QTableWidgetItem(t->getUserName());
  ui->tableWidget->setItem(row, 1, un);
  QTableWidgetItem* tagId = new QTableWidgetItem(t->getTagID());
  ui->tableWidget->setItem(row, 2, tagId);
  QTableWidgetItem* comment = new QTableWidgetItem(t->getComment());
  ui->tableWidget->setItem(row,3,comment);
  QTableWidgetItem* rosterId = new QTableWidgetItem(QString("%1").arg(((DefaultIdTag*)t)->rosterId()));
  ui->tableWidget->setItem(row,8,rosterId);
 }
}
void IdTagsWidget::on_newIdTagCreated(IdTag *tag)
{
 DefaultIdTag* t = (DefaultIdTag*)tag;
 int row = ui->tableWidget->rowCount();
 ui->tableWidget->setRowCount(row + 1);
 updateRow(row, (AbstractIdTag*)t);
 ui->tableWidget->setRowHidden(row,false);
 rows.append((AbstractIdTag*)t);
}

void IdTagsWidget::on_tableWidget_cellChanged(int row, int col)
{
 if(rows.isEmpty()) return;
 if(row == rows.count()) return;
 AbstractIdTag* t = rows.at(row);
 switch(col)
 {
 case 1: // user name
  t->setUserName(ui->tableWidget->item(row,col)->text());
  break;
 case 3:
  t->setComment(ui->tableWidget->item(row,col)->text());
  break;
 case 8:
  ((DefaultIdTag*)t)->setRosterId(ui->tableWidget->item(row, col)->text().toInt());
  break;
 }
}
void IdTagsWidget::on_deleteMapper_clicked(QObject *o)
{
 AbstractIdTag* t = (AbstractIdTag*)o;
 int row = rows.indexOf(t);
 if(row >= 0)
 {
  rows.remove(row);
  ui->tableWidget->removeRow(row);
  mgr->deregister(t);
 }
}
void IdTagsWidget::on_clearMapper_clicked(QObject *o)
{
 DefaultIdTag* t = (DefaultIdTag*)o;
 int row = rows.indexOf(t);
 if(row >= 0)
 {
  t->setWhereLastSeen(NULL);
  t->setState(IdTag::UNSEEN);
 }
}
void IdTagsWidget::on_chkSaveWhen_toggled(bool bState)
{
 mgr->setStateStored(bState);
}
void IdTagsWidget::on_chkFastClock_toggled(bool bState)
{
 mgr->setFastClockUsed(bState);
}
