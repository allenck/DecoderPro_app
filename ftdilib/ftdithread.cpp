#include "ftdithread.h"
#include <QDebug>

ftdithread::ftdithread(QObject *parent) :
    QThread(parent)
{
 bIsOpen = true;
 ftHandle = NULL;
 quit = false;
 connect(this, SIGNAL(finished()), this, SLOT(on_finished()));
}
ftdithread::~ftdithread()
{
 FT_Close(ftHandle);
 bIsOpen = false;
 ftHandle = NULL;
}
bool ftdithread::openFtdiPort(QString serial)
{
 QMutexLocker locker(&mutex);
 this->serial = serial;
 if (!isRunning())
  start();
 else
  cond.wakeOne();
 return true;
}

void ftdithread::run()
{
 FT_STATUS ftStatus;
#ifdef WIN32
 HANDLE hEvent;
 hEvent = CreateEvent(NULL,
                      false, // auto - reset event
                      false, // non - signalled state
                      L""
                      );
#else
 EVENT_HANDLE eh;
#endif
 DWORD EventMask = FT_EVENT_RXCHAR;
 quit = false;
 ftStatus = FT_OpenEx(serial.toLatin1().data(), FT_OPEN_BY_SERIAL_NUMBER, &ftHandle);
 if(ftStatus == FT_OK)
 {
  bIsOpen = true;
  ftStatus = FT_SetBaudRate(ftHandle, FT_BAUD_9600);
  ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1,FT_PARITY_NONE);
  ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_RTS_CTS,0x11, 0x13);
#ifdef WIN32
  ftStatus = FT_SetEventNotification(ftHandle, EventMask, hEvent);
#else
  pthread_mutex_init(&eh.eMutex, NULL);
  pthread_cond_init(&eh.eCondVar, NULL);
  ftStatus = FT_SetEventNotification(ftHandle, EventMask, &eh);
#endif
  while(!quit)
  {
#ifdef WIN32
 WaitForSingleObject(hEvent,INFINITE);
#else
   pthread_mutex_lock(&eh.eMutex);
   pthread_cond_wait(&eh.eCondVar, &eh.eMutex);
   pthread_mutex_unlock(&eh.eMutex);
#endif
   DWORD EventDWord;
   DWORD RxBytes;
   DWORD TxBytes;
   DWORD Status;
   DWORD BytesReceived;
   char RxBuffer[256];
   FT_GetStatus(ftHandle,&RxBytes,&TxBytes,&
   EventDWord);
   if (EventDWord & FT_EVENT_MODEM_STATUS)
   {
    // modem status event detected, so get current modem status
    FT_GetModemStatus(ftHandle,&Status);
    if (Status & 0x00000010)
    {
      // CTS is high
    }
    else
    {
      // CTS is low
    }
    if (Status & 0x00000020)
    {
      // DSR is high
    }
    else
    {
      // DSR is low
    }
   }
   if (RxBytes > 0)
   {
    msg.serial = serial;
    // call FT_Read() to get received data from device
    ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived);
    for(int i=0; i < BytesReceived; i++)
    {
     baRfid.append(RxBuffer[i]);
    }
    if(baRfid.count()>= 16)
    {
     if(baRfid.at(0) == 0x02 && baRfid.at(15) == 0x03)
     {
      msg.rfid = "";
      for(int i=1; i< 13; i++)
      {
       msg.rfid.append(baRfid.at(i));
      }
      emit rfidMsgRcvd(&msg);
      qDebug() << QString("RFID id %1 from %2").arg(msg.rfid).arg(msg.serial);
      baRfid.remove(0, 16);
     }
    }
   }
  }
 }
 else
 {
  emit error(tr("Error opening FTDI port %1 err %2").arg(serial).arg(ftStatus));
  qDebug() << tr("Error opening FTDI port %1 err %2").arg(serial).arg(ftStatus);
  bIsOpen = false;
 }
}
void ftdithread::setQuit()
{
 quit = true;
}
bool ftdithread::isOpen() { return bIsOpen;}
QString ftdithread::currPort() {return serial;}

ftdiMsg* ftdithread:: lastMsg()
{ return &msg;}

void ftdithread::on_finished()
{
    qDebug() << tr("ftdithreead finishing");
}
