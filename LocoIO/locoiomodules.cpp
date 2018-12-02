#include "locoiomodules.h"
#include "instancemanager.h"
#include "loconetsystemconnectionmemo.h"
//#include "locoiodata.h"
#include <QMenu>
#include "locoiodata.h"
#include "../LocoIO/locoiodialog.h"
#include "../LocoIO/sql.h"
#include "logger.h"
#include "locoioframe.h"

LocoIOModules* LocoIOModules::root = NULL;

const int LocoIOModules::locoBufferAddress  = 0x0150;

LocoIOModules::LocoIOModules(QObject *parent) :
  QObject(parent)
{
 tc = NULL;
 memo = (LocoNetSystemConnectionMemo*)InstanceManager::getDefault("LocoNetSystemConnectionMemo");
 if(qobject_cast<LocoNetSystemConnectionMemo*>(memo) != NULL)
  tc = memo->getLnTrafficController();
 data = new LocoIOData(0x51, 1,tc);
 menu = new QMenu("Configure LocoIO...");
 menu->addAction(tr("No LocoIO modules detected!"));
 sql = new Sql(data);
 log = new Logger("LocoIOModules");
 signalMapper = NULL;
 connect(data, SIGNAL(probeCompleted(QList<LocoIOAddress*>)), this, SLOT(onProbeCompleted(QList<LocoIOAddress*>)));
 lastOpCv = -1;
 bProbing = false;
 probeTimer = new QTimer(this);
 connect(probeTimer, SIGNAL(timeout()), this, SLOT(probeTimeout()));
 if (this->tc!=NULL)
 {
  //this->tc->addLocoNetListener(~0, (LocoNetListener*)this);
  connect(this->tc, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(onMessageReceived(LocoNetMessage*)));
 }
 else
 {
  log->error("No LocoNet interface available");
  return;
 }

#if 1 // temp disabled
 startProbe();
#endif
}

LocoIOModules* LocoIOModules::instance()
{
 if (root==NULL)
 {
  setRootInstance();
 }
 return root;
}
void LocoIOModules::setRootInstance()
{
 if(root!=NULL)
  return;
 root = new LocoIOModules();
}
void LocoIOModules::onMessageReceived(LocoNetMessage* m)
{
 int opCode = m->getOpCode();
 switch (opCode)
 {
  case LnConstants::OPC_PEER_XFER:
  {
   if(m->getElement(4)== 0x01)
   {
    // could be read or write operation
    // check that src_low_address is our unit, and
    // dst is "our" LocoBufferAddress
    int src = m->getElement(2);
    int dst = m->getElement(3)+m->getElement(4)*256;
    QVector<int> packet = m->getPeerXfrData();

    if ( src == lowPart(locoBufferAddress))
    {
     QString lbv = ((packet[2] != 0) ?  dotme(packet[2]) : "1.0");
     setLBVersion(lbv);
    }
    //qDebug()<< QString("dst=%1 src=%2 unitAddr=%3").arg(dst,0,16).arg(src,0,16).arg(packet[4]);
    if(dst==locoBufferAddress && m->getElement(7) == 0 && bProbing)
    {
     probeTimer->stop();
 //    stopTimer();
     log->debug( QString("probe %1 %2").arg(src).arg(packet[4]));
     LocoIOAddress* paddr = new LocoIOAddress(src, packet[4]);
//     paddr->unitAddr = src;
//     paddr->unitSubAddr = packet[4];
     QString fw = ((packet[2] != 0) ? dotme(packet[2]) : "1.3.2");
     //setLIOVersion(fw);
     paddr->setFirmwareVersion(fw);
     if(packet[2] == 0)
      paddr->setModuleType("<unknown>");
     else if(packet[2] >=1 && packet[2]<=4)
      paddr->setModuleType("LocoBooster");
     else if(packet[2] >=100 && packet[2]<=104)
      paddr->setModuleType("LocoServo");
     else if(packet[2] >=141 && packet[2]<=153)
      paddr->setModuleType("LocoIO");
     else paddr->setModuleType("<unknown>");
     bool bFound = false;
     foreach(LocoIOAddress* other, _probedAddresses)
     {
      if(other->address() == paddr->address() )
       bFound = true;
     }
     if(!bFound)
      _probedAddresses.append(paddr);
     probeTimer->start(TIMEOUT*2);
     timeoutcounter=1;
    }
   }
  }
 }
}

void LocoIOModules::startProbe()
{
 if(tc)
 {
  _probedAddresses.clear();
  probeTimer->start(TIMEOUT);
  lastOpCv = 0;
  bProbing = true;
  LocoIO::probeLocoIOs(tc);
 }
}
bool compare(LocoIOAddress* a1, LocoIOAddress* a2)
{
 return a1->address() < a2->address();
}

void LocoIOModules::probeTimeout()
{
 bProbing = false;
 probeTimer->stop();
 qSort(_probedAddresses.begin(), _probedAddresses.end(), compare);
 onProbeCompleted(_probedAddresses);
}

