#include "addpaneleditordialog.h"
#include "ui_addpaneleditordialog.h"
#include "inputdialog.h"
#include "analogclock2display.h"
#include "panelmenu.h"

AddPanelEditorDialog::AddPanelEditorDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddPanelEditorDialog)
{
 ui->setupUi(this);
 if(qobject_cast<PanelEditor*>(parent)!= NULL)
  editor = (PanelEditor*)parent;
 else
  editor = new PanelEditor(tr("New panel"));
 setWindowTitle(editor->getTitle() + tr(" Editor"));
 editor->getTargetFrame()->resize(600,400);
 editor->setAllEditable(ui->chkPopup->isChecked());
 editor->setAllPositionable(ui->chkReposition->isChecked());
 editor->setAllShowTooltip(ui->chkShowTooltips->isChecked());
 editor->setAllControlling(ui->chkControlLayout->isChecked());
 editor->setShowHidden(ui->chkShowHidden->isChecked());
 editor->setPanelMenu(ui->chkHasMenu->isChecked());
 editor->show();
 PanelMenu::instance()->addEditorPanel(editor);

 ui->cbType->clear();
 ui->cbType->addItem("",-1);
 ui->cbType->addItem(tr("Right Hand Turnout"),0);
 ui->cbType->addItem(tr("Left hand Turnout"), 1);
 ui->cbType->addItem(tr("Slip/3-Way Turnout/Scissors"), 2);
 ui->cbType->addItem(tr("Sensor"), 3);
 ui->cbType->addItem(tr("Signal Head"), 4);
 ui->cbType->addItem(tr("Signal Mast"), 5);
 ui->cbType->addItem(tr("Memory"), 6);
 ui->cbType->addItem(tr("Reporter"), 7);
 ui->cbType->addItem(tr("Light"), 8);
 ui->cbType->addItem(tr("Background"), 9);
 ui->cbType->addItem(tr("Multisensor"), 10);
 ui->cbType->addItem(tr("RPS Reporter"), 11);
 ui->cbType->addItem(tr("Fast Clock"), 12);
 ui->cbType->addItem(tr("Icon"), 13);
 ui->cbType->addItem(tr("Text/Label"),14);
}

AddPanelEditorDialog::~AddPanelEditorDialog()
{
 delete ui;
}
void AddPanelEditorDialog::on_btnSetName_clicked()
{
 InputDialog* dlg = new InputDialog(tr("Panel Name"),editor->getName(), NULL, this);
 if(dlg->exec() == QDialog::Accepted)
 {
  editor->setName(dlg->value());
  setWindowTitle(editor->getTitle() + tr(" Editor"));
 }
}
void AddPanelEditorDialog::on_edText_editingFinished(QString text)
{
 ui->btnAddText->setEnabled(text.size() > 0);
}
void AddPanelEditorDialog::on_btnAddText_clicked()
{

}
void AddPanelEditorDialog::on_cbType_activated(int i)
{
 int x = ui->edX->text().toInt();
 int y = ui->edY->text().toInt();
 editor->setLocation(x, y);

 switch(i-1)
 {
 case 0:
  //addRHTurnout();
  editor->on_addRHTurnout_triggered();
  break;
 case 1:
  //addLHTurnout();
  editor->on_addLHTurnout_triggered();
  break;
 case 2:
  //addSlipTurnout();
  editor->on_addSlipTurnout_triggered();
  break;
 case 3:
  //addSensor();
  editor->on_addSensor_triggered();
  break;
 case 6:
  editor->on_addMemory_triggered();
  break;
 case 7:
  editor->on_addReporter_triggered();
  break;
 case 8:
  editor->on_addLight_triggered();
  break;
 case 11:
  editor->on_addRPSReporter_triggered();
  break;
 case 12:
  //addClock();
  editor->on_addClock_triggered();
  break;
 case 13:
  editor->on_addIcon_triggered();
  break;
 case 14:
  editor->on_addTextLabel_triggered();
  break;
 default:
  break;
 }
}
void AddPanelEditorDialog::on_chkControlLayout_toggled(bool bState) {editor->setAllControlling(bState);}
void AddPanelEditorDialog::on_chkHasMenu_toggled(bool /*bState*/) {editor->setPanelMenu(true);}
void AddPanelEditorDialog::on_chkReposition_toggled(bool bState) {editor->setAllPositionable(bState);}
void AddPanelEditorDialog::on_chkPopup_toggled(bool bState) {editor->setAllEditable(bState);}
void AddPanelEditorDialog::on_chkShowTooltips_toggled(bool bState) {editor->setAllShowTooltip(bState);}
void AddPanelEditorDialog::on_chkShowHidden_toggled(bool bState) {editor->setShowHidden(bState);}


