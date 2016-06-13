#include "slotmonitor.h"
#include "ui_slotmonitor.h"
#include "instancemanager.h"
#include "slotmanager.h"
#include <QPushButton>
#include <QMessageBox>
#include "slotmondatamodel.h"
#include "pushbuttondelegate.h" // for PushButtonItemDelegate

SlotMonitor::SlotMonitor(LocoNetSystemConnectionMemo* memo, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SlotMonitor)
{
 ui->setupUi(this);
 this->memo = memo;
 log = new Logger("SlotMonitor");
 slotModel = new SlotMonDataModel(128,16, this->memo,this);
 ui->tableView->setModel(slotModel);
 ui->tableView->setItemDelegateForColumn(SlotMonDataModel::ESTOPCOLUMN, new PushButtonDelegate());
 slotModel->configureTable(ui->tableView);
 ui->tableView->setItemDelegateForColumn(SlotMonDataModel::DISPCOLUMN, new PushButtonDelegate());
 // adjust model to default settings
 slotModel->showAllSlots(ui->chkShowUnusedSlots->isChecked());
 slotModel->showSystemSlots(ui->chkShowSystemSlots->isChecked());

}
SlotMonitor::~SlotMonitor()
{
    delete ui;
}
/*public*/ QString getHelpTarget() { return "package.jmri.jmrix.loconet.slotmon.SlotMonFrame"; }
void SlotMonitor::on_chkShowUnusedSlots_toggled(bool b)
{
 slotModel->showAllSlots(b);
 slotModel->fireTableDataChanged();
}
void SlotMonitor::on_chkShowSystemSlots_toggled(bool b)
{
 slotModel->showSystemSlots(b);
 slotModel->fireTableDataChanged();

}
void SlotMonitor::on_estopAllButton_clicked()
{
 slotModel->estopAll();
}

