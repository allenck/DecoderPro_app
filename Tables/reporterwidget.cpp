#include "reporterwidget.h"
#include "ui_reporterwidget.h"
#include "instancemanager.h"
#include "abstractreporter.h"
#include "defaultidtag.h"
#include "lnreporter.h"
#include "addeditdialog.h"
#include "../LayoutEditor/systemnamecomparator.h"
#include "rosterentry.h"

ReporterWidget::ReporterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReporterWidget)
{
  ui->setupUi(this);
  ui->tableWidget->clearContents();
  ui->tableWidget->verticalHeader()->setHidden(true);
  rows.clear();
  deleteMapper = new QSignalMapper(this);

  mgr = (ProxyReporterManager*)InstanceManager::reporterManagerInstance();
  int row = ui->tableWidget->rowCount();
  ui->tableWidget->setAlternatingRowColors(true);
  ui->tableWidget->resizeColumnsToContents();
  QList<Manager*> mgrList = mgr->getManagerList();
  for(int i=0; i < mgrList.count(); i++)
  {
   AbstractReporterManager* rMgr = (AbstractReporterManager*)mgrList.at(i);
   connect(rMgr, SIGNAL(newReporterCreated(AbstractReporterManager*,AbstractReporter*)), this, SLOT(on_newReporterCreated(AbstractReporterManager*,AbstractReporter*)));
   QStringList list = rMgr->getSystemNameList();
   qSort(list.begin(), list.end(), SystemNameComparator::compare);
   ui->tableWidget->setRowCount(row + list.count());

   foreach (QString sysName, list)
   {
    Reporter* r = (Reporter*)rMgr->getBySystemName(sysName);
    updateRow(row, r);
    rows.append(r);
    connect(r, SIGNAL(propertyChange(AbstractReporter*,QString,QObject*,QObject*)), this, SLOT(on_propertyChange(AbstractReporter*,QString,QObject*,QObject*)));
    connect(r, SIGNAL(propertyChange(AbstractNamedBean*,QString,QString,QString)), this, SLOT(on_propertyChange(AbstractNamedBean*,QString,QString)));
    row++;
   }
   ui->tableWidget->resizeColumnsToContents();
#if QT_VERSION >= 0x04FF00
   ui->tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);
#else
   ui->tableWidget->horizontalHeader()->setResizeMode(4, QHeaderView::Fixed);
#endif
   connect(deleteMapper, SIGNAL(mapped(int)), this, SLOT(on_deleteMapper_signaled(int)));
  }
}
void ReporterWidget::updateRow(int row, Reporter* r)
{
 QTableWidgetItem* sn = new QTableWidgetItem(r->getSystemName());
 sn->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
 ui->tableWidget->setItem(row, 0,sn);
 QTableWidgetItem* un = new QTableWidgetItem(r->getUserName());
 ui->tableWidget->setItem(row, 1, un);
 QVariant currRpt = r->getCurrentReport();
 if(currRpt != QVariant())
 {
  IdTag* id = VPtr<IdTag>::asPtr(currRpt);
  QString rptText = currRpt.toString();
  if(id!= NULL)
    rptText = ((DefaultIdTag*)id)->getTagID();
  QTableWidgetItem* report = new QTableWidgetItem(rptText);
  ui->tableWidget->setItem(row,2, report);
 }
 QTableWidgetItem* comment = new QTableWidgetItem(r->getComment());
 ui->tableWidget->setItem(row,3, comment);
 QPushButton* btn = new QPushButton();
 btn->setText(tr("Delete"));
 deleteMapper->setMapping(btn,row);
 connect(btn, SIGNAL(clicked()), deleteMapper, SLOT(map()));
 ui->tableWidget->setCellWidget(row,4,btn);
 QVariant lastRpt = r->getLastReport();
 if(lastRpt != QVariant())
 {
  IdTag* id = VPtr<IdTag>::asPtr(lastRpt);
  QString rptText = lastRpt.toString();
  if(id != NULL)
   rptText = ((DefaultIdTag*)id)->getTagID();
  QTableWidgetItem* lastReport = new QTableWidgetItem(rptText);
  ui->tableWidget->setItem(row,3, lastReport);
 }
 row++;
}

