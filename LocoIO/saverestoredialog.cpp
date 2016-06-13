#include "saverestoredialog.h"
#include "ui_saverestoredialog.h"

SaveRestoreDialog::SaveRestoreDialog(bool bSaveMode, LocoIOData* data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveRestoreDialog)
{
 ui->setupUi(this);
 ui->lblHelp->setText("");
 this->_defaults = _defaults;
 this->bSaveMode = bSaveMode;
 this->data = data;
 if(!bSaveMode)
  ui->cbModules->setEditable(false);
 else
 {
  ui->btnDelete->setVisible(false);
  vals->clear();
  *vals << data->getUnitConfig() << data->getUnitAddress() << data->getUnitSubAddress();
  for(int channel = 0; channel < 48; channel++)
  {
   *vals << data->getV1(channel) << data->getV2(channel), data->getSV(channel);
  }
 }
 getSettings();
 ui->editAddr->setText(QString("%1 (0x%2)").arg(data->getUnitAddress()).arg(data->getUnitAddress(),0,16));
 ui->editSubUnit->setText(QString("%1 (0x%2)").arg(data->getUnitSubAddress()).arg(data->getUnitSubAddress(),0,16));
}

SaveRestoreDialog::~SaveRestoreDialog()
{
    delete ui;
}
void SaveRestoreDialog::getSettings()
{
 QSettings settings;
 settings.beginGroup("Modules");
 modules = settings.value("Modules").toStringList();
 settings.endGroup();
 descriptions.clear();
 foreach(QString s_module, modules)
 {
  settings.beginGroup(s_module);
  descriptions << settings.value("Description").toString();
  settings.endGroup();
 }
 if(modules.isEmpty())
  saveDefaults();
 vals = NULL;
 ui->cbModules->clear();
 if(bSaveMode)
 {
  ui->cbModules->addItem("New module");
  ui->cbModules->setEditable(true);
 }
 else
  ui->cbModules->setEditable(false);
 foreach(QString module, modules)
  ui->cbModules->addItem(module);
}
void SaveRestoreDialog::on_cbModules_currentIndexChanged(int index)
{
 if(index < 0)
  return;
 if(index == 0)
 {
  if(bSaveMode && ui->cbModules->currentText() == tr("New module"))
  {
   ui->btnDelete->setEnabled(false);
   ui->btnOK->setEnabled(false);
  }
  if(!ui->editDescription->text().isEmpty())
  {
   ui->btnOK->setEnabled(true);
  }
 }
 if(!bSaveMode)
  ui->btnOK->setEnabled(true);
 int currIndex = bSaveMode ? index-1 : index;
 if(currIndex >= 0)
 {
  ui->editDescription->setText(descriptions.at(currIndex));
  moduleName = modules.at(currIndex);
  if( vals == NULL)
  {
     vals = new QList<int>();
     vals->reserve(51);
     for(int i=0; i < 51; i++)
      vals->append(0);
  }
  QSettings settings;
  settings.beginGroup(modules.at(currIndex));
  QList<QVariant> list = settings.value("CVs").toList();
  vals->clear();
  foreach(QVariant qv, list)
   vals->append(qv.toInt());
  ui->editDescription->setText(settings.value("Description").toString());
  settings.endGroup();
  if(vals->count() > 1)
  {
   ui->editAddr->setText(QString("0x%1 (%2)").arg(vals->at(1),0,16).arg(vals->at(1)));
   ui->editSubUnit->setText(QString("0x%1 (%2)").arg(vals->at(2),0,16).arg(vals->at(2)));
  }
  ui->btnOK->setEnabled(true);
 }
}
void SaveRestoreDialog::setValues(QList<int> *vals, QString module)
{
 this->vals = vals;
 int curIndex = modules.indexOf(module);
 if(curIndex < 0)
  ui->cbModules->setCurrentIndex(0);
 else
  ui->cbModules->setCurrentIndex(curIndex+1);
 moduleName = module;
 if(!modules.contains(module))
  modules.append(module);
}
QList<int>* SaveRestoreDialog::getValues()
{
 return vals;
}
QString SaveRestoreDialog::getModuleName()
{
 return moduleName;
}
QStringList SaveRestoreDialog::moduleNames() { return modules;}
QStringList SaveRestoreDialog::moduleDescriptions() { return descriptions;}

