#include "sensorwidget.h"
#include "ui_sensorwidget.h"
#include "instancemanager.h"
#include "addeditdialog.h"
#include "connectionnamefromsystemname.h"
#include <QMessageBox>
#include "jtextfield.h"
#include <QBoxLayout>
#include "proxysensormanager.h"
#include "sensortableaction.h"
#include <QLabel>

SensorWidget::SensorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorWidget)
{
 ui->setupUi(this);
 ui->tabWidget->clear(); // remove default tabs
 widgets.clear();
 tableWidget1 = new SensorTableWidget(-1, this); // ALL
 ui->tabWidget->addTab(tableWidget1,tr("All"));
 widgets.append(tableWidget1);
 int iMgr = 0;
 ProxySensorManager* mgr = (ProxySensorManager*)InstanceManager::sensorManagerInstance();
 for(iMgr = 0; iMgr < mgr->nMgrs(); iMgr++)
 {
  SensorTableWidget* sensorTableWidget = new SensorTableWidget(iMgr,this);
  QString sName = mgr->getMgr(iMgr)->metaObject()->className();
  ui->tabWidget->addTab(sensorTableWidget,sName.mid(0, sName.indexOf("SensorManager")));
  widgets.append(sensorTableWidget);
  sensorTableWidget->showDebounceInfo(ui->chkShowDebounceInfo);
 }
// tableWidget2 = new SensorTableWidget(iMgr, this); // Internal only
// ui->tabWidget->addTab(tableWidget2, tr("Internal"));
// widgets.append(tableWidget2);
 ui->chkShowDebounceInfo->setChecked(false);
 setWindowTitle("Sensors");
 action = new SensorTableAction("SensorTable", this);
}

SensorWidget::~SensorWidget()
{
    delete ui;
}
void SensorWidget::on_chkShowDebounceInfo_toggled(bool bState)
{
// tableWidget1->showDebounceInfo(bState);
// tableWidget2->showDebounceInfo(bState);
 foreach(SensorTableWidget* tableWidget, widgets)
  tableWidget->showDebounceInfo(bState);
}
void SensorWidget::on_btnAdd_clicked()
{
#if 0
 AddEditDialog dlg(tr("Sensors"),this);
 if(dlg.exec() == QDialog::Accepted)
 {
  ProxySensorManager* mgr = (ProxySensorManager*)InstanceManager::sensorManagerInstance();
  QString sysName;
  QString system = dlg.system();
  QString userName = dlg.userName();
  int iMgr =mgr->nMgrs()-1;
  if(system != tr("Internal")) iMgr= 0;
  AbstractSensorManager* smgr = (AbstractSensorManager*)mgr->getMgr(iMgr);
  QString sPrefix = smgr->getSystemPrefix()+ smgr->typeLetter();
  if(dlg.isAddRange())
  {
   int count = dlg.numToAdd();
   int addr = dlg.systemName().toInt();
   for(int iAddr = addr; iAddr < addr + count -1; iAddr++)
   {
    sysName = sPrefix+QString("%1").arg(iAddr);
    mgr->newSensor(sysName, userName+QString("%1").arg(iAddr));
   }
  }
  else
  {
   sysName = sPrefix+dlg.systemName();
   mgr->newSensor(sysName, userName);
  }
 }
#else
 action->addPressed();
#endif
}
/*protected*/ void SensorWidget::setDefaultDebounce(QWidget* _who)
{
 ProxySensorManager* senManager = (ProxySensorManager*)InstanceManager::sensorManagerInstance();

 JTextField* activeField = new JTextField(QString::number(senManager->getDefaultSensorDebounceGoingActive()),4);
 JTextField* inActiveField = new JTextField(QString::number(senManager->getDefaultSensorDebounceGoingInActive()),4);

 QWidget* active = new QWidget();
 active->setLayout(new QHBoxLayout);
 active->layout()->addWidget(new QLabel(tr("Debounce Active Timer")));
 active->layout()->addWidget(activeField);

 QWidget* inActive = new QWidget();
 inActive->setLayout(new QHBoxLayout);
 inActive->layout()->addWidget(new QLabel(tr("Debounce InActive Timer")));
 inActive->layout()->addWidget(inActiveField);

// int retval = JOptionPane.showOptionDialog(_who,
//                                      tr("SensorGlobalDebounceMessageBox") , tr("SensorGlobalDebounceMessageTitle"),
//                                      0, JOptionPane.INFORMATION_MESSAGE, null,
//                                      new Object[]{"Cancel", "OK", active, inActive}, null );
 QMessageBox* box = new QMessageBox(QMessageBox::Information, tr("Sensor Debounce Timer"), tr("Set the default values for the time it takes to register a change in sensor state\n                                                                                          Duration is in Milliseconds"),QMessageBox::Cancel | QMessageBox::Ok,_who );
 box->layout()->addWidget(active);
 box->layout()->addWidget(inActive);
 int retval = box->exec();
 if (retval != QMessageBox::Ok)
 {
  return;
 }

 //We will allow the turnout manager to handle checking if the values have changed
// try
// {
 bool bOk;
 long goingActive = activeField->text().toLong(&bOk);
 if(!bOk)
     QMessageBox::critical(_who, tr("Input error"), tr("Value for Active Duration, must be a Number"));
 senManager->setDefaultSensorDebounceGoingActive(goingActive);
//    } catch (NumberFormatException ex) {
//        JOptionPane.showMessageDialog(_who, tr("SensorDebounceActError")+"\n" + activeField.getText(), "Input Error", JOptionPane.ERROR_MESSAGE);
//    }

//    try {
 long goingInActive = inActiveField->text().toLong(&bOk);
 QMessageBox::critical(_who, tr("Input error"), tr("Value for Active Duration, must be a Number"));

 senManager->setDefaultSensorDebounceGoingInActive(goingInActive);
//    } catch (NumberFormatException ex) {
//        JOptionPane.showMessageDialog(_who, tr("SensorDebounceActError")+"\n" + inActiveField.getText(), "Input Error", JOptionPane.ERROR_MESSAGE);
//    }
//    m.fireTableDataChanged();
}
void SensorWidget::setDefaults_triggered()
{
 setDefaultDebounce(this);
}
