#include "listthrottles.h"
#include "ui_listthrottles.h"
#include "loconetsystemconnectionmemo.h"
#include "lnthrottlemanager.h"
#include "../LayoutEditor/panelmenu.h"
#include "../LayoutEditor/editor.h"
#include "loconetthrottle.h"
#include "instancemanager.h"
#include "lnpowermanager.h"
#include "Throttle/throttlewindow.h"
#include "throttlestablecellrenderer.h"
#include "Throttle/throttleframemanager.h"
#include "dccthrottle.h"

ListThrottles::ListThrottles(/*LocoNetSystemConnectionMemo* memo,*/ QWidget *parent) :
    JmriJFrame(parent),
    ui(new Ui::ListThrottles)
{
 ui->setupUi(this);
//    this->memo = memo;
 log = new Logger("ListThrottles");
 newThrottle = new QAction(QIcon(":/resources/icons/throttles/new.png"), tr("New Throttle"),this);
 connect(newThrottle, SIGNAL(triggered()), this, SLOT(on_newThrottle_clicked()));
 ui->toolBar->addAction(newThrottle);
 emergencyStop = new QAction(QIcon(":/resources/icons/throttles/estop.png"), tr("Emergency stop"), this);
 connect(emergencyStop, SIGNAL(triggered()), this, SLOT(on_emergencyStop_clicked()));
 ui->toolBar->addAction(emergencyStop);

 pmgr=(LnPowerManager*)InstanceManager::powerManagerInstance();
 if(this->pmgr != NULL)
 {
  //LnPowerManager* pmgr = memo->getPowerManager();
  pmgr->addPropertyChangeListener((PropertyChangeListener*)this);
  connect(pmgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  if(pmgr->isPowerOn())
   togglePower = new QAction(QIcon(":/resources/icons/throttles/power_green.png"), tr("Power on"), this);
  else if (pmgr->isPowerOff())
   togglePower = new QAction(QIcon(":/resources/icons/throttles/power_red.png"), tr("Power off"), this);
  else
   togglePower = new QAction(QIcon(":/resources/icons/throttles/power_yellow.png"), tr("Power unknown"), this);
 }
 else
  togglePower = new QAction(QIcon(":/resources/icons/throttles/power_yellow.png"), tr("Power unknown"), this);
 connect(togglePower, SIGNAL(triggered()), this, SLOT(on_togglePower_clicked()));
 ui->toolBar->addAction(togglePower);
 throttlePrefs = new QAction(QIcon(":/resources/icons/throttles/preferences.png"), tr("Throttle preferences"),this);
 ui->toolBar->addAction(throttlePrefs);
 //LnThrottleManager* mgr = (LnThrottleManager*)InstanceManager::throttleManagerInstance();
 refreshList();
 PanelMenu::instance()->addEditorPanel((Editor*)this);
 connect(PanelMenu::instance(),SIGNAL(newThrottleWindow()), this, SLOT(refreshList()));
 renderer = new ThrottlesTableCellRenderer();
 connect(ThrottleFrameManager::instance(), SIGNAL(newThrottle(ThrottleWindow*)), this, SLOT(refreshList()));
}

ListThrottles::~ListThrottles()
{
    delete ui;
}
void ListThrottles::on_togglePower_clicked()
{
// LnPowerManager* pmgr = memo->getPowerManager();
 if(pmgr->isPowerOn())
  pmgr->setPower(PowerManager::OFF);
 else
  pmgr->setPower(PowerManager::ON);
}
void ListThrottles::propertyChange(PropertyChangeEvent *e)
{
 if(e->getPropertyName() == "Power")
 {
  //LnPowerManager* pmgr = memo->getPowerManager();
  if(pmgr->isPowerOn())
  {
   togglePower->setIcon(QIcon(":/resources/icons/throttles/power_green.png"));
   togglePower->setText(tr("Power on"));
  }
  else if (pmgr->isPowerOff())
  {
   togglePower->setIcon(QIcon(":/resources/icons/throttles/power_red.png"));
   togglePower->setText(tr("Power off"));
  }
  else
  {
   togglePower->setIcon(QIcon(":/resources/icons/throttles/power_yellow.png"));
   togglePower->setText( tr("Power unknown"));
  }
 }
 else
     log->debug(tr("Property change '%1'").arg(e->getPropertyName()));
}
void ListThrottles::on_emergencyStop_clicked()
{

}
void ListThrottles::on_newThrottle_clicked()
{
 ThrottleWindow* tw = ThrottleFrameManager::instance()->createThrottleWindow();
 tw->show();
}
QString ListThrottles::getTitle() { return windowTitle();}

void ListThrottles::refreshList()
{
// for(int row = 0; row < ui->tableWidget->rowCount(); row++)
// {
//  QWidget* widget = ui->tableWidget->cellWidget(row,0);
// }
 ui->tableWidget->clear();
 ui->tableWidget->setColumnCount(1);
 //QList<Editor*>* list = PanelMenu::instance()->getEditorPanelList();
 QListIterator<ThrottleWindow*> iter = ThrottleFrameManager::instance()->getThrottleWindows();

 int row = 0;
 ui->tableWidget->setRowCount(ThrottleFrameManager::instance()->getNumberThrottleWindows());
 while(iter.hasNext())
 {
   ThrottleWindow* tw = (ThrottleWindow*)iter.next();
   tw->disconnect();
   connect(tw, SIGNAL(throttleWindowupdate(PropertyChangeEvent*)), this, SLOT(onThrottleWindowChanged(PropertyChangeEvent*)));
   Throttle* t = tw->getThrottle();
   QString text = tw->getTitle();
   if(t != NULL)
    text.append((((LocoNetThrottle*)t)->getIsForward()?tr("Forward"):tr("Reverse")) + " " + QString("%1%").arg((int)(((LocoNetThrottle*)t)->getSpeedSetting()*100)));
   //QListWidgetItem* item =new QListWidgetItem(text);

   //item->setData(Qt::UserRole,VPtr<ThrottleWindow>::asQVariant(tw));
   //ui->listWidget->addItem(item);
   QWidget* w;
   ui->tableWidget->setCellWidget(row, 0, w = renderer->getTableCellRendererComponent(ui->tableWidget,VPtr<ThrottleWindow>::asQVariant(tw),true, true,row, 0));
   ui->tableWidget->setRowHeight(row, w->height());
   DccThrottle* at = (DccThrottle*)t;
   row++;
  }
}
void ListThrottles::onThrottleWindowChanged(PropertyChangeEvent*)
{
// for(int i=0; i < ui->listWidget->count(); i++)
// {
//  QListWidgetItem* item = ui->listWidget->item(i);
//  ThrottleWindow* tw1 = VPtr<ThrottleWindow>::asPtr(item->data(Qt::UserRole));
//  if(tw == tw1)
//  {
//   Throttle* t = tw->getThrottle();
//   QString text = tw->getTitle();
//   if(t != NULL)
//    text.append((((LocoNetThrottle*)t)->getIsForward()?tr("Forward"):tr("Reverse")) + " " + QString("%1%").arg((int)(((LocoNetThrottle*)t)->getSpeedSetting()*100)));
//   item->setText(text);
//  }
// }
    refreshList();
}
