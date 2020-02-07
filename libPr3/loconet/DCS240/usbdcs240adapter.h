#ifndef USBDCS240ADAPTER_H
#define USBDCS240ADAPTER_H
#include "locobufferadapter.h"

class UsbDcs240SystemConnectionMemo;
class UsbDcs240Adapter : public LocoBufferAdapter
{
public:
 UsbDcs240Adapter(QObject *parent = nullptr);
 /*protected*/ void setSerialPort(SerialPort* activeSerialPort); //throws UnsupportedCommOperationException
 /*public*/ void configure();
 /*public*/ QStringList validBaudRates();
 /*public*/ QVector<int> validBaudNumbers();
 /*public*/ int defaultBaudIndex();
 /*public*/ QStringList commandStationOptions();
 /*public*/ SystemConnectionMemo* getSystemConnectionMemo();
private:
 static Logger* log;
};

#endif // USBDCS240ADAPTER_H