ReporterWidget::~ReporterWidget()
{
    delete ui;
}
void ReporterWidget::on_propertyChange(Reporter *r, QString pName, QVariant /*o*/, QVariant /*n*/)
{
 if(rows.contains(r))
 {
  int row = rows.indexOf(r);
  if(pName == "lastReport")
  {
   QVariant lastRpt = r->getLastReport();
   QVariant currRpt = r->getCurrentReport();
   if(lastRpt != QVariant())
   {
    IdTag* id = VPtr<IdTag>::asPtr(lastRpt);
    QString rptText = lastRpt.toString();
    if(id != NULL)
     rptText = ((DefaultIdTag*)id)->getTagID();
    QTableWidgetItem* lastReport = new QTableWidgetItem(rptText);
    ui->tableWidget->setItem(row,3, lastReport);
   }
   if(pName == "currentReport")
   {
    IdTag* id = VPtr<IdTag>::asPtr(currRpt);
    QString rptText = currRpt.toString();
    if(id != NULL)
     rptText = ((DefaultIdTag*)id)->getTagID();
    QTableWidgetItem* report = new QTableWidgetItem(rptText);
    ui->tableWidget->setItem(row,2, report);
   }
  }
 }
}
void ReporterWidget::on_propertyChange(AbstractNamedBean *r, QString /*o*/, QString /*n*/)
{
 if(rows.contains((Reporter*)r))
 {
  int row = rows.indexOf((Reporter*)r);
  QTableWidgetItem* sn = new QTableWidgetItem(r->getSystemName());
  ui->tableWidget->setItem(row, 0,sn);
  QTableWidgetItem* un = new QTableWidgetItem(r->getUserName());
  ui->tableWidget->setItem(row, 1, un);
  QTableWidgetItem* comment = new QTableWidgetItem(r->getComment());
  ui->tableWidget->setItem(row,3, comment);
 }
}

void ReporterWidget::on_newReporterCreated(AbstractReporterManager *rMgr, Reporter *r)
{
 QList<Manager*> mgrList = mgr->getManagerList();
 for(int i=0; i <mgrList.count(); i++)
 {
  AbstractReporterManager* currMgr = (AbstractReporterManager*)mgrList.at(i);
  if(currMgr == rMgr)
  {
   int row = ui->tableWidget->rowCount();
   ui->tableWidget->setRowCount(row + 1);
   updateRow(row, r);
   rows.append(r);
  }
 }
}
void ReporterWidget::on_btnAdd_clicked()
{
 AddEditDialog dlg(tr("Reporters"),this);
 if(dlg.exec() == QDialog::Accepted)
 {
  QString sysName;
  //QString system = dlg.system();
  QString userName = dlg.userName();
  QList<Manager*> mgrList = mgr->getManagerList();
  AbstractReporterManager* rmgr = (AbstractReporterManager*)mgrList.at(dlg.mgrIndex());
  QString sPrefix = rmgr->getSystemPrefix()+ rmgr->typeLetter();
  //if(system != tr("Internal")) iMgr= 0;
  if(dlg.isAddRange())
  {
   int count = dlg.numToAdd();
   int addr = dlg.systemName().toInt();
   for(int iAddr = addr; iAddr < addr + count -1; iAddr++)
   {
    sysName = sPrefix+QString("%1").arg(iAddr);
    mgr->newReporter(sysName, userName+QString("%1").arg(iAddr));
   }
  }
  else
  {
   sysName = sPrefix+dlg.systemName();
   mgr->newReporter(sysName, userName);
  }
 }
}
void ReporterWidget::on_deleteMapper_signaled(int row)
{
 Reporter* r = rows.at(row);
 ui->tableWidget->removeRow(row);
 rows.remove(row);
 mgr->deregister(r);
}
