#include "addeditdialog.h"
#include "ui_addeditdialog.h"
#include "abstractturnout.h"
#include "proxyreportermanager.h"
#include "instancemanager.h"

AddEditDialog::AddEditDialog(QString type, QObject* o, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEditDialog)
{
 ui->setupUi(this);
 this->type = type;
 if(type == tr("Id Tags"))
 {
  setWindowTitle("Add/Edit Id Tag");
  ui->lbSystem->setVisible(false);
  ui->cbSystem->setVisible(false);
  ui->chkAdd->setVisible(false);
  ui->lbNumToAdd->setVisible(false);
  ui->sbAdd->setVisible(false);
  ui->chkAutoGen->setVisible(false);
 }
 if(type == tr("Turnouts"))
 {
  setWindowTitle("Add/Edit Turnout");
  ui->chkAutoGen->setVisible(false);
  ui->lbSystemName->setText(tr("Hardware Address"));
  ui->chkAutoGen->setVisible(false);
  if(o != NULL )
  {
   AbstractTurnout* t = (AbstractTurnout*)o;
   ui->edSystemName->setText(t->getSystemName());
   ui->edUserName->setText(t->getUserName());
  }
 }
 if(type == tr("Sensors"))
 {
  setWindowTitle(tr("Add/Edit Sensor"));
  ui->chkAutoGen->setVisible(false);
  ui->lbSystemName->setText(tr("Hardware Address"));
  ui->chkAutoGen->setVisible(false);
 }
 if(type == tr("Reporters"))
 {
  setWindowTitle(tr("Add New Reporter"));
  ui->chkAutoGen->setVisible(false);
  ui->lbSystemName->setText(tr("Hardware Address"));
  ui->chkAutoGen->setVisible(false);
  ui->cbSystem->clear();
  ProxyReporterManager* mgr = (ProxyReporterManager*)InstanceManager::reporterManagerInstance();
  QList<Manager*> mgrList = mgr->getManagerList();
  foreach (Manager* m, mgrList)
  {
   AbstractManager* am = (AbstractManager*)m;
   char t = am->getSystemPrefix().toLocal8Bit().at(0);
   switch(t)
   {
   case 'I':
    ui->cbSystem->addItem(tr("Internal"), t);
    break;
   case 'L':
    ui->cbSystem->addItem(tr("LocoNet"), t);
    break;
   case 'R':
    ui->cbSystem->addItem(tr("RFID"), t);
    break;
   }
  }
 }
 if(type == tr("Memory Variables"))
 {
  setWindowTitle(tr("Add New Memory"));
  ui->lbSystem->setVisible(false);
  ui->cbSystem->setVisible(false);
 }
 if(type == tr("Blocks"))
 {
  setWindowTitle(tr("Add/Edit Block"));
  ui->lbSystem->setVisible(false);
  ui->cbSystem->setVisible(false);
 }
}

AddEditDialog::~AddEditDialog()
{
 delete ui;
}
QString AddEditDialog::systemName() {return ui->edSystemName->text();}

QString AddEditDialog::userName() {return ui->edUserName->text();}

QString AddEditDialog::system() { return ui->cbSystem->currentText();}

bool AddEditDialog::isAddRange() { return ui->chkAdd->isChecked();}

bool AddEditDialog::isAutoGen() { return ui->chkAutoGen->isChecked();}

int AddEditDialog::numToAdd() { return ui->sbAdd->value();}

void AddEditDialog::on_btnOK_clicked()
{
 if(ui->edSystemName->text().isEmpty()) return;
 accept();
 close();
}
void AddEditDialog::on_chkAutoGen_toggled(bool bState)
{
 ui->lbSystemName->setEnabled(!bState);
 ui->edSystemName->setEnabled(!bState);
 if(bState)
  ui->edSystemName->setText("");
}
void AddEditDialog::on_chkAdd_toggled(bool bState)
{
 if(bState)
 {
  QIntValidator v(1, 2048, this);
  ui->edSystemName->setValidator(&v);
  ui->sbAdd->setEnabled(true);
 }
 else
 {
  ui->edSystemName->setValidator(NULL);
  ui->sbAdd->setEnabled(false);
 }
}
int AddEditDialog::mgrIndex() { return ui->cbSystem->currentIndex();}
