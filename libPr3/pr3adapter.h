#ifndef PR3ADAPTER_H
#define PR3ADAPTER_H

#include "locobufferadapter.h"
#include "serialportadapter.h"
#include "loconetinterface.h"
//#include "masterthread.h"
#include "lnpacketizer.h"
#include "libPr3_global.h"

class PR3SystemConnectionMemo;
class LocoBufferAdapter;
class LocoNetInterface;
class LnPortController;
class LIBPR3SHARED_EXPORT PR3Adapter : public  LocoBufferAdapter
{
 Q_OBJECT
public:
 PR3Adapter(QObject* parent = 0);
 ~PR3Adapter(){}
 void configure();
 /**
  * Get an array of valid baud rates.
  */
 /*public*/ QStringList validBaudRates();
 /**
  * Get an array of valid baud rates as integers. This allows subclasses
  * to change the arrays of speeds.
  */
 /*public*/ QVector<int> validBaudNumbers();
 // Option 1 does flow control, inherited from LocoBufferAdapter

 /**
  * The PR3 can be used in numerous modes, so handle that
  */
 /*public*/ QStringList commandStationOptions();
 /*public*/ SystemConnectionMemo *getSystemConnectionMemo();
 /*public*/ void setTranspondingAvailable(QString value);
 /*public*/ QString className();

private:
 Logger* log;
// MasterThread* thread;
 //LnPacketizer* packets;
 QObject* myParent;
 QMutex mutex1;
protected:
/**
 * Always use flow control, not considered a user-settable option
 */
 void setSerialPort(SerialPort* activeSerialPort) /*throw(UnsupportedCommOperationException)*/;

};

#endif // PR3ADAPTER_H
