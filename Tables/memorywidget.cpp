#include "memorywidget.h"
#include "ui_memorywidget.h"
#include "instancemanager.h"
#include "abstractmemory.h"
#include "addeditdialog.h"

MemoryWidget::MemoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MemoryWidget)
{
 ui->setupUi(this);
 ui->tableWidget->clearContents();
 rows.clear();
 deleteMapper = new QSignalMapper(this);
 mgr = (DefaultMemoryManager*)InstanceManager::memoryManagerInstance();
 int row = ui->tableWidget->rowCount();
 QStringList list = mgr->getSystemNameList();
 ui->tableWidget->setRowCount(row + list.count());
 ui->tableWidget->setAlternatingRowColors(true);
 ui->tableWidget->resizeColumnsToContents();
 ui->tableWidget->verticalHeader()->setHidden(true);

 foreach (QString sysName, list)
 {
  AbstractMemory* m = (AbstractMemory*)mgr->getBySystemName(sysName);
  connect(m->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  updateRow(row,  m);
  rows.append(m);

  row++;
 }
 connect(mgr, SIGNAL(newMemoryCreated(Memory*)), this, SLOT(on_newMemoryCreated(Memory*)));
 connect(deleteMapper, SIGNAL(mapped(int)), this, SLOT(on_deleteMapper_signaled(int)));
 connect(ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(on_tableWidget_cellChanged(int,int)));
}

MemoryWidget::~MemoryWidget()
{
    delete ui;
}
void MemoryWidget::updateRow(int row, AbstractMemory* m)
{
 QTableWidgetItem* sn = new QTableWidgetItem(m->getSystemName());
 sn->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
 ui->tableWidget->setItem(row, 0,sn);
 QTableWidgetItem* un = new QTableWidgetItem(m->getUserName());
 ui->tableWidget->setItem(row, 1, un);
 QVariant pValue = m->getValue();
 if(pValue != QVariant())
 {
  QTableWidgetItem* value = new QTableWidgetItem(pValue.toString());
  ui->tableWidget->setItem(row,2, value);
  }
 QTableWidgetItem* comment = new QTableWidgetItem(m->getComment());
 ui->tableWidget->setItem(row,3, comment);
 QPushButton* btn = new QPushButton();
 btn->setText(tr("Delete"));
 ui->tableWidget->setCellWidget(row,4,btn);
 deleteMapper->setMapping(btn, row);
 connect(btn, SIGNAL(clicked()), deleteMapper, SLOT(map()));
}

void MemoryWidget::on_btnAdd_clicked()
{
 AddEditDialog dlg(tr("Memory Variables"),this);
 if(dlg.exec() == QDialog::Accepted)
 {
  QString sysName = dlg.systemName();
  QString userName = dlg.userName();
  QString sPrefix = mgr->getSystemPrefix()+ mgr->typeLetter();
  if(dlg.isAddRange())
  {
   int count = dlg.numToAdd();
   int addr = dlg.systemName().toInt();
   for(int iAddr = addr; iAddr < addr + count -1; iAddr++)
   {
    sysName = sPrefix+QString("%1").arg(iAddr);
    if(dlg.isAutoGen())
     mgr->newMemory(userName+QString("%1").arg(iAddr));
    else
     mgr->newMemory(sysName, userName+QString("%1").arg(iAddr));
   }
  }
  else
  {
   sysName = sPrefix+dlg.systemName();
   if(dlg.isAutoGen())
    mgr->newMemory(userName);
   else
    mgr->newMemory(sysName, userName);
  }
 }
}
void MemoryWidget::on_deleteMapper_signaled(int row)
{
 AbstractMemory* m = rows.at(row);
 ui->tableWidget->removeRow(row);
 rows.remove(row);
 mgr->deregister((NamedBean*)m);
}
void MemoryWidget::on_newMemoryCreated(Memory *m)
{
 int row = ui->tableWidget->rowCount();
 ui->tableWidget->setRowCount(row +1);
 updateRow(row, (AbstractMemory*)m );
 rows.append((AbstractMemory*)m);
}
void MemoryWidget::on_tableWidget_cellChanged(int row, int col)
{
 if(row == rows.count()) return;
 AbstractMemory* m = rows.at(row);
 QString text;
 switch(col)
 {
 case 1: // User Name
  text = ui->tableWidget->item(row, col)->text();
  m->setUserName(text);
  break;
 case 2: // Current Value
  text = ui->tableWidget->item(row, col)->text();
  m->setValue(text);
  break;
 case 3: // comment
  text = ui->tableWidget->item(row, col)->text();
  m->setComment(text);
  break;
 }
}
void MemoryWidget::propertyChange(PropertyChangeEvent *e)
{
 for(int row=0; row < rows.count(); row++)
 {
  if(rows.at(row) == (AbstractMemory*)e->source)
      updateRow(row, (AbstractMemory*)e->source);
 }
 ui->tableWidget->resizeColumnsToContents();
}
