#include "signalmastlogicwidget.h"
#include "ui_signalmastlogicwidget.h"
#include "instancemanager.h"
#include "defaultsignalmastlogicmanager.h"
#include <qcheckbox.h>
#include "abstractsignalmast.h"
#include "signallingframe.h"

SignalMastLogicWidget::SignalMastLogicWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignalMastLogicWidget)
{
 ui->setupUi(this);
 log = new Logger("SignalMastWidget");
 mgr = (DefaultSignalMastLogicManager*)InstanceManager::signalMastLogicManagerInstance();
 ui->tableWidget->clearContents();
 ui->tableWidget->verticalHeader()->setHidden(true);
 rows.clear();
 deleteMapper = new QSignalMapper();
 enabledMapper = new QSignalMapper();
 editMapper = new QSignalMapper();
 fillTable();
 connect(mgr, SIGNAL(on_newSignalMastLogicCreated(SignalMastLogic*)), this, SLOT(on_newSignalMastLogicCreated(SignalMastLogic*)));
 connect(deleteMapper, SIGNAL(mapped(int)), this, SLOT(on_deleteMapper_signaled(int)));
 connect(enabledMapper, SIGNAL(mapped(int)), this, SLOT(on_enabledMapper_signaled(int)));
 connect(editMapper, SIGNAL(mapped(int)), this, SLOT(on_editMapper_signaled(int)));

 ui->tableWidget->resizeColumnsToContents();
}

