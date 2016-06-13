#include "ftdilib.h"
#include <QDebug>

Ftdilib::Ftdilib(QObject *parent) :
    QObject(parent)
{
 devInfo = NULL;
 loadDeviceList();
// _thread = new ftdithread(this);
// connect(_thread, SIGNAL(rfidMsgRcvd(ftdiMsg*)), this, SLOT(OnRfidRcvd(ftdiMsg*)));
 threadMap.clear();
}
Ftdilib::~Ftdilib()
{
 if(devInfo != NULL)
  free(devInfo);
}

void Ftdilib::loadDeviceList()
{
 DWORD numDevs;
 FT_STATUS ftStatus;
 if(devInfo != NULL)
  free(devInfo);

 // create the device information list
 ftStatus = FT_CreateDeviceInfoList(&numDevs);
 if (ftStatus == FT_OK)
 {
   qDebug()<< QString("Number of FTDI232 devices is %1").arg(numDevs);
 }
 else {
 // FT_CreateDeviceInfoList failed
 }
 if (numDevs > 0)
 {
  // allocate storage for list based on numDevs
  devInfo =
   (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numDevs);
  // get the device information list
  ftStatus = FT_GetDeviceInfoList(devInfo,&numDevs);
  if (ftStatus == FT_OK)
  {
   availPorts.clear();
   for (int i = 0; i < numDevs; i++)
   {
    qDebug() << tr("Dev %1:").arg(i);
    qDebug() << tr(" Flags=0x%1").arg(devInfo[i].Flags,0,16);
    qDebug() << tr(" Type=0x%1").arg(devInfo[i].Type,0,16);
    qDebug() << tr(" ID=0x%1").arg(devInfo[i].ID,0,16);
    qDebug() << tr(" LocId=0x%1").arg(devInfo[i].LocId,0,16);
    qDebug() << tr(" SerialNumber=%1").arg(devInfo[i].SerialNumber);
    qDebug() << tr(" Description=%1").arg(devInfo[i].Description);
    //qDebug() << tr(" ftHandle=0x%1").arg(devInfo[i].ftHandle,0,16);
    availPorts << devInfo[i].SerialNumber;
   }
  }
 }
}
//ftdithread* Ftdilib::thread() {return _thread;}

bool Ftdilib::openPort(QString serial)
{
// bIsOpen = _thread->openFtdiPort(serial);
 ftdithread* newThread = new ftdithread();
 bool bIsOpen = newThread->openFtdiPort(serial);
 if(bIsOpen)
 {
  threadMap.insert(serial, newThread);
  connect(newThread, SIGNAL(rfidMsgRcvd(ftdiMsg*)), this, SLOT(OnRfidRcvd(ftdiMsg*)));
 }
 return bIsOpen;
}
//bool Ftdilib::isOpen() { return bIsOpen;}

void Ftdilib::OnRfidRcvd(ftdiMsg *msg)
{
 emit rfidMsg(msg);
}
