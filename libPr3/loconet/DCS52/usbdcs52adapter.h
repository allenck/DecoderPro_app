#ifndef USBDCS52ADAPTER_H
#define USBDCS52ADAPTER_H
#include "locobufferadapter.h"

class UsbDcs52SystemConnectionMemo;
class Logger;
class UsbDcs52Adapter : public LocoBufferAdapter
{
 Q_OBJECT
public:
 UsbDcs52Adapter(QObject *parent = nullptr);
 /*public*/ void configure();
 /*public*/ QStringList validBaudRates();
 /*public*/ QVector<int> validBaudNumbers();
 /*public*/ int defaultBaudIndex();
 /*public*/ QStringList commandStationOptions();
 /*public*/ SystemConnectionMemo* getSystemConnectionMemo();
 /*public*/ QString className();

private:
 static Logger* log;

protected:
 /*protected*/ void setSerialPort(SerialPort* activeSerialPort); //throws UnsupportedCommOperationException

};

#endif // USBDCS52ADAPTER_H
