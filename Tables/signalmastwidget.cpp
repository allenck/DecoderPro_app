#include "signalmastwidget.h"
#include "ui_signalmastwidget.h"
#include "instancemanager.h"
#include "abstractsignalmast.h"
#include "defaultsignalmastmanager.h"
#include "addsignalmastpanel.h"
#include "../LayoutEditor/jmrijframe.h"
#include "signallingsourceaction.h"

SignalMastWidget::SignalMastWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignalMastWidget)
{
 ui->setupUi(this);
 log = new Logger("SignalHeadWidget");
 mgr = (DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance();
 //mgr->addPropertyChangeListener((PropertyChangeListener*)this);
 connect(mgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 aspectMapper = new QSignalMapper();
 deleteMapper = new QSignalMapper();
 editMapper = new QSignalMapper();
 editLogicMapper = new QSignalMapper();
 litMapper = new QSignalMapper();
 heldMapper = new QSignalMapper();
 ui->tableWidget->clearContents();
 ui->tableWidget->resizeColumnsToContents();
 ui->tableWidget->verticalHeader()->setHidden(true);

 connect(mgr, SIGNAL(newSignalMastCreated(AbstractSignalMast*)), this, SLOT(on_newSignalMastCreated(AbstractSignalMast*)));
 fillTable();
 //signalHeadTableAction = new SignalHeadTableAction(tr("SignalTable"));
 ui->tableWidget->resizeColumnsToContents();
 connect(aspectMapper, SIGNAL(mapped(int)), this, SLOT(on_aspectMapper_signaled(int)));
 connect(deleteMapper, SIGNAL(mapped(int)), this, SLOT(on_deleteMapper_signaled(int)));
 connect(editMapper, SIGNAL(mapped(int)), this, SLOT(on_editMapper_signaled(int)));
 connect(editLogicMapper, SIGNAL(mapped(int)), this, SLOT(on_editLogicMapper_signaled(int)));
 connect(litMapper, SIGNAL(mapped(int)), this, SLOT(on_litMapper_signaled(int)));
 connect(heldMapper, SIGNAL(mapped(int)), this, SLOT(on_heldMapper_signaled(int)));
}

SignalMastWidget::~SignalMastWidget()
{
    delete ui;
}
void SignalMastWidget::fillTable()
{
 int row = ui->tableWidget->rowCount();
 QStringList list = mgr->getSystemNameList();
 ui->tableWidget->setRowCount(row + list.count());
 ui->tableWidget->setAlternatingRowColors(true);
 ui->tableWidget->resizeColumnsToContents();
 ui->tableWidget->setColumnCount(9);

 foreach (QString sysName, list)
 {
  AbstractSignalMast* s = (AbstractSignalMast*)mgr->getBySystemName(sysName);
  updateRows(row, s);
  rows.append(s);
//  PropertyChangeListener* l = new PropertyChangeListener();
//  s->addPropertyChangeListener(l);
  connect(s, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  row++;
 }
 connect(ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(on_tableWidget_cellChanged(int,int)));
}
void SignalMastWidget::updateRows(int row, AbstractSignalMast* l)
{
 QTableWidgetItem* sn = new QTableWidgetItem(l->getSystemName());
 sn->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
 ui->tableWidget->setItem(row, 0,sn);
 QTableWidgetItem* un = new QTableWidgetItem(l->getUserName());
 ui->tableWidget->setItem(row, 1, un);
 QComboBox* cbAspect = new QComboBox();
 cbAspect->addItems(l->getValidAspects().toList());
 //cbAspect->setEditText(l->getAspect());
 cbAspect->setCurrentIndex(cbAspect->findText(l->getAspect()));
 aspectMapper->setMapping(cbAspect, row);
 connect(cbAspect, SIGNAL(currentIndexChanged(int)), aspectMapper, SLOT(map()));
 ui->tableWidget->setCellWidget(row, 2, cbAspect);
 QTableWidgetItem* comment = new QTableWidgetItem(l->getComment());
 ui->tableWidget->setItem(row, 3, comment);

 QPushButton* btnDelete = new QPushButton(tr("Delete"));
 deleteMapper->setMapping(btnDelete, row);
 connect(btnDelete, SIGNAL(clicked()), deleteMapper, SLOT(map()));
 ui->tableWidget->setCellWidget(row, 4, btnDelete);

 QPushButton* btnEdit = new QPushButton(tr("Edit"));
 editMapper->setMapping(btnEdit, row);
 connect(btnEdit, SIGNAL(clicked()), editMapper, SLOT(map()));
 ui->tableWidget->setCellWidget(row, 5, btnEdit);

 QPushButton* btnEditLogic = new QPushButton(tr("Edit logic"));
 editLogicMapper->setMapping(btnEditLogic, row);
 connect(btnEditLogic, SIGNAL(clicked()), editLogicMapper, SLOT(map()));
 ui->tableWidget->setCellWidget(row, 6, btnEditLogic);

 QCheckBox* chkLit = new QCheckBox();
 litMapper->setMapping(chkLit, row);
 connect(chkLit, SIGNAL(clicked()), litMapper, SLOT(map()));
 chkLit->setChecked(l->getLit());
 ui->tableWidget->setCellWidget(row, 7, chkLit);

 QCheckBox* chkHeld = new QCheckBox();
 litMapper->setMapping(chkHeld, row);
 connect(chkHeld, SIGNAL(clicked()), litMapper, SLOT(map()));
 chkHeld->setChecked(l->getHeld());
 ui->tableWidget->setCellWidget(row, 8, chkHeld);
}
void SignalMastWidget::propertyChange(PropertyChangeEvent *e)
{
 qDebug()<< "property change received" + e->toString();
 if(e->getPropertyName() == "length")
 {
  qDebug()<<tr("recvd property change '%1' from ").arg(e->getPropertyName())+e->source->metaObject()->className();
  aspectMapper = new QSignalMapper();
  deleteMapper = new QSignalMapper();
  editMapper = new QSignalMapper();
  editLogicMapper = new QSignalMapper();
  litMapper = new QSignalMapper();
  heldMapper = new QSignalMapper();
  ui->tableWidget->clearContents();
  fillTable();
 }
 AbstractSignalMast* lTarget = qobject_cast<AbstractSignalMast*>(e->source);
 for(int row =0; row<rows.count(); row++)
 {
  AbstractSignalMast* l = rows.at(row);
  if(l == lTarget)
  {
   updateRows(row, lTarget);
  }
 }
}

void SignalMastWidget::on_tableWidget_cellChanged(int row, int col)
{
 if(row >= rows.count()) return; // value not yet added
 AbstractSignalMast* l = rows.at(row);
 switch(col)
 {
 case 3: // comment
     l->setComment(ui->tableWidget->item(row,col)->text());
  break;
 default:
  break;
 }
}
void SignalMastWidget::on_btnAdd_clicked()
{
    JmriJFrame * panel = new JmriJFrame("Add Signal Mast");
    AddSignalMastPanel* asp = new AddSignalMastPanel();
    QFont font;
    font.setPointSize(9);
    panel->setFont(font);
    panel->setCentralWidget(asp);
    panel->show();
}
void SignalMastWidget::on_newSignalMastCreated(AbstractSignalMast *m)
{
 int row = ui->tableWidget->rowCount();

 updateRows(row, m);
 rows.append(m);
}
void SignalMastWidget::on_deleteMapper_signaled(int row)
{
    AbstractSignalMast* mast = rows.at(row);
    // TODO:
}
void SignalMastWidget::on_aspectMapper_signaled(int row)
{
 QComboBox* cbAspect = (QComboBox*) ui->tableWidget->cellWidget(row, 2);
 AbstractSignalMast* mast = rows.at(row);
 mast->setAspect(cbAspect->currentText());
}
void SignalMastWidget::on_editMapper_signaled(int row)
{
 AbstractSignalMast* mast = rows.at(row);
 AddSignalMastPanel* panel = new AddSignalMastPanel((SignalMast*)mast);
 panel->show();
}
void SignalMastWidget::on_editLogicMapper_signaled(int row)
{
 SignallingSourceAction* action = new SignallingSourceAction(tr("Signal Mast Logic Table"), (SignalMast*) rows.at(row));
 action->actionPerformed(NULL);

}
void SignalMastWidget::on_litMapper_signaled(int row)
{
 QCheckBox* chkLit = (QCheckBox*) ui->tableWidget->cellWidget(row, 7);
 AbstractSignalMast* mast = rows.at(row);
 mast->setLit(chkLit->isChecked());
}
void SignalMastWidget::on_heldMapper_signaled(int row)
{
 QCheckBox* chkHeld = (QCheckBox*) ui->tableWidget->cellWidget(row, 8);
 AbstractSignalMast* mast = rows.at(row);
 mast->setHeld(chkHeld->isChecked());
}