void SaveRestoreDialog::on_btnOK_clicked()
{
 if(ui->cbModules->currentIndex() < 0)
 {
  ui->lblHelp->setText(tr("Select a module"));
  return;
 }
 if(ui->cbModules->currentText() == "New module" || ui->cbModules->currentText().isEmpty() || ui->editDescription->text().isEmpty())
 {
  ui->lblHelp->setText(tr("Enter module name and description"));
  return;
 }
 if(vals == NULL)
 {
  ui->lblHelp->setText(tr("Values not set."));
  return;
 }
 QString s_moduleName = ui->cbModules->currentText();
 if(!modules.contains(s_moduleName))
  modules.append(s_moduleName);
 QSettings settings;
 settings.beginGroup("Modules");
 settings.setValue("Modules", modules);
 settings.endGroup();
 settings.beginGroup(s_moduleName);
 settings.setValue("Description", ui->editDescription->text());
 settings.endGroup();
 accept();
 close();
 ui->cbModules->clear();
 ui->cbModules->addItem("New module");
 foreach(QString s_module, modules)
  ui->cbModules->addItem(s_module);
 }
void SaveRestoreDialog::setDefaults(QList<int> *vals)
{
 this->vals = vals;
}
void SaveRestoreDialog::saveDefaults()
{
 modules << "Default";
 descriptions << "Default values";
 QSettings settings;
 settings.beginGroup("Modules");
 settings.setValue("Modules", modules);
 settings.endGroup();
 settings.beginGroup("Default");
 settings.setValue("Description", "Default values");
 QList<QVariant> list;
 foreach(int cv, *_defaults)
  list.append(QVariant(cv));
 settings.setValue("CVs", list);
 settings.endGroup();
}
void SaveRestoreDialog::closeEvent(QCloseEvent *)
{

}
void SaveRestoreDialog::on_btnCancel_clicked()
{
 reject();
 close();
}
void SaveRestoreDialog::on_btnDelete_clicked()
{
 int index = ui->cbModules->currentIndex();
 if(index < 0 )
 {
  ui->lblHelp->setText(tr("Select a module to delete"));
  return;
 }
 int currIndex = bSaveMode ? index-1 : index;
 Q_UNUSED(currIndex);
 if(index < 1 )
 {
  ui->lblHelp->setText(tr("Defaults cannot be deleted!"));
  return;
 }
 QString s_module = ui->cbModules->currentText();
 if(modules.contains(s_module))
 {
  int ix = modules.indexOf(s_module);
  Q_ASSERT(ix > 0);
  modules.removeAt(ix);
  descriptions.removeAt(ix);
  QSettings settings;
  settings.beginGroup("Modules");
  settings.remove(s_module);
  settings.endGroup();
  settings.beginGroup(s_module);
  settings.remove("");
  settings.endGroup();
 }
 else
  ui->lblHelp->setText(tr("Can't find '%1'").arg(s_module));
}
void SaveRestoreDialog::on_editDescription_editingFinished()
{
 QString text = ui->editDescription->text();
 if(modules.contains(text))
 {
  int ix = modules.indexOf(text);
  ui->cbModules->setCurrentIndex(ix);
  ui->btnOK->setEnabled(true);
  ui->editDescription->setText(descriptions.at(ix-1));
  return;
 }
 if((!text.isEmpty()) && ((ui->cbModules->currentIndex() > 0) ||((ui->cbModules->currentText() != "New Module") && (!ui->cbModules->currentText().isEmpty()))))
  ui->btnOK->setEnabled(true);
}
QString SaveRestoreDialog::Description()
{ return ui->editDescription->text();}