void LocoIOModules::onProbeCompleted(QList<LocoIOAddress* > list)
{
 //slotManager->update();

 if(list.isEmpty())
 {
  //QMessageBox::critical(this, tr("Error"), tr("No LocoIO modules found!"));
  //ui->statusbar->showMessage(tr("No LocoIO modules found!"),20000);
 }
 signalMapper = new QSignalMapper(this);
 this->list = list;
 menu->clear();
 int i=0;
 foreach(LocoIOAddress* addr, list)
 {
  QAction* act = new QAction(QString("0x%1/0x%2 (%4/%5) %6 %3").arg(addr->unitAddress(), 0, 16).arg(addr->unitSubAddress(),0,16).arg(addr->firmwareVersion()).arg(addr->unitAddress(), 0, 10).arg(addr->unitSubAddress(),0,10).arg(addr->moduleType()),this);
  act->setToolTip(tr("Configure LocoIO module 0x%1/0x%2 %6 %3").arg(addr->unitAddress(), 0, 16).arg(addr->unitSubAddress()).arg(addr->firmwareVersion()).arg(addr->moduleType()));
  if(!connect(act, SIGNAL(triggered()), signalMapper, SLOT(map())))
   qDebug()<<"action mapping failed to connect";
  signalMapper->setMapping(act,i++);
  //connect(act, SIGNAL(triggered()), this, SLOT(on_actionLocoIO_triggered()));
  menu->addAction(act);
 }
 if(!connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(onLocoIO_selected(int))))
  qDebug()<<"signal mapping failed to connect";

 emit probeCompleted(list);
}

QMenu* LocoIOModules::getMenu() { return menu;}

void LocoIOModules::on_actionLocoIO_triggered(/*bool bNewAddress*/)
{
 //Q_UNUSED(bNewAddress)
 //foreach(LocoIODialog* dlg, moduleDlg)
 foreach(LocoIOFrame* dlg, moduleDlg)
 {
  if(log->isDebugEnabled()) log->debug(QString("dialog for address 0x%1/0x%2").arg(dlg->address()->unitAddress(),0,16).arg(dlg->address()->unitSubAddress(),0, 16));

  if((dlg->address()->unitAddress() == address->unitAddress()) && (dlg->address()->unitSubAddress() == address->unitSubAddress()) )
  {
   dlg->show();
   return;
  }
 }
 //LocoIODialog* newDlg = new LocoIODialog(address, memo->getLnTrafficController(), bHexValues, sql, /*this*/NULL);
 LocoIOFrame* newDlg = new LocoIOFrame(address, memo->getLnTrafficController(), bHexValues, sql, /*this*/NULL);
// newDlg->setAddress(data->getUnitAddress(), data->getUnitSubAddress());
 newDlg->show();
 if(log->isDebugEnabled()) log->debug(QString("LocoIo dialog created 0x%1/0x%2").arg(newDlg->address()->unitAddress(),0, 16).arg(newDlg->address()->unitSubAddress(), 0,16));
 moduleDlg.append(newDlg);

}

void LocoIOModules::onLocoIO_selected(int index) // [slot]
{
 address = list.at(index);
// bool bAddressChange = false;
// if(data->getUnitAddress() != addr.unitAddr || data->getUnitSubAddress() != addr.unitSubAddr)
// {
//  bAddressChange = true;
//  //checkDirty();
// }
// data->setUnitAddress(addr.unitAddr );
// data->setUnitSubAddress(addr.unitSubAddr);
// data->setModuleType(addr.moduleType);
// if(log->isDebugEnabled()) log->debug(QString("LocoIo module 0x%1/0x%2").arg(addr.unitAddr,0, 16).arg(addr.unitSubAddr, 0,16));
 on_actionLocoIO_triggered(/*bAddressChange*/);
}
/*protected*/ int LocoIOModules::highPart(int value)
{ // generally value 1
 return value/256;
}

/*protected*/ int LocoIOModules::lowPart(int value)
{ // generally value 2
 return value-256*highPart(value);
}
/*private*/ QString LocoIOModules::dotme(int val)
{
 int dit;
 int x = val;
 QString ret;// = new StringBuffer();
 if (val == 0) return "0";
 while (x != 0)
 {
  dit = x % 10;
  ret.insert(0,QString("%1").arg(dit));
  x = x / 10;
  if (x != 0) ret.insert(0, ".");
 }
 return ret/*.toString()*/;
}
/*public*/ void LocoIOModules::setLBVersion(QString version)
{
 locoBufferVersion = version;
 //dataListeners.firePropertyChange("LBVersionChange", "", locoBufferVersion);
 //emit firePropertyChange("LBVersionChange", QVariant(""), QVariant(locoBufferVersion));
}
/*public*/ QString LocoIOModules::getLBVersion() {
    return locoBufferVersion;
}
/*public*/ QList<LocoIOAddress*> LocoIOModules::probedAddresses()
{
 return _probedAddresses;
}