SignalMastLogicWidget::~SignalMastLogicWidget()
{
    delete ui;
}
void SignalMastLogicWidget::fillTable()
{
 int row = ui->tableWidget->rowCount();
 logicList =mgr->getSignalMastLogicList();
 updateNameList();
 ui->tableWidget->setRowCount(row + logicList.count());
 ui->tableWidget->setAlternatingRowColors(true);
 ui->tableWidget->resizeColumnsToContents();
 ui->tableWidget->setColumnCount(8);

 foreach (SignalMastLogic* sml, logicList)
 {
  rows.append((DefaultSignalMastLogic*)sml);
  updateRows(row, (DefaultSignalMastLogic*)sml);
//  PropertyChangeListener* l = new PropertyChangeListener();
//  sml->addPropertyChangeListener((PropertyChangeListener*)l);
  DefaultSignalMastLogic* dsml = (DefaultSignalMastLogic*)sml;
  connect(dsml, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  row++;
 }
}
void SignalMastLogicWidget::updateRows(int row, DefaultSignalMastLogic* dsml)
{
 QTableWidgetItem* source = new QTableWidgetItem(dsml->getSourceMast()->getDisplayName());
 source->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
 ui->tableWidget->setItem(row, 0, source);
 QTableWidgetItem* sourceAppearance = new QTableWidgetItem(((AbstractSignalMast*)dsml->getSourceMast())->getAspect());
 sourceAppearance->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
 ui->tableWidget->setItem(row, 1, sourceAppearance);
 QTableWidgetItem* destination = new QTableWidgetItem(getDestMastFromRow(row)!= NULL?getDestMastFromRow(row)->getDisplayName():tr("unknown"));
 ui->tableWidget->setItem(row, 2,destination);
 QTableWidgetItem* destAppearance = new QTableWidgetItem(getDestMastFromRow(row)!= NULL?((AbstractSignalMast*)getDestMastFromRow(row))->getAspect():"??");
 ui->tableWidget->setItem(row, 3, destAppearance);

 QTableWidgetItem* comment = new QTableWidgetItem(dsml->getComment(dsml->getSourceMast()));
 ui->tableWidget->setItem(row, 4, comment);

 QPushButton* btnDelete = new QPushButton(tr("Delete"));
 connect(btnDelete, SIGNAL(clicked()), deleteMapper, SLOT(map()));
 deleteMapper->setMapping(btnDelete, row);
 ui->tableWidget->setCellWidget(row, 5, btnDelete);

 QCheckBox* chk = new QCheckBox();
 enabledMapper->setMapping(chk, row);
 connect(chk, SIGNAL(toggled(bool)), enabledMapper, SLOT(map()));
 chk->setChecked(dsml->isEnabled(getDestMastFromRow(row)));
 ui->tableWidget->setCellWidget(row, 6, chk);
 QPushButton* btnEdit = new QPushButton(tr("Edit"));
 connect(btnEdit, SIGNAL(clicked()), editMapper, SLOT(map()));
 editMapper->setMapping(btnEdit, row);
 ui->tableWidget->setCellWidget(row, 7, btnEdit);
}
void SignalMastLogicWidget::propertyChange(PropertyChangeEvent *e)
{
 qDebug()<< "property change received" + e->toString();
 DefaultSignalMastLogic* lTarget = qobject_cast<DefaultSignalMastLogic*>(e->source);
 for(int row =0; row<rows.count(); row++)
 {
  DefaultSignalMastLogic* l = rows.at(row);
  if(l == lTarget)
  {
   updateRows(row, lTarget);
   break;
  }
 }
}

void SignalMastLogicWidget::on_tableWidget_cellChanged(int row, int col)
{
 if(row >= rows.count()) return; // value not yet added
 DefaultSignalMastLogic* l = rows.at(row);
 switch(col)
 {
 case 4: // comment
//     l->setComment(ui->tableWidget->item(row,col)->text());
  break;
 default:
  break;
 }
}
void SignalMastLogicWidget::on_newSignalMastLogicCreated(SignalMastLogic *s)
{
 int row = ui->tableWidget->rowCount();
 ui->tableWidget->setRowCount(row +1);
 rows.append((DefaultSignalMastLogic*)s);
 updateRows(row,(DefaultSignalMastLogic*)s);
}
/*public*/ SignalMast* SignalMastLogicWidget::getDestMastFromRow(int row)
{
 // if object has been deleted, it's not here; ignore it
 QHash<SignalMastLogic*, SignalMast*> b = signalMastLogicList.value(row);
 QListIterator<SignalMastLogic*> en(b.keys());
    while (en.hasNext()) {
        return b.value(en.next());
    }
    return NULL;
}
/*protected*/ /*synchronized*/ void SignalMastLogicWidget::updateNameList()
{
 // first, remove listeners from the individual objects
 if (!signalMastLogicList .isEmpty())
 {
  for (int i = 0; i< signalMastLogicList.size(); i++)
  {
   // if object has been deleted, it's not here; ignore it
  QHash<SignalMastLogic*, SignalMast*> b = signalMastLogicList.value(i);
   QListIterator<SignalMastLogic*> en (b.keys());
   while (en.hasNext())
   {
    SignalMastLogic* sm = en.next();
    SignalMast* dest = b.value(sm);
    sm->removePropertyChangeListener((PropertyChangeListener*)this);
    sm->getSourceMast()->removePropertyChangeListener((PropertyChangeListener*)this);
    dest->removePropertyChangeListener((PropertyChangeListener*)this);
   }
  }
 }
 QList<SignalMastLogic*> source = mgr->getSignalMastLogicList();
  signalMastLogicList =  QList<QHash<SignalMastLogic*, SignalMast*> >();
  for (int i = 0; i< source.size(); i++)
  {
    QList<SignalMast*> destList = source.at(i)->getDestinationList();
    source.at(i)->addPropertyChangeListener((PropertyChangeListener*)this);
    connect(((DefaultSignalMastLogic*)source.at(i)), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    source.at(i)->getSourceMast()->addPropertyChangeListener((PropertyChangeListener*)this);
    connect(source.at(i)->getSourceMast(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    for (int j = 0; j<destList.size(); j++)
    {
     QHash<SignalMastLogic*, SignalMast*> hash =  QHash<SignalMastLogic*, SignalMast*>();
     hash.insert(source.at(i), destList.at(j));
     destList.at(j)->addPropertyChangeListener((PropertyChangeListener*)this);
     signalMastLogicList.append(hash);
     connect(destList.at(j), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
 }
}
void SignalMastLogicWidget::on_editMapper_signaled(int row)
{
DefaultSignalMastLogic* l = rows.at(row);
SignallingFrame* frame = new SignallingFrame();
frame->initComponents(l->source, l->destination);
frame->show();
}
void SignalMastLogicWidget::on_enabledMapper_signaled(int)
{

}
void SignalMastLogicWidget::on_deleteMapper_signaled(int)
{

}
void SignalMastLogicWidget::on_btnAdd_clicked()
{
 SignallingFrame* frame = new SignallingFrame();
 frame->initComponents(NULL, NULL);
 frame->show();
}
